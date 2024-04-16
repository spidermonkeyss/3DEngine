#include "FileLoader.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>

std::string FileLoader::GetFileExtension(const std::string& filePath)
{
    int fileExtensionDotIndex = filePath.find_last_of('.');

    if (fileExtensionDotIndex == -1)
    {
        std::cout << "File name has no extension. No extension found\n";
        return "";
    }

    if (fileExtensionDotIndex == filePath.size() - 1)
    {
        std::cout << "File name ends with dot. No extension found\n";
        return "";
    }

    return filePath.substr(fileExtensionDotIndex + 1, filePath.size() - 1);
}

bool FileLoader::LoadOBJFile(const std::string& filePath, float** vertexData, VertexAttributeInfo* attributeInfo, int& vertexCount)
{
    try
    {

        std::ifstream stream(filePath);
        std::string line = "";
        if (line[0] == ';')
        {

        }
        std::vector<VertexPosition> vertexPositions;
        std::vector<VertexUV> vertexUVs;
        std::vector<VertexNormal> vertexNormals;
        std::vector<Vertex> vertexArray;

        while (getline(stream, line))
        {
            if (line.find("vp") != std::string::npos)
            {
                std::cout << "Free-form geometry is not supported\n";
                return false;
            }
            else if (line[0] == '#')
            {
                //This line is a comment
            }
            else if (line.find("vn") != std::string::npos)
            {
                int xIndex = line.find(' ') + 1;
                int yIndex = line.find(' ', xIndex) + 1;
                int zIndex = line.find(' ', yIndex) + 1;

                std::string xStr = line.substr(xIndex, yIndex - xIndex);
                std::string yStr = line.substr(yIndex, zIndex - yIndex);
                std::string zStr = line.substr(zIndex, line.size() - zIndex);

                float x = std::stof(xStr);
                float y = std::stof(yStr);
                float z = std::stof(zStr);

                vertexNormals.push_back({ x, y, z });
            }
            else if (line.find("vt") != std::string::npos)
            {
                int uIndex = line.find(' ') + 1;
                int vIndex = line.find(' ', uIndex) + 1;

                std::string uStr = line.substr(uIndex, vIndex - uIndex);
                std::string vStr = line.substr(vIndex, line.size() - vIndex);

                float u = std::stof(uStr);
                float v = std::stof(vStr);

                vertexUVs.push_back({ u, v });
            }
            else if (line[0] == 'v')
            {
                int xIndex = line.find(' ') + 1;
                int yIndex = line.find(' ', xIndex) + 1;
                int zIndex = line.find(' ', yIndex) + 1;

                std::string xStr = line.substr(xIndex, yIndex - xIndex);
                std::string yStr = line.substr(yIndex, zIndex - yIndex);
                std::string zStr = line.substr(zIndex, line.size() - zIndex);

                float x = std::stof(xStr);
                float y = std::stof(yStr);
                float z = std::stof(zStr);

                vertexPositions.push_back({ x, y, z });
            }
            else if (line[0] == 'f')
            {
                int v1Index = line.find(' ') + 1;
                int v2Index = line.find(' ', v1Index) + 1;
                int v3Index = line.find(' ', v2Index) + 1;

                std::string v1Str = line.substr(v1Index, v2Index - v1Index);
                std::string v2Str = line.substr(v2Index, v3Index - v2Index);
                std::string v3Str = line.substr(v3Index, line.size() - v3Index);

                //File had both normals and uvs
                if (vertexNormals.size() != 0 && vertexUVs.size() != 0)
                {
                    Vertex vertex1;
                    int v1_v_Index = std::stoi(v1Str.substr(0, v1Str.find_first_of('/')));
                    int v1_vt_Index = std::stoi(v1Str.substr(v1Str.find_first_of('/') + 1, v1Str.find_last_of('/')));
                    int v1_vn_Index = std::stoi(v1Str.substr(v1Str.find_last_of('/') + 1, v1Str.size()));

                    //position
                    vertex1.v.x = vertexPositions.at(v1_v_Index - 1).x;
                    vertex1.v.y = vertexPositions.at(v1_v_Index - 1).y;
                    vertex1.v.z = vertexPositions.at(v1_v_Index - 1).z;
                    //normal
                    vertex1.vn.x = vertexNormals.at(v1_vn_Index - 1).x;
                    vertex1.vn.y = vertexNormals.at(v1_vn_Index - 1).y;
                    vertex1.vn.z = vertexNormals.at(v1_vn_Index - 1).z;
                    //uvs
                    vertex1.vt.u = vertexUVs.at(v1_vt_Index - 1).u;
                    vertex1.vt.v = vertexUVs.at(v1_vt_Index - 1).v;

                    Vertex vertex2;
                    int v2_v_Index = std::stoi(v2Str.substr(0, v2Str.find_first_of('/')));
                    int v2_vt_Index = std::stoi(v2Str.substr(v2Str.find_first_of('/') + 1, v2Str.find_last_of('/')));
                    int v2_vn_Index = std::stoi(v2Str.substr(v2Str.find_last_of('/') + 1, v2Str.size()));

                    //position
                    vertex2.v.x = vertexPositions.at(v2_v_Index - 1).x;
                    vertex2.v.y = vertexPositions.at(v2_v_Index - 1).y;
                    vertex2.v.z = vertexPositions.at(v2_v_Index - 1).z;
                    //normal
                    vertex2.vn.x = vertexNormals.at(v2_vn_Index - 1).x;
                    vertex2.vn.y = vertexNormals.at(v2_vn_Index - 1).y;
                    vertex2.vn.z = vertexNormals.at(v2_vn_Index - 1).z;
                    //uvs
                    vertex2.vt.u = vertexUVs.at(v2_vt_Index - 1).u;
                    vertex2.vt.v = vertexUVs.at(v2_vt_Index - 1).v;

                    Vertex vertex3;
                    int v3_v_Index = std::stoi(v3Str.substr(0, v3Str.find_first_of('/')));
                    int v3_vt_Index = std::stoi(v3Str.substr(v3Str.find_first_of('/') + 1, v3Str.find_last_of('/')));
                    int v3_vn_Index = std::stoi(v3Str.substr(v3Str.find_last_of('/') + 1, v3Str.size()));

                    //position
                    vertex3.v.x = vertexPositions.at(v3_v_Index - 1).x;
                    vertex3.v.y = vertexPositions.at(v3_v_Index - 1).y;
                    vertex3.v.z = vertexPositions.at(v3_v_Index - 1).z;
                    //normal
                    vertex3.vn.x = vertexNormals.at(v3_vn_Index - 1).x;
                    vertex3.vn.y = vertexNormals.at(v3_vn_Index - 1).y;
                    vertex3.vn.z = vertexNormals.at(v3_vn_Index - 1).z;
                    //uvs
                    vertex3.vt.u = vertexUVs.at(v3_vt_Index - 1).u;
                    vertex3.vt.v = vertexUVs.at(v3_vt_Index - 1).v;

                    vertexArray.push_back(vertex1);
                    vertexArray.push_back(vertex2);
                    vertexArray.push_back(vertex3);
                }
                //File has normals, no uvs
                else if (vertexNormals.size() != 0)
                {
                    std::cout << "obj files without uvs are not yet supported.\n";
                    return false;
                }
                //File has uvs, no normals
                else if (vertexUVs.size() != 0)
                {
                    std::cout << "obj files without normals are not yet supported.\n";
                    return false;
                }
                //File has no normals no uvs
                else
                {
                    std::cout << "obj files without normals and uvs are not yet supported.\n";
                    return false;
                }
            }
        }

        //Mesh could not be created
        if (vertexArray.size() == 0)
        {
            std::cout << "Mesh could not be created from file.\n";
            return false;
        }

        //File had both normals and uvs
        if (vertexNormals.size() != 0 && vertexUVs.size() != 0)
        {
            attributeInfo->attributeSize.push_back(3);
            attributeInfo->attributeSize.push_back(2);
            attributeInfo->attributeSize.push_back(3);

            vertexCount = vertexArray.size();

            float* vertexData1 = new float[vertexCount * 8];
            for (int i = 0; i < vertexCount; i++)
            {
                vertexData1[(i * 8) + 0] = vertexArray.at(i).v.x;
                vertexData1[(i * 8) + 1] = vertexArray.at(i).v.y;
                vertexData1[(i * 8) + 2] = vertexArray.at(i).v.z;
                vertexData1[(i * 8) + 3] = vertexArray.at(i).vt.u;
                vertexData1[(i * 8) + 4] = vertexArray.at(i).vt.v;
                vertexData1[(i * 8) + 5] = vertexArray.at(i).vn.x;
                vertexData1[(i * 8) + 6] = vertexArray.at(i).vn.y;
                vertexData1[(i * 8) + 7] = vertexArray.at(i).vn.z;
            }
            *vertexData = vertexData1;
        }
        //File has normals, no uvs
        else if (vertexNormals.size() != 0)
        {

        }
        //File has uvs, no normals
        else if (vertexUVs.size() != 0)
        {

        }
        //File has no normals no uvs
        else
        {

        }

        return true;
    }
    catch(...)
    {
        std::cout << "EXCEPTION THROW WHILE LOADING MESH: " + filePath + "\n";
        return false;
    }
}

std::vector<std::string> FileLoader::LoadShaderFile(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::vector<std::string> ss(2);
    
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type].append(line + '\n');
        }
    }

    return ss;
}
