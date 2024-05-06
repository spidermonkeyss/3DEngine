#pragma once

static class EngineTime
{
private:
	static double deltaTime;
public:
	inline static double DeltaTime() { return deltaTime; }

private:
	friend class Engine;
	friend class Physics;
};