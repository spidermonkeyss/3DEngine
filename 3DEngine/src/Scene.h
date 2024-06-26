#pragma once
#include "GameObject.h"
#include "LinkedList.h"
#include "Renderer/Material.h"
#include "Component/ComponentHandler.h"
#include "ScriptHandler_Injected.h"

#include <string>
#include <vector>

class Scene
{
private:
	static Scene* currentScene;

	std::unordered_map<unsigned int, std::unique_ptr<GameObject>> gameObjects;
	LinkedList<Shader> shaders;
	LinkedList<Mesh> meshes;
	LinkedList<Texture> textures;
	LinkedList<Material> materials;

	ComponentHandler componentHandler;
	ScriptHandler scriptHandler;

	Scene() = default;

	Material* CreateMaterial();
	Mesh* CreateMesh();
	Shader* CreateShader();
	Texture* CreateTexture();

	void StartScripts();
	void UpdateScripts();
public:
	void LoadScene(const std::string& filePath);

private:
	friend class GameObject;
	friend class Engine;
	friend class Renderer;
	friend class Physics;
	friend class Texture;
	friend class Material;
	friend class Mesh;
	friend class Shader;
	friend class Model;
};