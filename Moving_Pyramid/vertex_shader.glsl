#version 330 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec3 in_normal;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragColor  = in_color;
    fragNormal = mat3(transpose(inverse(model))) * in_normal;
    fragPos    = vec3(model * vec4(in_vertex, 1.0));

    gl_Position = projection * view * model * vec4(in_vertex, 1.0);
}
