#version 330 core

layout (location = 0) in vec2 vertex_pos;

uniform vec2 pos1;
uniform vec2 pos2;
uniform vec2 windowSize;

void main() {
    vec2 diff = pos2 - pos1;
    vec2 resultPos = vec2(pos1.x/windowSize.x + vertex_pos.x*diff.x/windowSize.x,
                            pos1.y/windowSize.y + vertex_pos.y*diff.y/windowSize.y);
    resultPos = (resultPos * 2) - 1;
    gl_Position = vec4(resultPos, 0.0, 1.0);
}
