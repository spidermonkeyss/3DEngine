#include "Mesh.h"
#include "GLCall.h"

Mesh::Mesh()
{
    gl_VertexBufferId = 0;
    gl_VertexArrayId = 0;
    gl_IndexBufferId = 0;
    vertexCount = -1;
    vertexStride = -1;
    vertexTypeSize = -1;
    hasIndexBuffer = false;
    indexCount = -1;
    indexType = 0;
}

Mesh::~Mesh()
{
    //GLCall(glDeleteBuffers(1, &gl_VertexArrayId));
    //GLCall(glDeleteBuffers(1, &gl_VertexBufferId));
    //GLCall(glDeleteBuffers(1, &gl_IndexBufferId));
}

void Mesh::Bind()
{
    GLCall(glBindVertexArray(gl_VertexArrayId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_IndexBufferId));
}

void Mesh::LoadGlVertexArray(const void* vertexData, FileLoader::VertexAttributeInfo* attributeInfo)
{
    vertexStride = 0;
    for (int i = 0; i < attributeInfo->attributeSize.size(); i++)
        vertexStride += attributeInfo->attributeSize[i];
    int vertexStrideByteSize = vertexTypeSize * vertexStride;
    int bufferSize = vertexCount * vertexStrideByteSize;

    GLCall(glGenBuffers(1, &gl_VertexBufferId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, gl_VertexBufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexData, GL_STATIC_DRAW));

    GLCall(glGenVertexArrays(1, &gl_VertexArrayId));
    GLCall(glBindVertexArray(gl_VertexArrayId));

    unsigned int offset = 0;
    for (int i = 0; i < attributeInfo->attributeSize.size(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, attributeInfo->attributeSize[i], GL_FLOAT, GL_FALSE, vertexStrideByteSize, (const void*)offset));
        offset += attributeInfo->attributeSize[i] * 4;
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

bool Mesh::LoadMeshFile(const std::string& filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(filePath);
    
    if (extensionTypeStr == "obj")
    {
        //give it size one and set the first index to something so it can still be deleted if the mesh doesnt load
        float** vertexData = new float*[1];
        vertexData[0] = 0;
        FileLoader::VertexAttributeInfo attributeInfo;
        bool isMeshLoaded = FileLoader::LoadOBJFile(filePath, vertexData, &attributeInfo, vertexCount);
        
        if (isMeshLoaded)
        {
            vertexTypeSize = 4;
            LoadGlVertexArray(*vertexData, &attributeInfo);
            return true;
        }
        else
        {
            vertexTypeSize = 0;
        }
        delete[] *vertexData;
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
    return false;
}