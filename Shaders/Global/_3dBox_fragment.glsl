#version 330 core

in vec3 fragment_pos;
in vec3 fragment_normal;
out vec4 out_color;

vec3 lightDir = vec3(0.4, 1, 0.4);

uniform vec4 color;

void main() {
    float light = max(0.2, dot(lightDir, fragment_normal));
    vec4 result = light * color;
    result.a = 1;

    out_color = result;
}
