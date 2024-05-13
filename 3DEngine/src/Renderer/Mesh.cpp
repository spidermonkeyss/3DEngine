#include "Mesh.h"
#include "GLCall.h"
#include "Scene.h"
#include "FileLoader.h"

Mesh::Mesh()
{
    gl_VertexBufferId = 0;
    gl_VertexArrayId = 0;
    gl_IndexBufferId = 0;
    vertexCount = 0;
    vertexByteStride = 0;
    hasIndexBuffer = false;
    indexCount = 0;
    indexType = 0;
    isLoaded = false;
}

Mesh::~Mesh()
{
    //GLCall(glDeleteBuffers(1, &gl_VertexArrayId));
    //GLCall(glDeleteBuffers(1, &gl_VertexBufferId));
    //GLCall(glDeleteBuffers(1, &gl_IndexBufferId));
}

Mesh* Mesh::CreateMesh()
{
    return Scene::currentScene->CreateMesh();
}

void Mesh::Bind()
{
    GLCall(glBindVertexArray(gl_VertexArrayId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_IndexBufferId));
}

void Mesh::LoadGlVertexArray(const void* vertexData)
{
    vertexByteStride = 0;
    for (int i = 0; i < vertexAttributeLayouts.size(); i++)
        vertexByteStride += vertexAttributeLayouts[i].count * vertexAttributeLayouts[i].typeByteSize;
    int bufferSize = vertexCount * vertexByteStride;

    GLCall(glGenBuffers(1, &gl_VertexBufferId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, gl_VertexBufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexData, GL_STATIC_DRAW));

    GLCall(glGenVertexArrays(1, &gl_VertexArrayId));
    GLCall(glBindVertexArray(gl_VertexArrayId));

    unsigned int offset = 0;
    for (int i = 0; i < vertexAttributeLayouts.size(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, vertexAttributeLayouts[i].count, GL_FLOAT, GL_FALSE, vertexByteStride, (const void*)offset));
        offset += vertexAttributeLayouts[i].count * vertexAttributeLayouts[i].typeByteSize;
    }
}

void Mesh::LoadGlIndexBuffer(const void* indexData, int count, unsigned int type) 
{
    hasIndexBuffer = true;
    indexCount = count;
    indexType = type;
    GLCall(glGenBuffers(1, &gl_IndexBufferId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_IndexBufferId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indexData, GL_STATIC_DRAW));
}

bool Mesh::LoadMeshFile(const std::string& _filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(_filePath);
    
    if (extensionTypeStr == "obj")
    {
        //give it size one and set the first index to something so it can still be deleted if the mesh doesnt load
        float** vertexData = new float*[1];
        vertexAttributeLayouts.clear();
        vertexData[0] = 0;
        isLoaded = FileLoader::Load_obj_file(_filePath, vertexData, &vertexAttributeLayouts, vertexCount);
        
        if (isLoaded)
        {
            filePath = _filePath;
            LoadGlVertexArray(*vertexData);
            return true;
        }
        delete[] *vertexData;
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
    return false;
}