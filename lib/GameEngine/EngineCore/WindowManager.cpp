#include <GLAD/glad.h>
#include "WindowManager.h"

namespace GameEngine
{
    WindowManager::WindowManager() : window(nullptr), windowWidth(800), windowHeight(600)
    {
    }

    GLFWwindow* WindowManager::GetWindowTEMPORARY(bool debug)
    {
        //if (getInstance().window == nullptr && debug) std::cerr << "ERROR::WINDOWMANAGER::WINDOW_NOT_FOUND\n";
        return getInstance().window;
    }

    void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        getInstance().HandleResize(window, width, height);
    }

    void WindowManager::Refresh()
    {
        glfwPollEvents();
        glfwSwapBuffers(getInstance().window);
    }

    bool WindowManager::ShouldClose()
    {
        return glfwWindowShouldClose(getInstance().window);
    }

    int WindowManager::GetHeight()
    {
        return getInstance().windowHeight;
    }

    int WindowManager::GetWidth()
    {
        return getInstance().windowWidth;
    }

    int WindowManager::init(int width, int height, const char* title, bool debug, GLFWmonitor* monitor,
                            GLFWwindow* share)
    {
        if (!glfwInit())
        {
            //std::cerr << "ERROR::GLFW::INITIALIZATION_FAILED\n";
            return -1;
        }
        else if (debug)
        {
            //std::cout << "SUCCESS::GLFW::INITIALIZATION\n";
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        getInstance().window = glfwCreateWindow(width, height, title, monitor, share);

        if (getInstance().window == nullptr)
        {
            //std::cerr << "ERROR::GLFW::WINDOW_CREATION_FAILED\n";
            glfwTerminate();
            return -2;
        }
        else if (debug)
        {
            //std::cout << "SUCCESS::GLFW::WINDOW_CREATION\n";
        }

        glfwMakeContextCurrent(getInstance().window);

        // ReSharper disable once CppCStyleCast
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // NOLINT(clang-diagnostic-cast-function-type-strict)
        {
            //std::cerr << "ERROR::GLAD::INITIALIZATION_FAILED\n";
            return -3;
        }
        else if (debug)
        {
            //std::cout << "SUCCESS::GLAD::INITIALIZATION\n";
        }

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(getInstance().window, WindowManager::framebuffer_size_callback);

        getInstance().windowWidth = width;
        getInstance().windowHeight = height;

        return 0;
    }

    void WindowManager::HandleResize(GLFWwindow* local_window, int width, int height)
    {
        glViewport(0, 0, width, height);
        windowWidth = width;
        windowHeight = height;
    }

    WindowManager& WindowManager::getInstance()
    {
        static WindowManager instance;
        return instance;
    }
}
