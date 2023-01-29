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
        VAO();

        void LinkVBO(VBO VBO,GLuint layout);
        void Bind();
        void Unbind();
        void Delete(); 
};

#endif