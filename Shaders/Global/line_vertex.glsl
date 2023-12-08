#version 330 core

layout (location = 0) in vec3 vertex_pos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform vec3 pos1;
uniform vec3 pos2;

void main() {
    vec3 diff = pos2 - pos1;
    vec3 result_pos = vec3(vertex_pos.x * diff.x, vertex_pos.y * diff.y, vertex_pos.z * diff.z);
    gl_Position = projectionMat * viewMat * modelMat * vec4(result_pos, 1);
}
