#version 330 core

in vec2 fragment_uv;

out vec4 out_color;

uniform sampler2D textTexture;
uniform vec4 color;

void main() {
    float alpha = texture(textTexture, fragment_uv).r;
    out_color = vec4(color.rgb, color.a * alpha);
}
