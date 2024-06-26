#include "Physics.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "Scene.h"

float Physics::gravity = -9.81f;
std::vector<BoxCollider*> Physics::collidiersToResolve;

void Physics::ApplyGravity()
{
	std::unordered_map<unsigned int, Rigidbody>::iterator i;
	for (i = Scene::currentScene->componentHandler.rigidbodyComponents.begin(); i != Scene::currentScene->componentHandler.rigidbodyComponents.end(); ++i)
	{
		Rigidbody* rigidbody = &i->second;
		if (rigidbody->doGravity && rigidbody->isEnabled)
		{
			rigidbody->velocity.y += gravity * EngineTime::deltaTime;
		}
	}
}

void Physics::FinalizePosition()
{
	std::unordered_map<unsigned int, Rigidbody>::iterator i;
	for (i = Scene::currentScene->componentHandler.rigidbodyComponents.begin(); i != Scene::currentScene->componentHandler.rigidbodyComponents.end(); ++i)
	{
		Rigidbody* rigidbody = &i->second;
		if (rigidbody->isEnabled)
		{
			Transform* transform = &rigidbody->gameobject->transform;

			transform->position.x += rigidbody->velocity.x * EngineTime::deltaTime;
			transform->position.y += rigidbody->velocity.y * EngineTime::deltaTime;
			transform->position.z += rigidbody->velocity.z * EngineTime::deltaTime;
		}
	}
}

void Physics::DoAABBCollisionCheck(BoxCollider* colliderOne, BoxCollider* colliderTwo, Transform* t_one, Transform* t_two)
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

	//Collision happens
	if (box2Start.x <= box1End.x && box2End.x >= box1Start.x && box2End.y >= box1Start.y && box2Start.y <= box1End.y && box2Start.z <= box1End.z && box2End.z >= box1Start.z)
	{
		//box 1 faces
		float face0 = abs(box1End.x - box2Start.x);//right
		float face1 = abs(box2End.x - box1Start.x);//left
		float face2 = abs(box1End.y - box2Start.y);//top
		float face3 = abs(box2End.y - box1Start.y);//bot
		float face4 = abs(box1End.z - box2Start.z);//back
		float face5 = abs(box2End.z - box1Start.z);//foward

		float faces[6];
		faces[0] = face0;
		faces[1] = face1;
		faces[2] = face2;
		faces[3] = face3;
		faces[4] = face4;
		faces[5] = face5;

		//get face with least penetration depth
		int leastDepthFace = 0;
		for (int i = 1; i < 6; i++)
		{
			if (faces[i] < faces[leastDepthFace])
			{
				leastDepthFace = i;
			}
		}

		Collision collisionOne;
		collisionOne.otherCollider = colliderTwo;
		collisionOne.penDepth = faces[leastDepthFace];

		Collision collisionTwo;
		collisionTwo.otherCollider = colliderOne;
		collisionTwo.penDepth = faces[leastDepthFace];

		switch (leastDepthFace)
		{
		case 0:
			collisionOne.collisionForceDirection.x = 1.0f;
			collisionTwo.collisionForceDirection.x = -1.0f;
			break;
		case 1:
			collisionOne.collisionForceDirection.x = -1.0f;
			collisionTwo.collisionForceDirection.x = 1.0f;
			break;
		case 2:
			collisionOne.collisionForceDirection.y = 1.0f;
			collisionTwo.collisionForceDirection.y = -1.0f;
			break;
		case 3:
			collisionOne.collisionForceDirection.y = -1.0f;
			collisionTwo.collisionForceDirection.y = 1.0f;
			break;
		case 4:
			collisionOne.collisionForceDirection.z = 1.0f;
			collisionTwo.collisionForceDirection.z = -1.0f;
			break;
		case 5:
			collisionOne.collisionForceDirection.z = -1.0f;
			collisionTwo.collisionForceDirection.z = 1.0f;
			break;
		default:
			std::cout << "\n\nProblem in AABB collision!!!!!!!!\n\n";
		}

		colliderOne->collisions.push_back(collisionOne);
		colliderTwo->collisions.push_back(collisionTwo);

		collidiersToResolve.push_back(colliderOne);
		collidiersToResolve.push_back(colliderTwo);
	}
}

