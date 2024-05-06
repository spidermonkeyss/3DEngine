#pragma once
#include <string>
#include "FileLoader.h"

class Mesh
{
private:
	unsigned int gl_VertexBufferId;
	unsigned int gl_VertexArrayId;
	unsigned int gl_IndexBufferId;

	int vertexCount;
	int vertexStride;
	int vertexTypeSize;
	bool hasIndexBuffer;
	int indexCount;
	unsigned int indexType;
	
	void Bind();

	void LoadGlVertexArray(const void* vertexData, FileLoader::VertexAttributeInfo* attributeInfo);
	void LoadGlIndexBuffer(const void* indexData, int count, unsigned int type);
public:
	Mesh();
	~Mesh();

	bool LoadMeshFile(const std::string& filePath);

private:
	friend class Renderer;
};