#pragma once
#include "GameObject.h"

#include <string>
#include <vector>

class Scene
{
private:
	static Scene* currentScene;

	std::unordered_map<unsigned int, std::unique_ptr<GameObject>> gameObjects;
	std::vector<Shader> shaders;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;

	ComponentHandler componentHandler;

	Scene();
	void CreateGameObjects(std::vector<Shader>* shaders, std::vector<Mesh>* meshes);
public:
	void LoadScene(const std::string& filePath);

private:
	friend class GameObject;
	friend class Engine;
	friend class Renderer;
	friend class Physics;
};