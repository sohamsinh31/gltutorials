#ifndef VGL_TEXTURE_H
#define VGL_TEXTURE_H

#include "GL/glew.h"
#include "string.h"
#include "stdio.h"
#include "shader.h"

class Texture
{
    public:
        GLuint ID;
        GLenum type;
        Texture(const char* image,GLenum textype,GLenum slot,GLenum format,GLenum pixeltype);

        void texUnit(Shader &shader,const char* uniform,GLuint unit);
        void Bind();
        void Unbind();
        void Delete();
};

#endif