#include "Engine.h"

#include "Renderer/Renderer.h"
#include "GameObject.h"
//#include "Camera.h"
#include "EngineTime.h"
#include "Physics.h"
#include "Scene.h"
#include "LinkedList.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

void Engine::IMGUI_ShowMesh(Mesh* mesh)
{
    if (ImGui::TreeNodeEx(("FilePath: " + mesh->filePath).c_str(), 0))
    {
        ImGui::Text(("Vertex Buffer Id: " + std::to_string(mesh->gl_VertexArrayId)).c_str());
        ImGui::Text(("Vertex count: " + std::to_string(mesh->vertexCount)).c_str());
        for (int i = 0; i < mesh->vertexAttributeLayouts.size(); i++)
        {
            std::string text = "Attribute " + std::to_string(i) + ": Count " + std::to_string(mesh->vertexAttributeLayouts[i].count) + ", type size " + std::to_string(mesh->vertexAttributeLayouts[i].typeByteSize);
            ImGui::Text(text.c_str());
        }
        ImGui::TreePop();
    }
}

void Engine::IMGUI_ShowShader(Shader* shader)
{
    if (ImGui::TreeNodeEx(("FilePath: " + shader->filePath).c_str(), 0))
    {
        ImGui::Text(("Shader Id: " + std::to_string(shader->gl_ShaderId)).c_str());
        for (std::unordered_map<std::string, Shader::ShaderProperity>::iterator sp = shader->attributies.begin(); sp != shader->attributies.end(); ++sp)
        {
            std::string text = "Attribute " + std::to_string(sp->second.location) + " : " + sp->first;
            ImGui::Text(text.c_str());
        }
        for (std::unordered_map<std::string, Shader::ShaderProperity>::iterator sp = shader->uniforms.begin(); sp != shader->uniforms.end(); ++sp)
        {
            std::string text = "Uniform " + std::to_string(sp->second.location) + " : " + sp->first;
            ImGui::Text(text.c_str());
        }
        ImGui::TreePop();
    }
}

void Engine::IMGUI_ShowTexture(Texture* texture)
{
    ImGui::Text(("FilePath: " + texture->filePath).c_str());
}

