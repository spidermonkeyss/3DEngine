#pragma once

static class EngineTime
{
private:
	static double currentFrameTime;
	static double prevFrameTime;
	static double deltaTime;
	static void Init();
	static void Update();

public:
	inline static double DeltaTime() { return deltaTime; }

private:
	friend class Engine;
	friend class Physics;
};