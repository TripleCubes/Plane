#version 330 core

in vec2 fragment_uv;
out vec4 out_color;

uniform sampler2D windowRectTexture;

void main() {
    out_color = texture(windowRectTexture, fragment_uv);
}
