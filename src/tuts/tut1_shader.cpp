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

// GLfloat vertices[] =
//     {
//         //cordinates                                      //colors
//         -0.5f,  -0.5f * float(sqrt(3)) / 3,      0.0f, 
//         0.5f,   -0.5f * float(sqrt(3)) / 3,      0.0f,    
//         0.0f,    0.5f * float(sqrt(3)) * 2 / 3,  0.0f,   
//         -0.5f/2,  0.5f * float(sqrt(3)) / 6,      0.0f,    
//         0.5f/2,   0.5f * float(sqrt(3)) / 6,      0.0f,    
//         0.0f,   -0.5f * float(sqrt(3)) / 3,      0.0f,   
//         };

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

    Shader shaderProgram("Assets/def.vert", "Assets/def.frag");

    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));    vao1.LinkVBO(vbo1, 0);

    vao1.LinkAttrib(vbo1,0,3,GL_FLOAT,6 * sizeof(float),(void *)0);
    vao1.LinkAttrib(vbo1,1,3,GL_FLOAT,6 * sizeof(float),(void *)(3 * sizeof(float)));
    EBO ebo1(indices, sizeof(indices));
    vao1.Unbind();
    vbo1.Unbind();

    GLuint uniId = glGetUniformLocation(shaderProgram.ID,"scale");

    // GLuint VAO, VBO, EBO;

    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniId,0.5f);
        vao1.Bind();
        // glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    shaderProgram.Delete();
    return 0;
}
