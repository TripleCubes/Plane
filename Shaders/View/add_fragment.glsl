#version 330 core

in vec2 fragment_uv;
out vec4 out_color;

uniform sampler2D in_texture;
uniform sampler2D blurredTexture;

void main() {
    vec4 in_color = texture(in_texture, fragment_uv);
    vec4 blurredColor = texture(blurredTexture, fragment_uv);
    vec4 result = in_color + blurredColor * 0.7;
    result.a = 1;
    out_color = result;
}
