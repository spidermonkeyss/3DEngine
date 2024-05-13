#pragma once
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

class FileLoader
{
public:
    struct VertexPosition
    {
        float x, y, z;
    };
    struct VertexUV
    {
        float u, v;
    };
    struct VertexNormal
    {
        float x, y, z;
    };
    struct Vertex
    {
        VertexPosition v;
        VertexUV vt;
        VertexNormal vn;
    };

    static std::string GetFileExtension(const std::string& filePath);
    static std::string GetFileName(const std::string& filePath);

    static bool Load_obj_file(const std::string& filePath, float** vertexData, std::vector<Mesh::VertexAttributeLayout>* attributeLayouts, int& vertexCount);
    static std::vector<std::string> Load_shader_file(const std::string& filePath);
    static bool Load_bmat_file(const std::string& filePath, Material::MaterialFileProperties* mfp);
    static unsigned char* Load_image_file(const std::string& filePath, int* width, int* height, int* channels, int desiredChannels);
};