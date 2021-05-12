#include "ShaderResource.h"
#include <fstream>

std::string LoadFile(std::string&& filename)
{
    std::ifstream ifile(filename, std::ifstream::binary);
    std::string filetext;

    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }
    return filetext;
}

GLuint LoadShader(std::string&& filename, GLuint type)
{
    std::string shader = LoadFile(std::move(filename));
    const char* txt = shader.c_str();
    GLuint Shader = glCreateShader(type);
    glShaderSource(Shader, 1, &txt, nullptr);
    glCompileShader(Shader);

    return Shader;
}

ShaderResource::ShaderResource(std::string&& filename)
{
    std::string FragShaderName = filename;
    FragShaderName += ".frag";
    std::string VertShaderName = filename;
    VertShaderName += ".vert";
    GLuint FragShader = LoadShader(std::move(FragShaderName), GL_FRAGMENT_SHADER);
    GLuint VertShader = LoadShader(std::move(VertShaderName), GL_VERTEX_SHADER);

    GLint ok;
    GLchar log[2000];
    ShaderID = glCreateProgram();
    glAttachShader(ShaderID, FragShader);
    glAttachShader(ShaderID, VertShader);
    glLinkProgram(ShaderID);
    glGetProgramiv(ShaderID, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        glGetProgramInfoLog(ShaderID, 2000, nullptr, log);
        printf("\n");
    }
}