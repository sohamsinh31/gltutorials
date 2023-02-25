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
#include "Headers/texture.h"
#include "math.h"
#include "src/SOIL2/SOIL2.h"

const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat vertices[] =
    {
        // positions
        // colors
        // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

GLuint indices[] =
    {
        0, 2, 1,
        0, 3, 2};

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

    Shader shaderProgram("Assets/def.vert", "Assets/def.frag");

    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo1(indices, sizeof(indices));
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();

    // texture
    Texture popcat("Assets/cat.jpg",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGBA,GL_UNSIGNED_BYTE);
    popcat.texUnit(shaderProgram,"tex0",0);

    GLuint uniId = glGetUniformLocation(shaderProgram.ID, "scale");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniId, 0.5f);
        popcat.Bind();
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    popcat.Delete();
    shaderProgram.Delete();

    glfwTerminate();

    return 0;
}
