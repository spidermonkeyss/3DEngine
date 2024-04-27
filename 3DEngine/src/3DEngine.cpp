#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

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
            gameObjects->at(i).AddComponent<Transform>();
            gameObjects->at(i).GetComponentUnsafe<Transform>()->SetPosition(meshIndex * xSpacing, shaderIndex * ySpacing, 0.0f);
            gameObjects->at(i).AddComponent<Model>();
            gameObjects->at(i).GetComponentUnsafe<Model>()->SetMesh(&meshes->at(meshIndex));
            gameObjects->at(i).GetComponentUnsafe<Model>()->SetShader(&shaders->at(shaderIndex));
            i++;
        }
    }

    std::cout << gameObjects->size() << " GameObjects created" << std::endl;
}

int main(void)
{
    Renderer renderer;
    renderer.Init();

    Camera camera;
    camera.Transform()->SetPosition(0.0f, 0.0f, 5.0f);

    renderer.SetCamera(&camera);

    std::vector<Shader> shaders = LoadShaders("res/Shaders/");
    std::vector<Mesh> meshes = LoadMeshes("res/Meshes/");

    std::vector<GameObject> gameObjects;
    CreateGameObjects(&gameObjects, &shaders, &meshes);

    double prevFrameTime = glfwGetTime();
    double deltaTime = 0;
    while (!renderer.shouldWindowClose)
    {
        deltaTime = glfwGetTime() - prevFrameTime;

        float speed = 0.5f;
        Vector3 cPos = camera.Transform()->Position();

        if (Renderer::keyPressed == 'w')
            camera.Transform()->SetPosition(cPos.x, cPos.y, cPos.z - speed);
        if (Renderer::keyPressed == 's')
            camera.Transform()->SetPosition(cPos.x, cPos.y, cPos.z + speed);
        if (Renderer::keyPressed == 'a')
            camera.Transform()->SetPosition(cPos.x - speed, cPos.y, cPos.z);
        if (Renderer::keyPressed == 'd')
            camera.Transform()->SetPosition(cPos.x + speed, cPos.y, cPos.z);
        if (Renderer::keyPressed == 'q')
            camera.Transform()->SetPosition(cPos.x, cPos.y + speed, cPos.z);
        if (Renderer::keyPressed == 'e')
            camera.Transform()->SetPosition(cPos.x, cPos.y - speed, cPos.z);
        Renderer::keyPressed = 'n';

        renderer.Render();
    }

    glfwTerminate();
    return 0;
}