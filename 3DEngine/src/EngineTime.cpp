#include "EngineTime.h"
#include "Window/Window.h"

double EngineTime::deltaTime = 0;
double EngineTime::currentFrameTime = 0;
double EngineTime::prevFrameTime = 0;

void EngineTime::Init()
{
    double currentFrameTime = 0;
    double prevFrameTime = Window::currentWindow->GetTime();
    EngineTime::deltaTime = 0;
}

void EngineTime::Update()
{
    currentFrameTime = Window::currentWindow->GetTime();
    EngineTime::deltaTime = currentFrameTime - prevFrameTime;
    prevFrameTime = currentFrameTime;
}