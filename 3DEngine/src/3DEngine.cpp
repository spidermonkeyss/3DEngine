#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "EngineTime.h"
#include "Physics.h"

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

void CreateGameObjects(std::vector<Shader>* shaders, std::vector<Mesh>* meshes)
{
    float xSpacing = 3.0f;
    float ySpacing = 3.0f;

    int i = 0;
    for (int shaderIndex = 0; shaderIndex < shaders->size(); shaderIndex++)
    {
        for (int meshIndex = 0; meshIndex < meshes->size(); meshIndex++)
        {
            GameObject* gameObject = GameObject::CreateGameObject();
            gameObject->transform()->SetPosition(meshIndex * xSpacing, shaderIndex * ySpacing, 0.0f);
            Model* model = gameObject->AddComponent<Model>();
            model->SetMesh(&meshes->at(meshIndex));
            model->SetShader(&shaders->at(shaderIndex));

            if (i > 2)
            {
                gameObject->AddComponent<Rigidbody>();
                gameObject->transform()->SetPosition(meshIndex * xSpacing + 0.3f, shaderIndex * ySpacing, 0.0f);
            }

            if (i == 0 || i == 3)
            {
                BoxCollider* bc = gameObject->AddComponent<BoxCollider>();
                bc->lengths.x = 2.0f;
                bc->lengths.y = 2.0f;
                bc->lengths.z = 2.0f;
            }

            i++;
        }
    }

    GameObject* gameObject = GameObject::CreateGameObject();
    gameObject->transform()->SetPosition(0.5f, shaders->size() * ySpacing, 0.0f);
    Model* model = gameObject->AddComponent<Model>();
    model->SetMesh(&meshes->at(1));
    model->SetShader(&shaders->at(1));
    gameObject->AddComponent<Rigidbody>();
    BoxCollider* bc = gameObject->AddComponent<BoxCollider>();
    bc->lengths.x = 3.0f;
    bc->lengths.y = 3.0f;
    bc->lengths.z = 3.0f;

    GameObject* gameObject2 = GameObject::CreateGameObject();
    gameObject2->transform()->SetPosition(-6.0f, 2.5f, 0.0f);
    Model* model2 = gameObject2->AddComponent<Model>();
    model2->SetMesh(&meshes->at(0));
    model2->SetShader(&shaders->at(1));
    Rigidbody* rb2 = gameObject2->AddComponent<Rigidbody>();
    rb2->doGravity = false;
    BoxCollider* bc2 = gameObject2->AddComponent<BoxCollider>();
    bc2->lengths.x = 2.0f;
    bc2->lengths.y = 2.0f;
    bc2->lengths.z = 2.0f;
}

int main(void)
{
    Renderer renderer;
    renderer.Init();

    Camera camera;
    camera.Transform()->SetPosition(0.0f, 0.0f, 16.0f);

    renderer.SetCamera(&camera);

    std::vector<Shader> shaders = LoadShaders("res/Shaders/");
    std::vector<Mesh> meshes = LoadMeshes("res/Meshes/");
    CreateGameObjects(&shaders, &meshes);

    double currentFrameTime = 0;
    double prevFrameTime = glfwGetTime();
    EngineTime::deltaTime = 0;
    while (!renderer.shouldWindowClose)
    {
        currentFrameTime = glfwGetTime();
        EngineTime::deltaTime = currentFrameTime - prevFrameTime;
        prevFrameTime = currentFrameTime;

        Physics::ApplyGravity();
        Physics::CollisionCheck();

        float speed = 0.5f;
        Vector3 cPos = camera.Transform()->position;

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

        {
            GameObject* sideMovingGO = GameObject::GetGameObjectByObjectId(GameObject::GetNextObjectId() - 1);
            Rigidbody* rb = sideMovingGO->GetComponent<Rigidbody>();
            rb->velocity.x = 5.0f;
        }

        Physics::ResolveCollisions();
        Physics::FinalizePosition();

        renderer.Render();
    }

    glfwTerminate();
    return 0;
}