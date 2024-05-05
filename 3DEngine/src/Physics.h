#pragma once
#include "Component/ComponentHandler.h"

static class Physics
{
private:
	static void DoAABBCollisionCheck(BoxCollider* colliderOne, BoxCollider* colliderTwo, Transform* t_one, Transform* t_two);
	static std::map<unsigned int, BoxCollider*> collidiersToResolve;
public:
	static float gravity;

	static void ApplyGravity();
	static void CollisionCheck();
	static void ResolveCollisions();
	static void FinalizePosition();
};