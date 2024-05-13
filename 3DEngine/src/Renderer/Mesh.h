#pragma once
#include <string>
#include <vector>

class Mesh
{
private:
	struct VertexAttributeLayout
	{
		int count;
		int typeByteSize;
	};

	unsigned int gl_VertexBufferId;
	unsigned int gl_VertexArrayId;
	unsigned int gl_IndexBufferId;

	int vertexCount;
	int vertexByteStride;
	bool hasIndexBuffer;
	int indexCount;
	unsigned int indexType;
	
	std::string filePath;
	std::vector<VertexAttributeLayout> vertexAttributeLayouts;
	
	void Bind();

	void LoadGlVertexArray(const void* vertexData);
	void LoadGlIndexBuffer(const void* indexData, int count, unsigned int type);

	Mesh();
public:
	bool isLoaded;

	~Mesh();

	bool LoadMeshFile(const std::string& filePath);

	static Mesh* CreateMesh();
private:
	friend class Engine;
	friend class Renderer;
	friend class FileLoader;
	friend class Model;
	friend class Scene;
};