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
    // vao1.LinkVBO(vbo1, 0);
    EBO ebo1(indices, sizeof(indices));
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();

    GLuint uniId = glGetUniformLocation(shaderProgram.ID, "scale");
    // texture

    int width_image, height_image, num_col;
    unsigned char *bytes = SOIL_load_image("Assets/cat.jpg", &width_image, &height_image, 0, SOIL_LOAD_RGBA);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // float flatcolor[] = {1.0f,1.0f,1.0f,1.0f};
    //  glTextureParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,flatcolor);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    printf("%s",bytes);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_image, height_image, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texuniId = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.Activate();
    glUniform1i(texuniId, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniId, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    glDeleteTextures(1, &texture);
    shaderProgram.Delete();

    glfwTerminate();

    return 0;
}
