#version 330 core

layout (location = 0) in vec3 vertex_pos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform vec3 size;
uniform vec3 margin;

void main() {
    vec3 size2 = size - margin*2;
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertex_pos.x*size2.x + margin.x, 
                                                            vertex_pos.y*size2.y + margin.y, 
                                                            vertex_pos.z*size2.z + margin.z, 1.0);
}
