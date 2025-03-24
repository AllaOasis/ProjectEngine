#include <GLAD/glad.h>
#include <GameEngine.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "INFO::GAMEENGINE::STARTING\n";

    int init = GameEngine::WindowManager::init(800, 600, "Project Engine!", true);
    if (init < 0) return init;

    unsigned int shaderProgram = GameEngine::Shaders::create_program(true);
    if (shaderProgram == 0) return -1;

    GameEngine::Square* square = new GameEngine::Square(100.0f, 100.0f);
    
    while (GameEngine::isRunning())
    {
        GameEngine::clear_bg(0.3f, 0.4f, 0.5f, 1.0f);

        square->render();
        
        GameEngine::framerate_limiter();

        GameEngine::WindowManager::Refresh();
    }

    GameEngine::GameObject::delete_all();
    glfwTerminate();
    
    return 0;
}
