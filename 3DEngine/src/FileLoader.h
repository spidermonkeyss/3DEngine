#pragma once
#include <vector>
#include <string>

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

    struct VertexAttributeInfo
    {
        std::vector<int> attributeSize;
    };

    static std::string GetFileExtension(const std::string& filePath);
    static bool LoadOBJFile(const std::string& filePath, float** vertexData, VertexAttributeInfo* attributeInfo, int& vertexCount);
    static std::vector<std::string> LoadShaderFile(const std::string& filePath);
};