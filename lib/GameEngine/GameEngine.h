#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <thread>
#include <chrono>
#include <GLAD/glad.h>

#include <EngineCore/Core.h>
#include <EngineCore/Shaders.h>
#include <EngineCore/GameObject.h>
#include <EngineCore/WindowManager.h>

namespace GameEngine
{
    static double targetFPS = 60;
    
    static void clear_bg(float red, float green, float blue, float alpha = 1.0f)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void framerate_limiter()
    {
        if (targetFPS < 1) return;

        static auto lastTime = std::chrono::high_resolution_clock::now();

        double frameTime = 1.0 / targetFPS; // Time per frame in seconds

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;

        if (elapsed.count() < frameTime)
        {
            std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - elapsed.count()));
        }

        lastTime = std::chrono::high_resolution_clock::now();
    }

    static bool isRunning()
    {
        return !WindowManager::ShouldClose();
    }
}

#endif //GAMEENGINE_H