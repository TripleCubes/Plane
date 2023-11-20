#version 330 core

in vec3 fragment_pos;
in vec3 fragment_normal;
out vec4 out_color;

vec3 lightDir = vec3(0.4, 1, 0.4);

void main() {
    vec4 color = vec4(0.71, 0.97, 0.59, 1);
    float light = max(0.2, dot(lightDir, fragment_normal));
    vec4 result = light * color;
    result.a = 1;

    out_color = result;
}
