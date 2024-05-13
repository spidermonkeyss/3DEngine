#include "Renderer.h"
#include "Component/ComponentHandler.h"
#include "GameObject.h"
#include "Scene.h"

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
    Model* model = Scene::currentScene->componentHandler.GetComponentUnsafe<Model>(objectId);

    if (!model->isEnabled)
        return;
    if (model->mesh == nullptr || model->material == nullptr)
        return;
    if (model->material->shader == nullptr)
        return;
    if (!model->mesh->isLoaded || !model->material->isLoaded || !model->material->shader->isLoaded)
        return;

    model->mesh->Bind();
    model->material->shader->Bind();
    model->material->ApplyMaterialToShader();

    Transform* transform = &model->GameObject()->transform;

    glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform->position.x, transform->position.y, transform->position.z));

    glm::mat4 mvp = projectionMatrix * viewMatrix * transformMatrix;
    model->material->shader->SetMVP("MVP", & mvp[0][0]);

    if (model->mesh->hasIndexBuffer)
    {
        GLCall(glDrawElements(GL_TRIANGLES, model->mesh->indexCount, model->mesh->indexType, nullptr));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, model->mesh->vertexCount));
    }
}

int Renderer::Init()
{
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1280, 960, "3DEngine", NULL, NULL);
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

    return 0;
}

void Renderer::SetCamera(Camera* _camera)
{
    camera = _camera;
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));
    // 0.14f, 0.5f, 0.85f, 1.0f
}

void Renderer::Render()
{
    if (camera != nullptr)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        projectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 150.0f);
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(camera->transform.position.x, camera->transform.position.y, camera->transform.position.z));
        viewMatrix = glm::inverse(viewMatrix);

        std::unordered_map<unsigned int, Model>::iterator i;
        for (i = Scene::currentScene->componentHandler.modelComponents.begin(); i != Scene::currentScene->componentHandler.modelComponents.end(); ++i)
            DrawModel(i->first);
    }
}

void Renderer::SwapBuffer()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
    shouldWindowClose = glfwWindowShouldClose(window);
}


