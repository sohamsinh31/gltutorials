#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include "math.h"
#include <GLFW/glfw3.h>
#include "Headers/VAO.h"
#include "Headers/VBO.h"
#include "Headers/EBO.h"
#include "Headers/shader.h"

const GLuint WIDTH = 800, HEIGHT = 600;

float vertices[] = {
    // positions
    // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
};

float indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main()
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
    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));
    vao1.LinkVBO(vbo1, 0);
    vao1.Unbind();
    vbo1.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram.ID,
                                                       "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        vao1.Bind();
        // now render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    vao1.Delete();
    vbo1.Delete();
    shaderProgram.Delete();
    glfwTerminate();

    return EXIT_SUCCESS;
}
