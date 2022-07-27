#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 normal;
out vec3 fragPos;
out vec3 lightPosView;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    normal = normalize(mat3(transpose(inverse(view * model))) * aNormal);
    lightPosView = vec3(view * vec4(lightPos, 1.0));
}