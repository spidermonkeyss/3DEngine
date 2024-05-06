#include "Engine.h"

#include "Renderer/Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "EngineTime.h"
#include "Physics.h"
#include "Scene.h"

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

        renderer.Render();
    }

    glfwTerminate();
    return 0;
}