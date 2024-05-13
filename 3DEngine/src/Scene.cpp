#include "Scene.h"
#include "Renderer/Shader.h"

void Scene::LoadMaterials()
{
    Material* m1 = Material::CreateMaterial();
    m1->SetShader("res/shaders/basiclighting.shader");

    Material* m2 = Material::CreateMaterial();
    m2->SetShader("res/shaders/basicTexture.shader");
    m2->SetTexture("u_Texture", "res/textures/Antikythera.png");

    Material* m3 = Material::CreateMaterial();
    m3->SetShader("res/shaders/rgb.shader");
    m3->SetFloat("u_Opacity", 1.0f);
}

void Scene::CreateGameObjects()
{
    GameObject* go;
    BoxCollider* bc;
    Model* model;
    Rigidbody* rb;

    //line 1
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(0));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial(materials.At(0));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial(materials.At(0));

    //line 2
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(1));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial(materials.At(1));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial(materials.At(1));

    //line 3
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(2));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial(materials.At(2));

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial(materials.At(2));

    //misc
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-3.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(0));
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-3.5f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(1));
    go->AddComponent<Rigidbody>();
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-4.0f, 9.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial(materials.At(2));
    go->AddComponent<Rigidbody>();
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-10.0f, 2.5f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial(materials.At(2));
    rb = go->AddComponent<Rigidbody>();
    rb->doGravity = true;
    rb->velocity.x = 10.0f;
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;
}

Scene* Scene::currentScene;

Scene::Scene()
{
}

void Scene::LoadScene(const std::string& filePath)
{
	currentScene = this;
    LoadMaterials();
    CreateGameObjects();
}