void Engine::IMGUI_ShowMaterial(Material* material)
{
    if (ImGui::TreeNodeEx(("Material " + std::to_string(material->id)).c_str(), 0))
    {
        ImGui::Text(("FilePath: " + material->filePath).c_str());
        ImGui::Text(("Shader: " + material->shader->filePath).c_str());

        if (ImGui::TreeNodeEx("Properties", 0))
        {
            for (std::unordered_map<std::string, Texture*>::iterator i = material->textures.begin(); i != material->textures.end(); ++i)
                ImGui::Text((i->first + ": " + i->second->filePath).c_str());
            for (std::unordered_map<std::string, int>::iterator i = material->ints.begin(); i != material->ints.end(); ++i)
                ImGui::Text((i->first + ": " + std::to_string(i->second)).c_str());
            for (std::unordered_map<std::string, float>::iterator i = material->floats.begin(); i != material->floats.end(); ++i)
                ImGui::Text((i->first + ": " + std::to_string(i->second)).c_str());
            for (std::unordered_map<std::string, float[2]>::iterator i = material->float2s.begin(); i != material->float2s.end(); ++i)
                ImGui::Text((i->first + ": " + std::to_string(i->second[0]) + ", " + std::to_string(i->second[1])).c_str());
            for (std::unordered_map<std::string, float[3]>::iterator i = material->float3s.begin(); i != material->float3s.end(); ++i)
                ImGui::Text((i->first + ": " + std::to_string(i->second[0]) + ", " + std::to_string(i->second[1]) + ", " + std::to_string(i->second[2])).c_str());
            for (std::unordered_map<std::string, float[4]>::iterator i = material->float4s.begin(); i != material->float4s.end(); ++i)
                ImGui::Text((i->first + ": " + std::to_string(i->second[0]) + ", " + std::to_string(i->second[1]) + ", " + std::to_string(i->second[2]) + ", " + std::to_string(i->second[3])).c_str());
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

void Engine::RunImGuiFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();

    ImGui::ShowDemoWindow();
    ImGui::ShowMetricsWindow();
	ImGui::Text("Scene");

    if (ImGui::TreeNodeEx("Camera", 0))
    {
        float rot[3] = { Renderer::currentRenderer->camera->gameobject->transform.rotation.x, Renderer::currentRenderer->camera->gameobject->transform.rotation.y, Renderer::currentRenderer->camera->gameobject->transform.rotation.z };
        ImGui::InputFloat3("Rot", &rot[0]);
        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Meshes", 0))
    {
        for (LinkedList<Mesh>::Iterator i = Scene::currentScene->meshes.Begin(); i != Scene::currentScene->meshes.End(); ++i)
            IMGUI_ShowMesh(i.Data());
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Shaders", 0))
    {
        for (LinkedList<Shader>::Iterator i = Scene::currentScene->shaders.Begin(); i != Scene::currentScene->shaders.End(); ++i)
            IMGUI_ShowShader(i.Data());
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Textures", 0))
    {
        for (LinkedList<Texture>::Iterator i = Scene::currentScene->textures.Begin(); i != Scene::currentScene->textures.End(); ++i)
            IMGUI_ShowTexture(i.Data());
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Materials", 0))
    {
        for (LinkedList<Material>::Iterator i = Scene::currentScene->materials.Begin(); i != Scene::currentScene->materials.End(); ++i)
            IMGUI_ShowMaterial(i.Data());
        ImGui::TreePop();
    }


    //List GameObjects
    if (ImGui::TreeNodeEx("GameOebjcts", 0))
    {
        std::unordered_map<unsigned int, std::unique_ptr<GameObject>>::iterator i;
        for (i = Scene::currentScene->gameObjects.begin(); i != Scene::currentScene->gameObjects.end(); ++i)
        {
            GameObject* go = i->second.get();
            std::string text = "ID: " + std::to_string(go->objectId);
            if (ImGui::TreeNodeEx(text.c_str(), 0))
            {
                float pos[3] = { go->transform.position.x, go->transform.position.y, go->transform.position.z };
                ImGui::InputFloat3("Position", &pos[0]);

                //Model
                Model* model = go->GetComponent<Model>();
                if (model)
                {
                    if (ImGui::TreeNodeEx("Model", 0))
                    {
                        IMGUI_ShowMesh(model->mesh);
                        IMGUI_ShowMaterial(model->material);
                        ImGui::TreePop();
                    }
                }
                //Rigidbody
                Rigidbody* rigidbody = go->GetComponent<Rigidbody>();
                if (rigidbody)
                {
                    if (ImGui::TreeNodeEx("Rigidbody", 0))
                    {
                        ImGui::TreePop();
                    }
                }
                //BoxCollider
                BoxCollider* boxCollider = go->GetComponent<BoxCollider>();
                if (boxCollider)
                {
                    if (ImGui::TreeNodeEx("BoxCollider", 0))
                    {
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Render();

	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

int Engine::RunEngine()
{
    Window window;
    window.Init();

    Renderer renderer;
    renderer.currentRenderer = &renderer;
    renderer.window = &window;

    Scene scene;
    scene.LoadScene("");

    EngineTime::Init();

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window.glfw_window, false);
    ImGui::StyleColorsDark();

    while (!window.shouldWindowClose)
    {
        EngineTime::Update();

        Physics::ApplyGravity();
        Physics::CollisionCheck();

        scene.UpdateScripts();

        Physics::ResolveCollisions();
        //Physics::ApplyForces();
        Physics::FinalizePosition();

        Input::SetDownKeysToHeld();
        Input::ClearReleasedKeys();
        window.Clear();
        renderer.Render();
        RunImGuiFrame();
        window.SwapBuffer();
        window.PollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    window.Terminate();
    return 0;
}