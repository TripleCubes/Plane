#version 330 core

in vec2 fragment_uv;
out vec4 out_color;

uniform sampler2D in_texture;
uniform bool horizontalBlur;
uniform int blurSizePx;
uniform vec2 windowSize;

void main() {
    vec2 step = vec2(1/windowSize.x, 1/windowSize.y);
    vec4 result = vec4(0, 0, 0, 0);

    if (horizontalBlur) {
        for (int i = -blurSizePx; i <= blurSizePx; i++) {
            result += texture(in_texture, vec2(fragment_uv.x + i*step.x, fragment_uv.y));
        }
    } else {
        for (int i = -blurSizePx; i <= blurSizePx; i++) {
            result += texture(in_texture, vec2(fragment_uv.x, fragment_uv.y + i*step.y));
        }
    }
    result /= (blurSizePx*2 + 1);
    result.a = 1;

    out_color = result;
}
