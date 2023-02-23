#include "shader.h"

std::string get_file(const char* filename)
{
    try{
    std::ifstream in(filename,std::ios::binary);
    if(in)
    {
        std::string contents;
        in.seekg(0,std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0,std::ios::beg);
        in.read(&contents[0],contents.size());
        in.close();
        return contents;
    }
    throw(errno);
    }
    catch(int i)
    {
        std::cout<<"Shader file not found"<<std::endl;
    }
}

Shader :: Shader()
{
    std::cout<<"Declare files first\n";
}

Shader::Shader(const char* vertexfile,const char* fragfile){
    std::string vertex_code = get_file(vertexfile);
    std::string frag_code = get_file(fragfile);

    const char* vertex_source = vertex_code.c_str();
    const char* frag_source = frag_code.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_source, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag_source, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader :: Activate()
{
    glUseProgram(ID);
}

void Shader :: Delete()
{
    glDeleteProgram(ID);
}