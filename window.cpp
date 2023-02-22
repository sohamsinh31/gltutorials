#include "Headers/EBO.h"
#include "Headers/VBO.h"
#include "Headers/VAO.h"
#include "Headers/shader.h"
#include "math.h"

GLint windowWidth, windowHeight;
Shader shaderProgram;

// float vertices[] = {
//     0.5f, 0.5f, 0.0f, // top right
//     0.5f, -0.5f, 0.0f, // bottom right
//     -0.5f, -0.5f, 0.0f, // bottom left
//     -0.5f, 0.5f, 0.0f // top left
// };

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

GLfloat vertices[] =
    {
        -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
        1, -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1,
        -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, -1, -1,
        -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
        -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
        -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1};

GLfloat colors[] =
    {
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,
        0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1};

GLFWwindow *window;

void drawCube()
{

    static float alpha = 0;
    // attempt to rotate cube
    glRotatef(alpha, 0, 1, 0);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += 1;
}

void display()
{
    // Scale to window size
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    // Draw stuff

    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluPerspective(60, (double)windowWidth / (double)windowHeight, 0.1, 100);

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0, 0, -5);

    drawCube();
}

int main()
{
    glfwInit();
    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    GLenum err;
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << glewGetErrorString(err) << "\n";
    }
    shaderProgram = Shader("Assets/def.vert", "Assets/def.frag");
    VAO vao1;
    vao1 = VAO();
    vao1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices,sizeof(indices));

    vao1.LinkVBO(VBO1, 0);
    vao1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glViewport(0, 0, 800, 600);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // shaderProgram.Activate();
        // vao1.Bind();
        //glDrawArrays(GL_QUADS, 0, 24);
        // glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vao1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwTerminate();
    return 0;
}
