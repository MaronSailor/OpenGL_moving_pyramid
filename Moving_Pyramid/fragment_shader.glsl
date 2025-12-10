#version 330 core

in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 outColor;

uniform vec3 lightPos = vec3(4.0, 5.5, 2.0);
uniform vec3 viewPos  = vec3(0.0, 1.0, 5.0);

void main() {
    vec3 N = normalize(fragNormal);

    vec3 L = normalize(lightPos - fragPos);

    float diff = max(dot(N, L), 0.0);

    vec3 result = fragColor * diff;

    outColor = vec4(result, 1.0);
}
