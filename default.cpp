#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "string"
#include "shader.h"

const GLuint WIDTH = 800, HEIGHT = 600;

int main(int argc, char const *argv[])
{
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    glViewport(0, 0, screenWidth, screenHeight);

    Shader shaderProgram("def.vert", "def.frag");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    return 0;
}
