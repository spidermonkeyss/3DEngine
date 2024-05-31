#include "MovementController.h"
#include "ScriptIncludes.h"

void MovementController::Update()
{
	if (Input::GetKeyHeld(Input::W))
	{
		printf("w");
		gameobject->GetComponent<Rigidbody>();
		gameobject->Transform()->SetPosition(0, 1.5f, 0);
	}
}
