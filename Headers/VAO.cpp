#include "VAO.h"

VAO :: VAO(GLuint id)
{
    this->ID=id;
    glGenVertexArrays(1,&id);
    // glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    // glEnableVertexAttribArray(0);
}

void VAO :: LinkVBO(VBO VBO,GLfloat layout)
{
    VBO.Bind();
    glVertexAttribPointer( layout, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO :: Bind()
{
    glBindVertexArray(ID);
}

void VAO :: Unbind()
{
    glBindVertexArray(0);
}

void VAO :: Delete()
{
    glDeleteVertexArrays(1,&ID);
}