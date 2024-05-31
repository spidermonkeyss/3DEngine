#pragma once

struct GLFWwindow;

class Window
{
protected:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);

private:
	static Window* currentWindow;
	GLFWwindow* glfw_window;
	int width = 1280;
	int height = 960;
	bool shouldWindowClose = false;

	Window();

	int Init();
	void Clear();
	void SwapBuffer();
	void PollEvents();
	double GetTime();
	void Terminate();

	friend class Renderer;
	friend class Engine;
	friend class EngineTime;
};