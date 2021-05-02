#include "Material.h"

#include <string>
#include <fstream>
#include <sstream>

//FIXME glfw -> sfml

std::string LoadFile(const sf::String &FileName) {
    std::ifstream ifile(FileName, std::ifstream::binary);
    std::stringstream ss;

    while (ifile.good()) {
        std::string temp;
        std::getline(ifile, temp);
        ss << temp << std::endl;
    }
    return ss.str();
}

//GLuint LoadShader(const char* FileName, GLuint type)
//{
//    std::string shader = LoadFile(FileName).c_str();
//    const char* txt = shader.c_str();
//    GLuint Shader = glCreateShader(type);
//    glShaderSource(Shader, 1, &txt, NULL);
//    glCompileShader(Shader);
//
//    return Shader;
//}

void Material::SetProgram() {
//    glUseProgram(prog);
}

void Material::ResetProgram() {
//    glUseProgram(0);
}

void Material::InitShaders(const sf::String &filename) {
    auto FragShaderName = filename + ".frag";
    auto VertShaderName = filename + ".vert";
//    GLuint FragShader = LoadShader(FragShaderName.c_str(), GL_FRAGMENT_SHADER);
//    GLuint VertShader = LoadShader(VertShaderName.c_str(), GL_VERTEX_SHADER);
//
//    GLint ok;
//    GLchar log[2000];
//    prog = glCreateProgram();
//    glAttachShader(prog, FragShader);
//    //glAttachShader(prog, VertShader);
//
//    glLinkProgram(prog);
//    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
//    if (!ok)
//    {
//        glGetProgramInfoLog(prog, 2000, NULL, log);
//        printf("\n");
//    }
}