//Pyramid.cpp

#include "Pyramid.h"

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define GRAY 0.5f, 0.5f, 0.5f

Pyramid::Pyramid() {

	// Use brace-enclosed initializer lists to initialize arrays element-wise
	GLfloat initVertices[48] = {
		0.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f,
		0.5f, 0.0f, 0.5f, // First face

		0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,
		0.5f, 0.0f, -0.5f, // Second face

		0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,
		-0.5f, 0.0f, -0.5f, // Third face

		0.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,
		-0.5f, 0.0f, 0.5f, // Fourth face

		-0.5f, 0.0f, 0.5f,
		0.5f, 0.0f, 0.5f,
		0.5f, 0.0f, -0.5f,
		-0.5f, 0.0f, -0.5f // Base face	
	};
	for (int i = 0; i < 48; ++i) Vertices[i] = initVertices[i];

	GLfloat initColors[48] = {
		RED,
		RED,
		RED, // First face

		RED,
		RED,
		RED,  // Second face

		RED,
		RED,
		RED, // Third face	

		RED,
		RED,
		RED, // Fourth face

		RED,
		RED,
		RED,
		RED // Base face
	};
	for (int i = 0; i < 48; ++i) Colors[i] = initColors[i];

	GLfloat initNormals[48] = {
		// Side 1 (Apex, Base1, Base2)
		0.0f, 0.5f, 0.5f, // Apex
		0.0f, 0.5f, 0.5f, // Base1
		0.0f, 0.5f, 0.5f, // Base2

		// Side 2 (Apex, Base2, Base3)
		0.5f, 0.5f, 0.0f, // Apex
		0.5f, 0.5f, 0.0f, // Base2
		0.5f, 0.5f, 0.0f, // Base3

		// Side 3 (Apex, Base3, Base4)
		0.0f, 0.5f, -0.5f, // Apex
		0.0f, 0.5f, -0.5f, // Base3
		0.0f, 0.5f, -0.5f, // Base4

		// Side 4 (Apex, Base4, Base1)
		-0.5f, 0.5f, 0.0f, // Apex
		-0.5f, 0.5f, 0.0f, // Base4
		-0.5f, 0.5f, 0.0f, // Base1

		// Base (Base1, Base2, Base3, Base4)
		0.0f, -1.0f, 0.0f, // Base1
		0.0f, -1.0f, 0.0f, // Base2
		0.0f, -1.0f, 0.0f, // Base3
		0.0f, -1.0f, 0.0f  // Base4
	};
	for (int i = 0; i < 48; ++i) Normals[i] = initNormals[i];
}

void Pyramid::Draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12); 
	glDrawArrays(GL_QUADS, 12, 4);     
	glBindVertexArray(0);
}



void Pyramid::Init(GLuint programId) {
    vertexLoc = glGetAttribLocation(programId, "in_vertex");
    colorLoc = glGetAttribLocation(programId, "in_color");
	normalLoc = glGetAttribLocation(programId, "in_normal");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW); 
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals), Normals, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalLoc);

    glBindVertexArray(0);
}
