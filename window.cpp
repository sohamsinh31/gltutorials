#include "Headers/EBO.h"
#include "Headers/VBO.h"
#include "Headers/VAO.h"
#include "Headers/shader.h"
#include "math.h"

float vertices[] = {
    -0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
    0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
    0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f,
    -0.5f / 2,-0.5f * float(sqrt(3)) / 6,0.0f,
    0.5f / 2,-0.5f * float(sqrt(3)) / 6,0.0f,
    0.0f,-0.5f * float(sqrt(3)) / 3,0.0f,
};

GLfloat indices[] = {
    0,3,5,
    3,2,4,
    5,4,1,
};

int main()
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    GLenum err;
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (!glewInit())
    {
        std::cout<<glewGetErrorString(err)<<"\n";
    }
    Shader shaderProgram("Assets/def.vert","Assets/def.frag");
    VAO vao1;
    vao1.Bind();
    VBO VBO1(vertices,sizeof(vertices));
    //EBO EBO1(indices,sizeof(indices));

    vao1.LinkVBO(VBO1,0);
    vao1.Unbind();
    VBO1.Unbind();
    //EBO1.Unbind();

    glViewport(0, 0, 800, 600);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        shaderProgram.Activate();
        vao1.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vao1.Delete();
    VBO1.Delete();
    //EBO1.Delete();
    shaderProgram.Delete();
    glfwTerminate();
    return 0;
}
