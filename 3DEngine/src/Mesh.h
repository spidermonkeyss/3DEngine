#pragma once
#include <string>
#include "FileLoader.h"

class Mesh
{
private:
	void LoadGlVertexArray(const void* vertexData, FileLoader::VertexAttributeInfo* attributeInfo);
	void LoadGlIndexBuffer(const void* indexData, int count, unsigned int type);
	unsigned int gl_VertexBufferId;
	unsigned int gl_VertexArrayId;
	unsigned int gl_IndexBufferId;
public:
	int vertexCount;
	int vertexStride;
	int vertexTypeSize;
	bool hasIndexBuffer;
	int indexCount;
	unsigned int indexType;

	Mesh();
	~Mesh();
	
	void Bind();

	bool LoadMeshFile(const std::string& filePath);

};