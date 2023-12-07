#version 330 core

out vec4 out_color;

uniform vec4 surfaceColor;

void main() {
    out_color = surfaceColor;
}
