#include "CameraController.h"
#include "ScriptIncludes.h"

void CameraController::OnStart()
{
}

void CameraController::Update()
{
    gameobject->Transform()->SetPosition(gameObjectToFollow->Transform()->Position().x, gameObjectToFollow->Transform()->Position().y, gameObjectToFollow->Transform()->Position().z + 25.0f);
    gameobject->Transform()->SetRotation(gameObjectToFollow->Transform()->Rotation());
}