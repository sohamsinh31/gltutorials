#include "texture.h"
#include "SOIL/SOIL.h"

Texture ::Texture(const char *image, GLenum textype, GLenum slot, GLenum format, GLenum pixeltype)
{
    type = textype;
    int width_image, height_image, num_col;
    unsigned char *bytes = SOIL_load_image(image, &width_image, &height_image, 0, SOIL_LOAD_RGBA);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(textype, ID);

    glTexParameteri(textype, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(textype, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(textype, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(textype, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // float flatcolor[] = {1.0f,1.0f,1.0f,1.0f};
    //  glTextureParameterfv(textype,GL_TEXTURE_BORDER_COLOR,flatcolor);

    glTexImage2D(textype, 0, GL_RGBA, width_image, height_image, 0, format, pixeltype, bytes);
    glGenerateMipmap(textype);
    SOIL_free_image_data(bytes);
    glBindTexture(textype, 0);
}

void Texture ::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    GLuint texuniId = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texuniId, unit);
}

void Texture :: Bind()
{
    glBindTexture(type,ID);
}

void Texture :: Unbind()
{
    glBindTexture(type,0);
}

void Texture :: Delete()
{
    glDeleteTextures(1,&ID);  
}