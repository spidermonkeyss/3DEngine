#include "MovementController.h"
#include "ScriptIncludes.h"

void MovementController::Update()
{
    if (Input::GetKeyHeld(Input::W))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() + (gameobject->Transform()->Forward() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::S))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() - (gameobject->Transform()->Forward() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::A))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() - (gameobject->Transform()->Right() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::D))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() + (gameobject->Transform()->Right() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::Q))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() + (gameobject->Transform()->Up() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::E))
        gameobject->Transform()->SetPosition(gameobject->Transform()->Position() - (gameobject->Transform()->Up() * speed * EngineTime::DeltaTime()));
    if (Input::GetKeyHeld(Input::Z))
        gameobject->Transform()->SetRotation(gameobject->Transform()->Rotation().x, gameobject->Transform()->Rotation().y + turnSpeed * EngineTime::DeltaTime(), gameobject->Transform()->Rotation().z);
    if (Input::GetKeyHeld(Input::X))
        gameobject->Transform()->SetRotation(gameobject->Transform()->Rotation().x, gameobject->Transform()->Rotation().y - turnSpeed * EngineTime::DeltaTime(), gameobject->Transform()->Rotation().z);
}
