#pragma once

static class Physics
{
private:
	static void ApplyGravity();
	static void CheckCollisions();
	static void ApplyCollisionForces();
	static void FinalizePosition();
public:
	static float gravity;


	static void Update();
};