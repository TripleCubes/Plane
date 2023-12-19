#version 330 core

layout (location = 0) in vec3 vertex_pos;
out vec2 fragment_uv;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform vec2 textureSize;
uniform bool flipped;

void main() {
    vec3 final_pos = vec3(vertex_pos.x * textureSize.x / 24, vertex_pos.y * textureSize.y / 24, vertex_pos.z);
    gl_Position = projectionMat * viewMat * modelMat * vec4(final_pos, 1.0);
    if (!flipped) {
        fragment_uv = vec2(vertex_pos.x, 1 - vertex_pos.y);
    } else {
        fragment_uv = vec2(1 - vertex_pos.x, 1 - vertex_pos.y);
    }
}
