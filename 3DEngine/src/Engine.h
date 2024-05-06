#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include <vector>

class Engine
{
private:
	static void CreateGameObjects(std::vector<Shader>* shaders, std::vector<Mesh>* meshes);
public:
	static int RunEngine();
};