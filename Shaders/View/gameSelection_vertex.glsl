#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_normal;
out vec3 fragment_pos;
out vec3 fragment_normal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertex_pos, 1.0);
    fragment_pos = (modelMat * vec4(vertex_pos, 1.0)).xyz;
    fragment_normal = vertex_normal;
}
