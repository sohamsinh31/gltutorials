#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "string"
#include "Headers/shader.h"
#include "Headers/VBO.h"
#include "Headers/VAO.h"
#include "Headers/EBO.h"
#include "math.h"

const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat vertices[] =
    {
        //cordinates                                      //colors
        -0.5f,  -0.5f * float(sqrt(3)) / 3,      0.0f,    0.9f, 0.9f, 0.02f,//lower left corner
        0.5f,   -0.5f * float(sqrt(3)) / 3,      0.0f,    0.9f ,0.9f, 0.02f,//lower rignt corner
        0.0f,    0.5f * float(sqrt(3)) * 2 / 3,  0.0f,    0.8f, 0.8f, 0.02f,//uper corner
        -0.25f,  0.5f * float(sqrt(3)) / 6,      0.0f,    0.8f, 0.3f, 0.02f,//inner left
        0.25f,   0.5f * float(sqrt(3)) / 6,      0.0f,    0.8f, 0.3f, 0.02f,//inner right
        0.0f,   -0.5f * float(sqrt(3)) / 3,      0.0f,    0.8f, 0.3f, 0.02f,//inner down
        };

GLuint indices[] =
    {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1};

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

    Shader shaderProgram("Assets/core.vert", "Assets/core.frag");

    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));    vao1.LinkVBO(vbo1, 0);

    vao1.LinkAttrib(vbo1,0,3,GL_FLOAT,6 * sizeof(float),(void *)0);
    vao1.LinkAttrib(vbo1,1,3,GL_FLOAT,6 * sizeof(float),(void *)(3 * sizeof(float)));
    EBO ebo1(indices, sizeof(indices));
    vao1.Unbind();
    vbo1.Unbind();

    GLuint uniId = glGetUniformLocation(shaderProgram.ID,"scale");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniId,0.5f);
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
