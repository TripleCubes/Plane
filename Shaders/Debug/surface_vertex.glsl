#version 330 core

layout (location = 0) in vec3 vertex_pos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform vec2 surfaceSize;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertex_pos.x*surfaceSize.x, 
                                                            vertex_pos.y, 
                                                            vertex_pos.z*surfaceSize.y, 
                                                            1.0);
}
