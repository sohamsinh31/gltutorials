#ifndef VAO_H
#define VAO_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "fstream"
#include "cerrno"
#include "string"
#include "VBO.h"

class VAO
{
    public:
        GLuint ID;
        VAO(GLuint id);

        void LinkVBO(VBO VBO,GLfloat layout);
        void Bind();
        void Unbind();
        void Delete(); 
};

#endif