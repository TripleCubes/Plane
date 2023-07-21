#version 330 core

in vec2 fragment_uv;
out vec4 out_color;

const int DRAWMODE_RECT = 0;
const int DRAWMODE_TEXTURE = 1;
const int DRAWMODE_TEXT = 2;
uniform int drawMode;
uniform vec4 drawColor;
uniform sampler2D rectTexture;

void main() {
    if (drawMode == DRAWMODE_RECT) {
        out_color = drawColor;
        return;
    }

    if (drawMode == DRAWMODE_TEXTURE) {
        out_color = texture(rectTexture, fragment_uv);
        return;
    }

    // drawMode == DRAWMODE_TEXT
    float alpha = texture(rectTexture, fragment_uv).r;
    out_color = vec4(drawColor.rgb, drawColor.a * alpha);
}
