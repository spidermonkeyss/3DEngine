#include "Engine.h"

#include "Renderer/Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "EngineTime.h"
#include "Physics.h"
#include "Scene.h"

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

void Engine::RunImGuiFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();

    ImGui::ShowDemoWindow();
    ImGui::ShowMetricsWindow();
	ImGui::Text("Scene");

    //List GameObjects
    ImGuiTreeNodeFlags open = ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx("GameOebjcts", open))
    {
        std::unordered_map<unsigned int, std::unique_ptr<GameObject>>::iterator i;
        for (i = Scene::currentScene->gameObjects.begin(); i != Scene::currentScene->gameObjects.end(); ++i)
        {
            GameObject* go = i->second.get();
            std::string text = std::to_string(go->objectId);
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
                        ImGui::Checkbox("Enabled", &model->isEnabled);
                        {
                            std::unordered_map<std::string, Texture*>::iterator i;
                            for (i = model->material->textures.begin(); i != model->material->textures.end(); ++i)
                            {
                                ImGui::Text((i->first + ": " + i->second->fileName).c_str());
                            }
                        }
                        {
                            std::unordered_map<std::string, int>::iterator i;
                            for (i = model->material->ints.begin(); i != model->material->ints.end(); ++i)
                            {
                                ImGui::Text((i->first + std::to_string(i->second)).c_str());
                            }
                        }
                        {
                            std::unordered_map<std::string, float>::iterator i;
                            for (i = model->material->floats.begin(); i != model->material->floats.end(); ++i)
                            {
                         
                            }
                        }

                        {
                            std::unordered_map<std::string, float[2]>::iterator i;
                            for (i = model->material->float2s.begin(); i != model->material->float2s.end(); ++i)
                            {

                            }
                        }

                        {
                            std::unordered_map<std::string, float[3]>::iterator i;
                            for (i = model->material->float3s.begin(); i != model->material->float3s.end(); ++i)
                            {

                            }
                        }

                        {
                            std::unordered_map<std::string, float[4]>::iterator i;
                            for (i = model->material->float4s.begin(); i != model->material->float4s.end(); ++i)
                            {

                            }
                        }

                        ImGui::TreePop();
                    }
                }
                //Rigidbody
                Rigidbody* rigidbody = go->GetComponent<Rigidbody>();
                if (rigidbody)
                {
                    if (ImGui::TreeNodeEx("Rigidbody", 0))
                    {
                        ImGui::Checkbox("Enabled", &rigidbody->isEnabled);
                        ImGui::TreePop();
                    }
                }
                //BoxCollider
                BoxCollider* boxCollider = go->GetComponent<BoxCollider>();
                if (boxCollider)
                {
                    if (ImGui::TreeNodeEx("BoxCollider", 0))
                    {
                        ImGui::Checkbox("Enabled", &boxCollider->isEnabled);
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
    Renderer renderer;
    renderer.Init();

    Scene scene;
    scene.LoadScene("");

    Camera camera;
    camera.transform.SetPosition(0.0f, 0.0f, 16.0f);

    renderer.SetCamera(&camera);

    double currentFrameTime = 0;
    double prevFrameTime = glfwGetTime();
    EngineTime::deltaTime = 0;
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(renderer.window, false);
    ImGui::StyleColorsDark();
    
    while (!renderer.shouldWindowClose)
    {
        currentFrameTime = glfwGetTime();
        EngineTime::deltaTime = currentFrameTime - prevFrameTime;
        prevFrameTime = currentFrameTime;

        Physics::ApplyGravity();
        Physics::CollisionCheck();

        float speed = 0.5f;
        Vector3 cPos = camera.transform.position;

        if (Renderer::keyPressed == 'w')
            camera.transform.SetPosition(cPos.x, cPos.y, cPos.z - speed);
        if (Renderer::keyPressed == 's')
            camera.transform.SetPosition(cPos.x, cPos.y, cPos.z + speed);
        if (Renderer::keyPressed == 'a')
            camera.transform.SetPosition(cPos.x - speed, cPos.y, cPos.z);
        if (Renderer::keyPressed == 'd')
            camera.transform.SetPosition(cPos.x + speed, cPos.y, cPos.z);
        if (Renderer::keyPressed == 'q')
            camera.transform.SetPosition(cPos.x, cPos.y + speed, cPos.z);
        if (Renderer::keyPressed == 'e')
            camera.transform.SetPosition(cPos.x, cPos.y - speed, cPos.z);
        Renderer::keyPressed = 'n';

        Physics::ResolveCollisions();
        //Physics::ApplyForces();
        Physics::FinalizePosition();

        renderer.Clear();
        renderer.Render();
        RunImGuiFrame();
        renderer.SwapBuffer();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}