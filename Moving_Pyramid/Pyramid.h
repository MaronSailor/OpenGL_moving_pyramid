//Pyramid.h

#pragma once

#define PYRAMID_H

#include <GL/glew.h>
#include <GL/glut.h>


class Pyramid {

public:
	Pyramid();
	void Init(GLuint programId);
	void Draw();
private:
	GLfloat Vertices[48];

	GLfloat Colors[48];

	GLfloat Normals[48];

	GLuint VAO = 0;

	GLuint VBO = 0;   

	GLuint NBO = 0;

	GLuint CBO = 0;  

	GLint vertexLoc = -1;

	GLint colorLoc = -1;

	GLint normalLoc = -1;
};
