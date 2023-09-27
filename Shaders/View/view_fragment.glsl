#version 330 core

in vec3 fragment_pos;
in vec3 fragment_normal;
in float fragment_colorIndex;
out vec4 out_color;

uniform sampler2D colorPalleteTexture;
uniform vec2 colorPalleteTextureWH;

vec3 lightDir = vec3(0.4, 1, 0.4);

void main() {
    vec2 colorSamplePos = vec2(fragment_colorIndex / colorPalleteTextureWH.x + 0.01, 0.01);
    vec4 color = texture(colorPalleteTexture, colorSamplePos);
    float light = max(0.2, dot(lightDir, fragment_normal));

    out_color = light * color;
}
