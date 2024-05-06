#pragma once
#include "Component/ComponentHandler.h"
#include <vector>

static class Physics
{
private:
	static void DoAABBCollisionCheck(BoxCollider* colliderOne, BoxCollider* colliderTwo, Transform* t_one, Transform* t_two);
	//static std::unordered_map<unsigned int, BoxCollider*> collidiersToResolve;
	static std::vector<BoxCollider*> collidiersToResolve;

	static void ApplyGravity();
	static void CollisionCheck();
	static void ResolveCollisions();
	static void ApplyForces();
	static void FinalizePosition();

	static float gravity;
public:
	inline static float GetPhysicsGravity() { return gravity; }
	inline static float SetPhysicsGravity(float _gravity) { gravity = _gravity; }
private:
	friend class Engine;
};