#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"

#include <vector>

class Engine
{
private:
	static void IMGUI_ShowMesh(Mesh* mesh);
	static void IMGUI_ShowShader(Shader* shader);
	static void IMGUI_ShowTexture(Texture* texture);
	static void IMGUI_ShowMaterial(Material* material);

	static void RunImGuiFrame();
public:
	static int RunEngine();
};