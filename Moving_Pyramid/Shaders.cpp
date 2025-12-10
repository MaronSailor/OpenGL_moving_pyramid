// Shaders.cpp

#include "Shaders.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

    std::string vCode = LoadFile(vertexPath);
    std::string fCode = LoadFile(fragmentPath);

    GLuint vShader = Compile(GL_VERTEX_SHADER, vCode.c_str());
    GLuint fShader = Compile(GL_FRAGMENT_SHADER, fCode.c_str());

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, vShader);
    glAttachShader(ProgramId, fShader);
    glLinkProgram(ProgramId);

    GLint success;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ProgramId, 512, NULL, infoLog);
        std::cerr << "Error: Program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::Use() {
    glUseProgram(ProgramId);
}

std::string Shader::LoadFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: could not open shader file " << path << std::endl;
        exit(EXIT_FAILURE);
    }
    std::stringstream buf;
    buf << file.rdbuf();
    return buf.str();
}

GLuint Shader::Compile(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Error: Shader compilation failed\n" << infoLog << std::endl;
    }
    return shader;
}