void Physics::CollisionCheck()
{
	collidiersToResolve.clear();

	std::unordered_map<unsigned int, BoxCollider>::iterator i;
	for (i = Scene::currentScene->componentHandler.boxColliderComponents.begin(); i != Scene::currentScene->componentHandler.boxColliderComponents.end(); ++i)
	{
		BoxCollider* colliderOne = &i->second;
		if (colliderOne->isEnabled && !colliderOne->isTrigger)
		{
			Rigidbody* rigidbody = Scene::currentScene->componentHandler.GetComponent<Rigidbody>(i->first);
			if (rigidbody != nullptr)
			{
				if (rigidbody->isEnabled)
				{
					std::unordered_map<unsigned int, BoxCollider>::iterator k;
					for (k = Scene::currentScene->componentHandler.boxColliderComponents.begin(); k != Scene::currentScene->componentHandler.boxColliderComponents.end(); ++k)
					{
						if (k->first != i->first)
						{
							BoxCollider* colliderTwo = &k->second;
							if (colliderTwo->isEnabled)
							{
								//Check if these two have already made a collision
								bool noCollision = true;
								for (int j = 0; j < colliderOne->collisions.size(); j++)
								{
									if (colliderOne->collisions[j].otherCollider == colliderTwo)
										noCollision = false;
								}
								if (noCollision)
								{
									Transform* t_one = &colliderOne->gameobject->transform;
									Transform* t_two = &colliderTwo->gameobject->transform;

									DoAABBCollisionCheck(colliderOne, colliderTwo, t_one, t_two);
								}
							}
						}
					}
				}
			}
		}
	}
}

void Physics::ResolveCollisions()
{
	for (int colliderI = 0; colliderI < collidiersToResolve.size(); colliderI++)
	{
		BoxCollider* bc = collidiersToResolve[colliderI];
		Rigidbody* rb = bc->gameobject->GetComponent<Rigidbody>();

		if (rb != nullptr)
		{
			for (int i = 0; i < bc->collisions.size(); i++)
			{
				Rigidbody* otherRb = bc->collisions[i].otherCollider->gameobject->GetComponent<Rigidbody>();

				Transform* t = &rb->gameobject->transform;

				float x = bc->collisions[i].collisionForceDirection.x;
				float y = bc->collisions[i].collisionForceDirection.y;
				float z = bc->collisions[i].collisionForceDirection.z;

				rb->velocity.x = (x == 0.0f) ? rb->velocity.x : 0.0f;
				rb->velocity.y = (y == 0.0f) ? rb->velocity.y : 0.0f;
				rb->velocity.z = (z == 0.0f) ? rb->velocity.z : 0.0f;
				
				//Both objects have rigidbodys, so only move each half the distance of the penetration depth
				if (otherRb != nullptr)
				{
					if (otherRb->isEnabled)
					{
						t->position.x -= x * bc->collisions[i].penDepth / 2.0f;
						t->position.y -= y * bc->collisions[i].penDepth / 2.0f;
						t->position.z -= z * bc->collisions[i].penDepth / 2.0f;
					}
					else
					{
						t->position.x -= x * bc->collisions[i].penDepth;
						t->position.y -= y * bc->collisions[i].penDepth;
						t->position.z -= z * bc->collisions[i].penDepth;
					}
				}
				//only one object has a rigidbody, so move it full pen depth distacne
				else
				{
					t->position.x -= x * bc->collisions[i].penDepth;
					t->position.y -= y * bc->collisions[i].penDepth;
					t->position.z -= z * bc->collisions[i].penDepth;
				}
			}
		}
		bc->collisions.clear();
	}
}

void Physics::ApplyForces()
{
	std::unordered_map<unsigned int, Rigidbody>::iterator i;
	for (i = Scene::currentScene->componentHandler.rigidbodyComponents.begin(); i != Scene::currentScene->componentHandler.rigidbodyComponents.end(); ++i)
	{
		Rigidbody* rb = &i->second;
	}
}
