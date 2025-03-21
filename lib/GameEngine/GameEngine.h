#pragma once

#include "Shaders.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <list>

namespace GameEngine
{
    static GLFWwindow* window;
    static bool updateObjects = true;
    static int windowWidth = 800;
    static int windowHeight = 600;
    static double targetFPS = 60;

    struct vector3
    {
    public:
        float x, y, z;

        vector3()
        {
            x = y = z = 0.0f;
        }

        vector3(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        vector3 operator+(const vector3& _other) const
        {
            return {x + _other.x, y + _other.y, z + _other.z};
        }

        vector3& operator+=(const vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        float magnitude() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }
    };

    struct Color
    {
    public:
        float r, g, b, a = 1.0f;
    };

    struct Transform
    {
    public:
        vector3 position = vector3();
        vector3 rotation = vector3();
        vector3 scale = vector3(1, 1, 1);
    };

    static bool isRunning() { return !glfwWindowShouldClose(window); }

    static void clear_bg(float red, float green, float blue, float alpha = 1.0f)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void refresh()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
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

    static void framebuffer_size_callback(GLFWwindow* local_window, int width, int height)
    {
        glViewport(0, 0, width, height);
        windowWidth = width;
        windowHeight = height;

        updateObjects = true;
    }

    static int init(int width, int height, const char* title, GLFWmonitor* monitor = nullptr,
                    GLFWwindow* share = nullptr)
    {
        if (!glfwInit())
        {
            std::cerr << "ERROR::GLFW::INITIALIZATION_FAILED\n";
            return -1;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, monitor, share);

        if (window == nullptr)
        {
            std::cerr << "ERROR::GLFW::WINDOW_CREATION_FAILED\n";
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(window);

        // ReSharper disable once CppCStyleCast
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // NOLINT(clang-diagnostic-cast-function-type-strict)
        {
            std::cerr << "ERROR::GLAD::INITIALIZATION_FAILED\n";
            return -3;
        }

        glViewport(0, 0, width, height);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        windowWidth = width;
        windowHeight = height;

        return 0;
    };
}

namespace GameEngine
{
    class IGameObject // NOLINT(cppcoreguidelines-special-member-functions)
    {
    protected:
        virtual void Start() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
        virtual void Destroy() = 0;

    public:
        virtual ~IGameObject()
        {
        }
    };

    class GameObject : public IGameObject // NOLINT(cppcoreguidelines-special-member-functions)
    {
    protected:
        unsigned int VAO, VBO;
        float* vertices;
        int pointDataLength;
        int pointCount;

        float x;
        float y;

        Color color;

        void create_vao()
        {
            if (vertices == nullptr)
            {
                std::cerr << "Missing Vertices. Failed to create VAO\n";
                return;
            }
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float)) * pointCount * pointDataLength,
                         vertices,
                         GL_STATIC_DRAW);

            glVertexAttribPointer(0, pointDataLength, GL_FLOAT, GL_FALSE, (GLsizei)pointDataLength * sizeof(float),
                                  static_cast<void*>(nullptr));
            glEnableVertexAttribArray(0);

            reload_object = false;
        }

        bool reload_object = true;

        void static reload()
        {
            if (updateObjects)
            {
                for (GameObject* object : game_objects)
                {
                    object->reload_object = true;
                }
            }
        }

        void Start() override
        {
        }

        void Update(float deltaTime) override
        {
        }

        void Render() override
        {
        }

        void Destroy() override
        {
        }

    public:
        static std::list<GameObject*> game_objects;
        static void delete_all() { while (!game_objects.empty()) delete game_objects.front(); }

        Transform transform;
        std::list<GameObject*> children;

        GameObject()
        {
            VAO = 0;
            VBO = 0;
            pointDataLength = 3;
            pointCount = 3;
            vertices = new float[pointDataLength];

            x = y = 0;
            color.r = color.g = color.b = 1.0f;

            game_objects.push_back(this);
        }

        GameObject(float x, float y) : GameObject()
        {
            this->x = x;
            this->y = y;
        }

        GameObject(float x, float y, float red, float green, float blue) : GameObject(x, y)
        {
            this->color.r = red;
            this->color.g = green;
            this->color.b = blue;
        }

        ~GameObject() override
        {
            delete vertices;
            vertices = nullptr;
            game_objects.remove(this);
        }
    };

    class Square : public GameObject
    {
        float width;
        float height;
        bool GPU_move;

        void create_square_vertices() const
        {
            // Normalized screen coordinates
            float x1 = (x + width) / static_cast<float>(windowWidth) * transform.scale.x; // right edge
            float x2 = -x1; // left edge

            float y1 = (y + height) / static_cast<float>(windowHeight) * transform.scale.y; // top edge
            float y2 = -y1; // bottom edge

            if (!GPU_move)
            {
                // Handle Transform Position - CPU
                float moveX = transform.position.x / static_cast<float>(windowWidth);
                float moveY = transform.position.y / static_cast<float>(windowHeight);

                x1 += moveX;
                x2 += moveX;
                y1 += moveY;
                y2 += moveY;
            }

            // Corner Creation
            for (int i = 0; i < 6; ++i)
            {
                int baseIndex = i * pointDataLength;

                if (i < 3)
                {
                    // First triangle
                    // Lower-left and upper-left
                    vertices[baseIndex + 0] = (i == 0 || i == 2) ? x2 : x1; // x
                    vertices[baseIndex + 1] = (i == 0 || i == 1) ? y2 : y1; // y
                }
                else
                {
                    // Second triangle
                    // Upper-right and lower-right
                    vertices[baseIndex + 0] = (i == 3 || i == 5) ? x1 : x2; // x
                    vertices[baseIndex + 1] = (i == 3 || i == 4) ? y1 : y2; // y
                }

                vertices[baseIndex + 2] = 0.0f; // z

                //vertices[baseIndex + 3] = red;
                //vertices[baseIndex + 4] = green;
                //vertices[baseIndex + 5] = blue;
            }
        }

    public:
        float get_width() const { return width; }
        float get_height() const { return height; }

        Square(float width, float height, float posX, float posY, bool GPU_Move = false) : GameObject(posX, posY)
        {
            this->width = abs(width);
            this->height = abs(height);
            pointCount = 6;

            int size = pointCount * pointDataLength;
            vertices = new float[size];

            create_square_vertices();
            create_vao();
        }

        Square(float width, float height, bool GPU_Move = false) : Square(width, height, 0, 0, GPU_Move)
        {
        }

        void render(bool update = false)
        {
            if (!reload_object) reload();

            if (reload_object || update)
            {
                create_square_vertices();
                create_vao();
            }

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    };
}
