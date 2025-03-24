#include <GLAD/glad.h>
#include <iostream>
#include "GameObject.h"
#include "WindowManager.h"

namespace GameEngine
{

    // GameObject
    std::list<GameObject*> GameObject::game_objects = std::list<GameObject*>();
    
    void GameObject::create_vao() {
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
    void GameObject::reload(bool update)
    {
        if (update)
        {
            for (GameObject* object : game_objects)
            {
                object->reload_object = true;
            }
        }
    }
    // Square
    void Square::create_square_vertices() const
    {
        // Normalized screen coordinates
        float x1 = (x + width) / static_cast<float>(WindowManager::GetWidth()) * transform.scale.x; // right edge
        float x2 = -x1; // left edge

        float y1 = (y + height) / static_cast<float>(WindowManager::GetHeight()) * transform.scale.y; // top edge
        float y2 = -y1; // bottom edge

        if (!GPU_move)
        {
            // Handle Transform Position - CPU
            float moveX = transform.position.x / static_cast<float>(WindowManager::GetWidth());
            float moveY = transform.position.y / static_cast<float>(WindowManager::GetHeight());

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
    void Square::render(bool update)
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


}