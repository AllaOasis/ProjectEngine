#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include "GameEngine.h"

GameEngine::vector3 user_input;

float speed = 10.0f;

void input_handle(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    user_input.x = 0;
    user_input.y = 0;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        user_input.y += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        user_input.y -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        user_input.x += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        user_input.x -= speed;
    }
}

int main(int argc, char* argv[])
{
    int init = GameEngine::init(800, 600, "Hello Window!");
    if (init < 0) return init;
    
    unsigned int shaderProgram = GameEngine::Shaders::create_program(true);
    if (shaderProgram == 0) return -1;

    GameEngine::Square* square = new GameEngine::Square(100.0f, 100.0f);

    glUseProgram(shaderProgram);
    
    while (GameEngine::isRunning())
    {
        input_handle(GameEngine::window);
        GameEngine::clear_bg(0.3f, 0.4f, 0.5f, 1.0f);

        square->transform.position += user_input;
        square->render(user_input.magnitude() > 0);

        GameEngine::refresh();
        GameEngine::framerate_limiter();
    }

    GameEngine::GameObject::delete_all();
    glfwTerminate();
    return 0;
}
