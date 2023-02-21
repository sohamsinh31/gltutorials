#ifndef EBO_H
#define EBO_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "fstream"
#include "cerrno"
#include "string"

class EBO
{
    public:
        GLuint ID;
        EBO(GLuint* indices,GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif