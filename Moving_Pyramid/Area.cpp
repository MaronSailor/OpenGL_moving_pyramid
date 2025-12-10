// Area.cpp
#include "Area.hpp"

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define GRAY 0.5f, 0.5f, 0.5f

#define COLOR1 0.2f, 0.6f, 0.9f
#define COLOR2 0.9f, 0.6f, 0.2f

Area::Area() {
    // Define a static ground plane made of two triangles (a quad) under the pyramid
    // Square centered at origin on Y=0
    // Vertices (6 vertices -> 2 triangles)
    // Triangle 1: v0(-5,0,-5), v1(5,0,-5), v2(5,0,5)
    // Triangle 2: v0(-5,0,-5), v2(5,0,5), v3(-5,0,5)

    // Clear arrays
    for (int i = 0; i < 48; ++i) { Vertices[i] = 0.0f; Colors[i] = 0.0f; Normals[i] = 0.0f; }

    // Vertices
    GLfloat planeVertices[18] = {
        -1.0f, -0.5f, -1.0f,
         1.0f, -0.5f, -1.0f,
         1.0f, -0.5f,  1.0f,

         1.0f, -0.5f,  1.0f,
        -1.0f, -0.5f, -1.0f,
        -1.0f, -0.5f,  1.0f
    };
    for (int i = 0; i < 18; ++i) Vertices[i] = planeVertices[i];

    // Colors: two different colors, one per triangle
    GLfloat planeColors[18] = {
        COLOR1,
        COLOR1,
        COLOR1,

        COLOR2,
        COLOR2,
        COLOR2
    };
    for (int i = 0; i < 18; ++i) Colors[i] = planeColors[i];

    // Normals: up-facing for a flat plane
    GLfloat planeNormals[18] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    for (int i = 0; i < 18; ++i) Normals[i] = planeNormals[i];
}

void Area::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Area::Init(GLuint programId) {
    vertexLoc = glGetAttribLocation(programId, "in_vertex");
    colorLoc = glGetAttribLocation(programId, "in_color");
    normalLoc = glGetAttribLocation(programId, "in_normal");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, Normals, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalLoc);

    glBindVertexArray(0);
}
