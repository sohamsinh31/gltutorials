#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "fstream"
#include "cerrno"
#include "string"

std::string get_file(const char *filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char *vertexfile, const char *fragfile);

    void Activate();
    void Delete();
};

#endif