#version 330 core

in vec3 fragment_pos;
in vec3 fragment_normal;
in float fragment_colorIndex;
out vec4 out_color;

vec3 lightDir = vec3(0.4, 1, 0.4);

uniform sampler2D colorPalleteTexture;

void main() {
    float light = max(0.2, dot(lightDir, fragment_normal));
    vec3 result = light * vec3(1, 1, 1);

    out_color = vec4(result, 1);
}
