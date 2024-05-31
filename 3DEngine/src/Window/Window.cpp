#include "Window.h"
#include "GLCall.h"
#include <GLFW/glfw3.h>

Window* Window::currentWindow = nullptr;

Window::Window()
    : glfw_window(nullptr)
{
}

void Window::framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
    currentWindow->width = _width;
    currentWindow->height = _height;
    glViewport(0, 0, _width, _height);
}

int Window::Init()
{
    currentWindow = this;

    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfw_window = glfwCreateWindow(width, height, "3DEngine", NULL, NULL);
    if (!glfw_window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSwapInterval(1);

    //callbacks
    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    fprintf(stdout, "OpenGL version: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "GLFW version: %s\n", glfwGetVersionString());
    fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));

    bool drawWireFrame = false;
    if (drawWireFrame)
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
    else
    {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        GLCall(glEnable(GL_BLEND));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glFrontFace(GL_CCW));
    }

    return 0;
}

void Window::SwapBuffer()
{
    glfwSwapBuffers(glfw_window);
    shouldWindowClose = glfwWindowShouldClose(glfw_window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

double Window::GetTime()
{
    return glfwGetTime();
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));
    // 0.14f, 0.5f, 0.85f, 1.0f
}

void Window::Terminate()
{
    glfwTerminate();
}