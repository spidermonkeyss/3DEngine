#include "Scene.h"

#include <filesystem>
std::vector<Texture> LoadTextures(const std::string& filePath)
{
    std::vector<Texture> textures;
    bool isLoaded = false;

    if (std::filesystem::exists(filePath))
    {
        for (const auto& entry : std::filesystem::directory_iterator(filePath))
        {
            std::cout << "Trying to load texture at: " << entry.path() << std::endl;
            Texture texture;
            isLoaded = texture.LoadTextureFile(entry.path().generic_string());
            if (isLoaded)
                textures.push_back(texture);
        }
    }

    std::cout << textures.size() << " textures loaded" << std::endl;
    return textures;
}

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

void Scene::LoadMaterials()
{
    Material m1;
    m1.SetShader(&shaders[0]);
    materials.push_back(m1);

    Material m2;
    m2.SetShader(&shaders[1]);
    m2.SetTexture("u_Texture", &textures[0]);
    materials.push_back(m2);

    Material m3;
    m3.SetShader(&shaders[2]);
    m3.SetFloat("opacity", 1.0f);
    materials.push_back(m3);
}

void Scene::CreateGameObjects(std::vector<Shader>* shaders, std::vector<Mesh>* meshes)
{
    float xSpacing = 3.0f;
    float ySpacing = 3.0f;

    int i = 0;
    for (int shaderIndex = 0; shaderIndex < shaders->size(); shaderIndex++)
    {
        for (int meshIndex = 0; meshIndex < meshes->size(); meshIndex++)
        {
            GameObject* gameObject = GameObject::CreateGameObject();
            gameObject->transform.SetPosition(meshIndex * xSpacing, shaderIndex * ySpacing, 0.0f);
            Model* model = gameObject->AddComponent<Model>();
            model->SetMesh(&meshes->at(meshIndex));
            model->SetMaterial(&materials.at(shaderIndex));

            if (shaderIndex > 0)
            {
                gameObject->AddComponent<Rigidbody>();
                gameObject->transform.SetPosition(meshIndex * xSpacing + 0.3f, shaderIndex * ySpacing, 0.0f);
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
    gameObject->transform.SetPosition(0.5f, shaders->size() * ySpacing, 0.0f);
    Model* model = gameObject->AddComponent<Model>();
    model->SetMesh(&meshes->at(1));
    model->SetMaterial(&materials.at(2));
    gameObject->AddComponent<Rigidbody>();
    BoxCollider* bc = gameObject->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    GameObject* gameObject2 = GameObject::CreateGameObject();
    gameObject2->transform.SetPosition(-10.0f, 2.5f, 0.0f);
    Model* model2 = gameObject2->AddComponent<Model>();
    model2->SetMesh(&meshes->at(0));
    model2->SetMaterial(&materials.at(2));
    Rigidbody* rb2 = gameObject2->AddComponent<Rigidbody>();
    rb2->doGravity = true;
    rb2->velocity.x = 10.0f;
    BoxCollider* bc2 = gameObject2->AddComponent<BoxCollider>();
    bc2->lengths.x = 2.0f;
    bc2->lengths.y = 2.0f;
    bc2->lengths.z = 2.0f;
}

Scene* Scene::currentScene;

Scene::Scene()
{
}

void Scene::LoadScene(const std::string& filePath)
{
	currentScene = this;
    textures = LoadTextures("res/textures/");
    shaders = LoadShaders("res/Shaders/");
    meshes = LoadMeshes("res/Meshes/");
    LoadMaterials();
    CreateGameObjects(&shaders, &meshes);
}