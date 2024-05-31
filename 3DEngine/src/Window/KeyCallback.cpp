#include "Window.h"
#include "Input.h"
#include "GLCall.h"
#include <GLFW/glfw3.h>

void Window::key_callback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_Q:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::Q] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::Q] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::Q] = Input::DOWN;
        break;
    case GLFW_KEY_W:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::W] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::W] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::W] = Input::DOWN;
        break;
    case GLFW_KEY_E:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::E] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::E] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::E] = Input::DOWN;
        break;
    case GLFW_KEY_R:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::R] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::R] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::R] = Input::DOWN;
        break;
    case GLFW_KEY_T:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::T] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::T] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::T] = Input::DOWN;
        break;







    case GLFW_KEY_A:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::A] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::A] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::A] = Input::DOWN;
        break;
    case GLFW_KEY_S:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::S] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::S] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::S] = Input::DOWN;
        break;
    case GLFW_KEY_D:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::D] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::D] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::D] = Input::DOWN;
        break;
    case GLFW_KEY_Z:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::Z] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::Z] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::Z] = Input::DOWN;
        break;
    case GLFW_KEY_X:
        if (action == GLFW_REPEAT)
            Input::keyStates[Input::X] = Input::HELD;
        else if (action == GLFW_RELEASE)
            Input::keyStates[Input::X] = Input::RELEASED;
        else if (action == GLFW_PRESS)
            Input::keyStates[Input::X] = Input::DOWN;
        break;
 
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
}