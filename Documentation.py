"""
################
# OpenGL Setup #
################
'''
Step1: INSTALL GLAD & GLFW

Step2: Add "Additional Include Directories" under C/C++ in Project Properties
Current: lib/glfw/include/;lib/glad/include/

Step3: Add "Additional Library Directories" under Linker in Project Properties
Current: lib/glfw/lib-vc2022

Step4: Add glad.c using "Add -> Existing Item..."

Step5: Run -> Crash. Copy glfw3.dll into the build directory
Example: ...\x64\Debug
'''#Setup Steps
#####################
# How to use OpenGL #
#####################
#Stage 1 - Window Creation
'''
Step1: Include glad.h and glfw3.h

Step2: Initialize GLFW and set HINTS
Example:
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
Step3: Create Window using "glfwCreateWindow" (return type GLFWwindow*)

Step4: Make the window current context using "glfwMakeContextCurrent"

Step5: Load GL Loader with "gladLoadGLLoader"

Step6: Set size of viewing area (camera) using "glViewport"

Step7: Main loop: while(!glfwWindowShouldClose(window))
Example:
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window); // Updates window
        glfwPollEvents(); // Prevents crashes
    }

Step8: Don't forget to terminate and exit "glfwTerminate" & "return 0"
'''#Basics
'''
if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
'''#Debugging Window Creation
'''
Option1: Set Auto Viewport resizing with "glfwSetFramebufferSizeCallback" 
(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);)
Example method:
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
'''#Frame Buffer
'''
Option2: Handle inputs
Example method:
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
'''#Input
'''Option3: Change background color
Example: 
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
'''#Buffer Color
#Stage 2 - Triangle and Shaders
'''
Position of points in a 3D space
example:
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  
'''#Vertex input
'''
Vertex Array Object (Saves the instructions):

Create Variable: unsigned int VAO;
Generate Array: glGenVertexArrays(1, &VAO);  
Bind Array: glBindVertexArray(VAO);

Vertex Buffer Objects (Saves Vertex Array):

Create variable: unsigned int VBO;
Generate Buffer: glGenBuffers(1, &VBO); 
Bind Buffer: glBindBuffer(GL_ARRAY_BUFFER, VBO);  
Set Buffer Data: glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

Enabling an setting Vertex Array:

Set Read Instructions: glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
Enable Object: glEnableVertexAttribArray(0); 

'''#Buffers
'''
Create Variable: unsigned int vertexShader;
Create Shader: vertexShader = glCreateShader(GL_VERTEX_SHADER);
Set Source: glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
CompileShader: glCompileShader(vertexShader);

Vertex Shader Example:
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
'''#Vertex Shader (Shape)
'''
Create Variable: unsigned int fragmentShader;
Create Shader: fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
Set Source: glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
Compile Shader: glCompileShader(fragmentShader);

Fragment Shader Example:
const char *fragmentShaderSource = "
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"} \0";
'''#Fragment Shader (Color)
'''
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
'''#Shader Compilation Success Tester
'''
Program Links Shaders to OpenGL Library

Create Variable: unsigned int shaderProgram;
Create Program: shaderProgram = glCreateProgram();
Attach Vertex Shader: glAttachShader(shaderProgram, vertexShader);
Attach Fragment Shader: glAttachShader(shaderProgram, fragmentShader);
Link Program: glLinkProgram(shaderProgram);
'''#Shader Program
'''
int  success;
char infoLog[512];
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
}
'''#Program Compilation Success Tester
'''
glUseProgram(shaderProgram);

After linking and using the Program we can remove the original shader objects

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader); 
'''#Using Program
'''
glUseProgram(shaderProgram);
glBindVertexArray(VAO);

glDrawArrays(GL_TRIANGLES, 0, 3);
'''#Drawing a Triangle"""# OpenGL HOW-TO
"""
####################
# GameEngine Usage #
####################
## Coming soon... ##
####################
""" # GameEngine HOW-TO