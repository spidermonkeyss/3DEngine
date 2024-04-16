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
    camera.Transform()->SetPosition(0.0f, 0.0f, 0.0f);

    Mesh cubeMesh;
    cubeMesh.LoadMeshFile("res/Meshes/cube.obj");
    
    Mesh monkeyMesh;
    monkeyMesh.LoadMeshFile("res/Meshes/monkey.obj");

    Mesh smoothMonkeyMesh;
    smoothMonkeyMesh.LoadMeshFile("res/meshes/smoothmonkey.obj");

    Shader rgbShader;
    rgbShader.LoadShaderFile("res/shaders/rgb.shader");

    Shader basicLightingShader;
    basicLightingShader.LoadShaderFile("res/shaders/basiclighting.shader");
    
    GameObject cubeGO;
    cubeGO.AddModel();
    cubeGO.GetModel()->SetMesh(&cubeMesh);
    cubeGO.GetModel()->SetShader(&rgbShader);
    cubeGO.Transform()->SetPosition(0.0f, 0.0f, -5.0f);

    GameObject rgbMonkeyGO;
    rgbMonkeyGO.AddModel();
    rgbMonkeyGO.GetModel()->SetMesh(&monkeyMesh);
    rgbMonkeyGO.GetModel()->SetShader(&rgbShader);
    rgbMonkeyGO.Transform()->SetPosition(3.0f, 0, -5.0f);

    GameObject go2;
    go2.AddModel();
    go2.GetModel()->SetMesh(&smoothMonkeyMesh);
    go2.GetModel()->SetShader(&rgbShader);
    go2.Transform()->SetPosition(6.0f, 0, -5.0f);

    GameObject go1;
    go1.AddModel();
    go1.GetModel()->SetMesh(&cubeMesh);
    go1.GetModel()->SetShader(&basicLightingShader);
    go1.Transform()->SetPosition(0.0f, 3.0f, -5.0f);

    GameObject monkeyGO;
    monkeyGO.AddModel();
    monkeyGO.GetModel()->SetMesh(&monkeyMesh);
    monkeyGO.GetModel()->SetShader(&basicLightingShader);
    monkeyGO.Transform()->SetPosition(3.0f, 3.0f, -5.0f);

    GameObject smoothMonkeyGO;
    smoothMonkeyGO.AddModel();
    smoothMonkeyGO.GetModel()->SetMesh(&smoothMonkeyMesh);
    smoothMonkeyGO.GetModel()->SetShader(&basicLightingShader);
    smoothMonkeyGO.Transform()->SetPosition(6.0f, 3.0f, -5.0f);

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
        go1.GetModel()->Draw(&camera);
        go2.GetModel()->Draw(&camera);
        cubeGO.GetModel()->Draw(&camera);
        rgbMonkeyGO.GetModel()->Draw(&camera);
        monkeyGO.GetModel()->Draw(&camera);
        smoothMonkeyGO.GetModel()->Draw(&camera);

        keyPressed = 'n';
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}