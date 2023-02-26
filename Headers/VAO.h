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
        void LinkVBO(VBO VBO,GLfloat layout);
        void LinkAttrib(VBO &VBO,GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride, void *offset);
        void Bind();
        void Unbind();
        void Delete(); 
};

#endif