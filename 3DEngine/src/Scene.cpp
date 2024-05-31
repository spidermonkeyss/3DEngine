#include "Scene.h"
#include "Renderer/Shader.h"

Scene* Scene::currentScene;

Material* Scene::CreateMaterial()
{
    materials.PushBack(new Material());
    return materials.Back();
}

Mesh* Scene::CreateMesh()
{
    meshes.PushBack(new Mesh());
    return meshes.Back();
}

Shader* Scene::CreateShader()
{
    shaders.PushBack(new Shader());
    return shaders.Back();
}

Texture* Scene::CreateTexture()
{
    textures.PushBack(new Texture());
    return textures.Back();
}

void Scene::UpdateScripts()
{
    scriptHandler.CallScriptUpdates();
}

void Scene::LoadScene(const std::string& filePath)
{
	currentScene = this;

    GameObject* go;
    BoxCollider* bc;
    Model* model;
    Rigidbody* rb;

    //line 1
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat1.bmat");
    MovementController* mc = go->AddScript<MovementController>();

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial("res/materials/mat1.bmat");

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial("res/materials/mat1.bmat");

    //line 2
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat2.bmat");

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial("res/materials/mat2.bmat");

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial("res/materials/mat2.bmat");

    //line 3
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(0.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat3.bmat");

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(3.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial("res/materials/mat3.bmat");

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(6.0f, 6.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/smoothmonkey.obj");
    model->SetMaterial("res/materials/mat3.bmat");

    //misc
    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-3.0f, 0.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat1.bmat");
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-3.5f, 3.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat2.bmat");
    go->AddComponent<Rigidbody>();
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-4.0f, 9.0f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/monkey.obj");
    model->SetMaterial("res/materials/mat3.bmat");
    go->AddComponent<Rigidbody>();
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;

    go = GameObject::CreateGameObject();
    go->transform.SetPosition(-10.0f, 2.5f, 0.0f);
    model = go->AddComponent<Model>();
    model->SetMesh("res/meshes/cube.obj");
    model->SetMaterial("res/materials/mat3.bmat");
    rb = go->AddComponent<Rigidbody>();
    rb->doGravity = true;
    rb->velocity.x = 10.0f;
    bc = go->AddComponent<BoxCollider>();
    bc->lengths.x = 2.0f;
    bc->lengths.y = 2.0f;
    bc->lengths.z = 2.0f;
}