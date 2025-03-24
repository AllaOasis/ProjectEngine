#pragma once
#include "Core.h"
#include <list>

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
        virtual ~IGameObject() = default;
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

        void create_vao();

        bool reload_object = true;
        
        void static reload(bool update = false);

        void Start() override {}

        void Update(float deltaTime) override {}

        void Render() override {}

        void Destroy() override {}

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

        void create_square_vertices() const;

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

        Square(float width, float height, bool GPU_Move = false) : Square(width, height, 0, 0, GPU_Move) {}

        void render(bool update = false);
    };
}

