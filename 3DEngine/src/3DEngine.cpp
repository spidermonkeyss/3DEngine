#include <iostream>
#include "GLCall.h"
#include "GameObject.h"
#include "Camera.h"

char keyPressed = 'n';
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

#include <filesystem>
std::vector<Shader> LoadShaders(const std::string& filePath)
{
    std::vector<Shader> shaders;
    bool isLoaded = false;

    if (std::filesystem::exists(filePath))
    {
        for (const auto& entry : std::filesystem::directory_iterator(filePath))
        {
            std::cout << "Trying to load shader at: " << entry.path() << std::endl;
            Shader shader;
            isLoaded = shader.LoadShaderFile(entry.path().generic_string());
            if (isLoaded)
                shaders.push_back(shader);
        }
    }

    std::cout << shaders.size() << " shaders loaded" << std::endl;
    return shaders;
}

std::vector<Mesh> LoadMeshes(const std::string& filePath)
{
    std::vector<Mesh> meshes;
    bool isLoaded = false;

    if (std::filesystem::exists(filePath))
    {
        for (const auto& entry : std::filesystem::directory_iterator(filePath))
        {
            std::cout << "Trying to load mesh at: " << entry.path() << std::endl;
            Mesh mesh;
            isLoaded = mesh.LoadMeshFile(entry.path().generic_string());
            if (isLoaded)
                meshes.push_back(mesh);
        }
    }

    std::cout << meshes.size() << " meshes loaded" << std::endl;
    return meshes;
}

void CreateGameObjects(std::vector<GameObject>* gameObjects, std::vector<Shader>* shaders, std::vector<Mesh>* meshes)
{
    gameObjects->resize(shaders->size() * meshes->size());

    float xSpacing = 3.0f;
    float ySpacing = 3.0f;

    int i = 0;
    for (int shaderIndex = 0; shaderIndex < shaders->size(); shaderIndex++)
    {
        for (int meshIndex = 0; meshIndex < meshes->size(); meshIndex++)
        {
            gameObjects->at(i).AddModel();
            gameObjects->at(i).GetModel()->SetMesh(&meshes->at(meshIndex));
            gameObjects->at(i).GetModel()->SetShader(&shaders->at(shaderIndex));
            gameObjects->at(i).Transform()->SetPosition(meshIndex * xSpacing, shaderIndex * ySpacing, 0.0f);
            i++;
        }
    }

    std::cout << gameObjects->size() << " GameObjects created" << std::endl;
}


int main(void)
{
    GLFWwindow* window;

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

    Camera camera(window);
    camera.Transform()->SetPosition(0.0f, 0.0f, 5.0f);

    std::vector<Shader> shaders = LoadShaders("res/Shaders/");
    std::vector<Mesh> meshes = LoadMeshes("res/Meshes/");
    std::vector<GameObject> gameObjects;
    CreateGameObjects(&gameObjects, &shaders, &meshes);


    double prevFrameTime = glfwGetTime();
    double deltaTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        deltaTime = glfwGetTime() - prevFrameTime;

        float speed = 0.5f;
        Vector3 cPos = camera.Transform()->Position();

        if (keyPressed == 'w')
            camera.Transform()->SetPosition(cPos.x, cPos.y, cPos.z - speed);
        if (keyPressed == 's')
            camera.Transform()->SetPosition(cPos.x, cPos.y, cPos.z + speed);
        if (keyPressed == 'a')
            camera.Transform()->SetPosition(cPos.x - speed, cPos.y, cPos.z);
        if (keyPressed == 'd')
            camera.Transform()->SetPosition(cPos.x + speed, cPos.y, cPos.z);
        if (keyPressed == 'q')
            camera.Transform()->SetPosition(cPos.x, cPos.y + speed, cPos.z);
        if (keyPressed == 'e')
            camera.Transform()->SetPosition(cPos.x, cPos.y - speed, cPos.z);

        camera.CameraDraw(window);
        for (int i = 0; i < gameObjects.size(); i++)
        {
            gameObjects[i].GetModel()->Draw(&camera);
        }
       
        keyPressed = 'n';
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}