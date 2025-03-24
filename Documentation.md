# OpenGL HOW-TO

## OpenGL Setup

### Step 1: Install GLAD & GLFW

### Step 2: Add "Additional Include Directories" under C/C++ in Project Properties  
**Current:** `lib/glfw/include/;lib/glad/include/`

### Step 3: Add "Additional Library Directories" under Linker in Project Properties  
**Current:** `lib/glfw/lib-vc2022`

### Step 4: Add `glad.c` using "Add -> Existing Item..."

### Step 5: Run -> Crash. Copy `glfw3.dll` into the build directory  
**Example:** `...d**Example:** `...\x64\Debug`

---

## How to Use OpenGL

### Stage 1 - Window Creation

#### Step 1: Include Headers
```cpp
#include <glad.h>
#include <GLFW/glfw3.h>
```

#### Step 2: Initialize GLFW and Set Hints
```cpp
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

#### Step 3: Create a Window
```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
```

#### Step 4: Make the Window Current Context
```cpp
glfwMakeContextCurrent(window);
```

#### Step 5: Load GL Loader
```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
std::cerr << "Failed to initialize GLAD" << std::endl;
return -1;
}
```

#### Step 6: Set Viewport Size
```cpp
glViewport(0, 0, 800, 600);
```

#### Step 7: Main Loop
```cpp
while (!glfwWindowShouldClose(window)) {
glfwSwapBuffers(window); // Updates window
glfwPollEvents(); // Prevents crashes
}
```

#### Step 8: Cleanup
```cpp
glfwTerminate();
return 0;
```

### Debugging Window Creation
```cpp
if (window == nullptr) {
std::cerr << "Failed to create GLFW window\n";
glfwTerminate();
return -1;
}
```

### Framebuffer Resizing
```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
glViewport(0, 0, width, height);
}

glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

### Handling Input
```cpp
void processInput(GLFWwindow *window) {
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
```

### Changing Background Color
```cpp
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
```

---

## Stage 2 - Triangle and Shaders

### Vertex Input
```cpp
float vertices[] = {
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
0.0f,  0.5f, 0.0f
};
```

### Buffers (VAO & VBO)
```cpp
unsigned int VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);

unsigned int VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

### Vertex Shader
```cpp
const char *vertexShaderSource = "#version 330 core\n" \
                                 "layout (location = 0) in vec3 aPos;\n" \
                                 "void main()\n" \
                                 "{\n" \
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" \
                                 "}\0";

unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

### Fragment Shader
```cpp
const char *fragmentShaderSource = "#version 330 core\n" \
                                   "out vec4 FragColor;\n" \
                                   "void main()\n" \
                                   "{\n" \
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" \
                                   "}\0";

unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

### Shader Compilation Error Checking
```cpp
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success) {
glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

### Shader Program (Linking)
```cpp
unsigned int shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```

### Shader Program Error Checking
```cpp
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
```

### Using Shader Program
```cpp
glUseProgram(shaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

### Drawing a Triangle
```cpp
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

---

## GameEngine Usage
### Coming soon...

