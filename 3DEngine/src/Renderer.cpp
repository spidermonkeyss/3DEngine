#include "Renderer.h"
#include "Component/ComponentHandler.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

char Renderer::keyPressed = 'n';

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
        keyPressed = 'w';
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
        keyPressed = 'a';
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
        keyPressed = 's';
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        keyPressed = 'd';
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        keyPressed = 'q';
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
        keyPressed = 'e';
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        keyPressed = 'z';
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
        keyPressed = 'x';
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Renderer::Renderer()
    :window(), camera(nullptr)
{
}

void Renderer::DrawModel(unsigned int objectId)
{
    Model* model = ComponentHandler::GetComponentUnsafe<Model>(objectId);

    if (!model->isEnabled)
        return;
    if (model->GetMesh() == nullptr || model->GetShader() == nullptr)
        return;
    if (model->GetMesh()->vertexTypeSize == 0)
        return;

    model->GetMesh()->Bind();
    model->GetShader()->Bind();

    Transform* transform = ComponentHandler::GetComponentUnsafe<Transform>(objectId);

    glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform->position.x, transform->position.y, transform->position.z));

    glm::mat4 mvp = projectionMatrix * viewMatrix * transformMatrix;
    model->GetShader()->SetMVP(&mvp[0][0]);

    if (model->GetMesh()->hasIndexBuffer)
    {
        GLCall(glDrawElements(GL_TRIANGLES, model->GetMesh()->indexCount, model->GetMesh()->indexType, nullptr));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, model->GetMesh()->vertexCount));
    }
}

int Renderer::Init()
{
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "3DEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
}

void Renderer::SetCamera(Camera* _camera)
{
    camera = _camera;
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
    Clear();

    if (camera != nullptr)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        projectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 150.0f);
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(camera->Transform()->position.x, camera->Transform()->position.y, camera->Transform()->position.z));
        viewMatrix = glm::inverse(viewMatrix);

        std::map<unsigned int, Model>::iterator i;
        for (i = ComponentHandler::GetModelComponents()->begin(); i != ComponentHandler::GetModelComponents()->end(); ++i)
            DrawModel(i->first);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
    shouldWindowClose = glfwWindowShouldClose(window);
}


