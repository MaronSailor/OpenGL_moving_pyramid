// Shaders.h

#pragma once
#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint ProgramId;

    Shader(const char* vertexPath, const char* fragmentPath);
    void Use();

private:
    std::string LoadFile(const char* path);
    GLuint Compile(GLenum type, const char* source);
};

#endif // !SHADERS_H