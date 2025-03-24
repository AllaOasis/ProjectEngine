#include "Shaders.h"

#include <GLAD/glad.h>
#include <iostream>

namespace GameEngine
{
    const char* Shaders::get_fragment_source()
    {
        return R"(
            #version 330 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange color
            })";
    }

    const char* Shaders::get_vertex_source()
    {
        return R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            })";
    }

    unsigned int Shaders::create_program(bool debug)
    {
        const char* vertexShaderSource = get_vertex_source();
        const char* fragmentShaderSource = get_fragment_source();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int successVertex;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
        if (!successVertex)
        {
            char info_log_v[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, info_log_v);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log_v << "\n";
        }
        else if (debug) std::cout << "SUCCESS::SHADER::VERTEX::COMPILATION_SUCCESS\n";

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        int successFragment;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
        if (!successFragment)
        {
            char info_log_fragment[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, info_log_fragment);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log_fragment << "\n";
        }
        else if (debug) std::cout << "SUCCESS::SHADER::FRAGMENT::COMPILATION_SUCCESS\n";

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        int successProgram;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);
        if (!successProgram)
        {
            char info_log_program[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, info_log_program);
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << info_log_program << "\n";
        }
        else if (debug) std::cout << "SUCCESS::PROGRAM::LINKING_SUCCESS\n";

        glUseProgram(shaderProgram);
        
        return shaderProgram;
    }
}
