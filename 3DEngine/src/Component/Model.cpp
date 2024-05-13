#include "Model.h"
#include "GameObject.h"
#include "GLCall.h"
#include "Camera.h"
#include "LinkedList.h"
#include "Scene.h"

Model::Model()
{
	mesh = nullptr;
	material = nullptr;
}

void Model::SetMesh(Mesh* _mesh)
{
	if (_mesh->isLoaded)
		mesh = _mesh;
	else
		std::cout << "WARNING: mesh not loaded when trying to apply to model" << std::endl;
}

void Model::SetMesh(std::string _filePath)
{
	//if the mesh is already loaded just set it the model
	bool foundMesh = false;

	for (LinkedList<Mesh>::Iterator i = Scene::currentScene->meshes.Begin(); i != Scene::currentScene->meshes.End(); ++i)
	{
		Mesh* _mesh = i.Data();
		if (_filePath == _mesh->filePath)
		{
			foundMesh = true;
			if (_mesh->isLoaded)
				mesh = _mesh;
			else
				std::cout << "WARNING: mesh " + _filePath << " not loaded when trying to apply to model" << std::endl;
		}
	}

	if (!foundMesh)
	{
		std::cout << "Loading mesh at: " << _filePath << std::endl;
		mesh = Mesh::CreateMesh();
		bool loaded = mesh->LoadMeshFile(_filePath);
		if (loaded)
		{

		}
		else
		{
			mesh = nullptr;
			std::cout << "WARNING: no mesh found by the name: " + _filePath << std::endl;
		}
	}
}

void Model::SetMaterial(Material* _material)
{
	if (_material->isLoaded)
		material = _material;
	else
		std::cout << "WARNING: material not loaded when trying to apply to model" << std::endl;
}

void Model::SetMaterial(std::string _filePath)
{
	//if the material is already loaded just set it the model
	bool foundMaterial = false;

	for (LinkedList<Material>::Iterator i = Scene::currentScene->materials.Begin(); i != Scene::currentScene->materials.End(); ++i)
	{
		Material* _material = i.Data();
		if (_filePath == _material->filePath)
		{
			foundMaterial = true;
			if (_material->isLoaded)
				material = _material;
			else
				std::cout << "WARNING: material " + _filePath << " not loaded when trying to apply to model" << std::endl;
		}
	}

	if (!foundMaterial)
	{
		std::cout << "Loading material at: " << _filePath << std::endl;
		material = Material::CreateMaterial();
		bool loaded = material->LoadMaterialFile(_filePath);
		if (loaded)
		{

		}
		else
		{
			material = nullptr;
			std::cout << "WARNING: no material found by the name: " + _filePath << std::endl;
		}
	}
}
