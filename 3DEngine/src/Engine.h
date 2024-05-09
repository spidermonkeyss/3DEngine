#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include <vector>

class Engine
{
private:
	static void RunImGuiFrame();
public:
	static int RunEngine();
};