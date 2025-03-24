#pragma once
#ifndef WINDOWMGR_H
#define WINDOWMGR_H

#include <GLFW/glfw3.h>

namespace GameEngine
{
    class WindowManager
    {
    public:
        static GLFWwindow* GetWindowTEMPORARY(bool debug = false);

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void Refresh();
        static bool ShouldClose();
        static int GetHeight();
        static int GetWidth();

        static int init(int width, int height, const char* title, bool debug = false, GLFWmonitor* monitor = nullptr,
                        GLFWwindow* share = nullptr);

        WindowManager(const WindowManager&) = delete;
        void operator =(const WindowManager&) = delete;

        WindowManager(WindowManager&&) noexcept = default;
        WindowManager& operator=(WindowManager&&) noexcept = default;

        ~WindowManager() = default;

    private:
        WindowManager();

        GLFWwindow* window;
        int windowWidth;
        int windowHeight;

        void HandleResize(GLFWwindow* local_window, int width, int height);
        static WindowManager& getInstance();
    };
}

#undef WINDOWMGR_H
#endif
