#include "Renderer.h"
#include "GLCall.h"
#include "Component/ComponentHandler.h"
#include "GameObject.h"
#include "Scene.h"

Renderer* Renderer::currentRenderer = nullptr;

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

    Transform* transform = &model->gameobject->transform;

    glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform->position.x, transform->position.y, transform->position.z));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
              rotationMatrix = glm::rotate(rotationMatrix, transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
              rotationMatrix = glm::rotate(rotationMatrix, transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(transform->scale.x, transform->scale.y, transform->scale.z));

    glm::mat4 transformMatrix = positionMatrix * rotationMatrix * scaleMatrix;

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

void Renderer::SetCamera(Camera* _camera)
{
    camera = _camera;
}

void Renderer::Render()
{
    if (camera != nullptr)
    {
        projectionMatrix = glm::perspective(45.0f, (float)window->width / (float)window->height, 0.1f, 150.0f);
        
        glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(camera->gameobject->transform.position.x, camera->gameobject->transform.position.y, camera->gameobject->transform.position.z));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), camera->gameobject->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                  rotationMatrix = glm::rotate(rotationMatrix, camera->gameobject->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                  rotationMatrix = glm::rotate(rotationMatrix, camera->gameobject->transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        viewMatrix = glm::inverse(positionMatrix * rotationMatrix);

        std::unordered_map<unsigned int, Model>::iterator i;
        for (i = Scene::currentScene->componentHandler.modelComponents.begin(); i != Scene::currentScene->componentHandler.modelComponents.end(); ++i)
            DrawModel(i->first);
    }
}

