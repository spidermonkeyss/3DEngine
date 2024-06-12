#include "Window.h"
#include "Input.h"
#include "GLCall.h"
#include <GLFW/glfw3.h>

void Window::InitGLFWKeyArray()
{
    glfwInputKeyMap[GLFW_KEY_Q] = Input::Q;
    glfwInputKeyMap[GLFW_KEY_W] = Input::W;
    glfwInputKeyMap[GLFW_KEY_E] = Input::E;
    glfwInputKeyMap[GLFW_KEY_R] = Input::R;
    glfwInputKeyMap[GLFW_KEY_T] = Input::T;
    glfwInputKeyMap[GLFW_KEY_Y] = Input::Y;
    glfwInputKeyMap[GLFW_KEY_U] = Input::U;
    glfwInputKeyMap[GLFW_KEY_I] = Input::I;
    glfwInputKeyMap[GLFW_KEY_O] = Input::O;
    glfwInputKeyMap[GLFW_KEY_P] = Input::P;
    glfwInputKeyMap[GLFW_KEY_A] = Input::A;
    glfwInputKeyMap[GLFW_KEY_S] = Input::S;
    glfwInputKeyMap[GLFW_KEY_D] = Input::D;
    glfwInputKeyMap[GLFW_KEY_F] = Input::F;
    glfwInputKeyMap[GLFW_KEY_G] = Input::G;
    glfwInputKeyMap[GLFW_KEY_H] = Input::H;
    glfwInputKeyMap[GLFW_KEY_J] = Input::J;
    glfwInputKeyMap[GLFW_KEY_K] = Input::K;
    glfwInputKeyMap[GLFW_KEY_L] = Input::L;
    glfwInputKeyMap[GLFW_KEY_Z] = Input::Z;
    glfwInputKeyMap[GLFW_KEY_X] = Input::X;
    glfwInputKeyMap[GLFW_KEY_C] = Input::C;
    glfwInputKeyMap[GLFW_KEY_V] = Input::V;
    glfwInputKeyMap[GLFW_KEY_B] = Input::B;
    glfwInputKeyMap[GLFW_KEY_N] = Input::N;
    glfwInputKeyMap[GLFW_KEY_M] = Input::M;
}

void Window::key_callback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, GLFW_TRUE);

    if (action == GLFW_REPEAT)
        Input::keyStates[glfwInputKeyMap[key]] = Input::HELD;
    else if (action == GLFW_RELEASE)
        Input::keyStates[glfwInputKeyMap[key]] = Input::RELEASED;
    else if (action == GLFW_PRESS)
        Input::keyStates[glfwInputKeyMap[key]] = Input::DOWN;
}