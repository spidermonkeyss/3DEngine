#include "Physics.h"
#include "Component/ComponentHandler.h"
#include "Component/Rigidbody.h"
#include "Component/Transform.h"
#include "EngineTime.h"

float Physics::gravity = -9.81f;

void Physics::ApplyGravity()
{
	std::map<unsigned int, Rigidbody>::iterator i;
	for (i = ComponentHandler::GetRigidbodyComponents()->begin(); i != ComponentHandler::GetRigidbodyComponents()->end(); ++i)
	{
		Rigidbody* rigidbody = ComponentHandler::GetComponentUnsafe<Rigidbody>(i->first);
		if (rigidbody->doGravity && rigidbody->isEnabled)
		{
			rigidbody->velocity.y += gravity * EngineTime::deltaTime;
		}
	}
}

bool DoAABBCollisionCheck(BoxCollider* colliderOne, BoxCollider* colliderTwo, Transform* t_one, Transform* t_two)
{
	Vector3 box1Start;
	Vector3 box1End;
	Vector3 box2Start;
	Vector3 box2End;

	box1Start.x = t_one->position.x + colliderOne->offset.x - (colliderOne->lengths.x / 2.0f);
	box1Start.y = t_one->position.y + colliderOne->offset.y - (colliderOne->lengths.y / 2.0f);
	box1Start.z = t_one->position.z + colliderOne->offset.z - (colliderOne->lengths.z / 2.0f);

	box1End.x = t_one->position.x + colliderOne->offset.x + (colliderOne->lengths.x / 2.0f);
	box1End.y = t_one->position.y + colliderOne->offset.y + (colliderOne->lengths.y / 2.0f);
	box1End.z = t_one->position.z + colliderOne->offset.z + (colliderOne->lengths.z / 2.0f);


	box2Start.x = t_two->position.x + colliderTwo->offset.x - (colliderTwo->lengths.x / 2.0f);
	box2Start.y = t_two->position.y + colliderTwo->offset.y - (colliderTwo->lengths.y / 2.0f);
	box2Start.z = t_two->position.z + colliderTwo->offset.z - (colliderTwo->lengths.z / 2.0f);

	box2End.x = t_two->position.x + colliderTwo->offset.x + (colliderTwo->lengths.x / 2.0f);
	box2End.y = t_two->position.y + colliderTwo->offset.y + (colliderTwo->lengths.y / 2.0f);
	box2End.z = t_two->position.z + colliderTwo->offset.z + (colliderTwo->lengths.z / 2.0f);

	if (box2Start.x <= box1End.x && box2End.x >= box1Start.x && box2End.y >= box1Start.y && box2Start.y <= box1End.y && box2Start.z <= box1End.z && box2End.z >= box1Start.z)
		return true;
	return false;

}

void Physics::CheckCollisions()
{
	std::map<unsigned int, BoxCollider>::iterator i;
	for (i = ComponentHandler::GetBoxColliderComponents()->begin(); i != ComponentHandler::GetBoxColliderComponents()->end(); ++i)
	{
		BoxCollider* colliderOne = ComponentHandler::GetComponentUnsafe<BoxCollider>(i->first);
		if (colliderOne->isEnabled && !colliderOne->isTrigger)
		{
			Rigidbody* rigidbody = ComponentHandler::GetComponent<Rigidbody>(i->first);
			if (rigidbody != nullptr)
			{
				if (rigidbody->isEnabled)
				{
					std::map<unsigned int, BoxCollider>::iterator k;
					for (k = ComponentHandler::GetBoxColliderComponents()->begin(); k != ComponentHandler::GetBoxColliderComponents()->end(); ++k)
					{
						if (k->first != i->first)
						{
							BoxCollider* colliderTwo = ComponentHandler::GetComponentUnsafe<BoxCollider>(k->first);

							Transform* t_one = ComponentHandler::GetComponentUnsafe<Transform>(i->first);
							Transform* t_two = ComponentHandler::GetComponentUnsafe<Transform>(k->first);
							bool collision = DoAABBCollisionCheck(colliderOne, colliderTwo, t_one, t_two);
							if (collision)
							{
								int i = 0;
							}
						}
					}
				}
			}
		}
	}
}

void Physics::ApplyCollisionForces()
{

}

void Physics::FinalizePosition()
{
	std::map<unsigned int, Rigidbody>::iterator i;
	for (i = ComponentHandler::GetRigidbodyComponents()->begin(); i != ComponentHandler::GetRigidbodyComponents()->end(); ++i)
	{
		Rigidbody* rigidbody = ComponentHandler::GetComponentUnsafe<Rigidbody>(i->first);
		if (rigidbody->isEnabled)
		{
			Transform* transform = ComponentHandler::GetComponentUnsafe<Transform>(i->first);

			transform->position.x += rigidbody->velocity.x * EngineTime::deltaTime;
			transform->position.y += rigidbody->velocity.y * EngineTime::deltaTime;
			transform->position.z += rigidbody->velocity.z * EngineTime::deltaTime;
		}
	}
}

void Physics::Update()
{
	ApplyGravity();
	CheckCollisions();
	ApplyCollisionForces();
	FinalizePosition();
}
