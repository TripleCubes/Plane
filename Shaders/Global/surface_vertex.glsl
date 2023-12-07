#version 330 core

layout (location = 0) in vec3 vertex_pos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform vec2 size;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertex_pos.x*size.x, 
                                                            vertex_pos.y, 
                                                            vertex_pos.z*size.y, 
                                                            1.0);
}
