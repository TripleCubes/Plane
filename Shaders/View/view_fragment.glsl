#version 330 core

in vec2 fragment_uv;
out vec4 out_color;

uniform sampler2D gBuffer_pos;
uniform sampler2D gBuffer_normal;
uniform sampler2D gBuffer_color;

vec3 lightDir = vec3(0.4, 1, 0.4);

void main() {
    // vec3 pos = texture(gBuffer_pos, fragment_uv).xyz;
    vec3 normal = texture(gBuffer_normal, fragment_uv).xyz;
    vec3 color = texture(gBuffer_color, fragment_uv).xyz;

    float light = max(0.2, dot(lightDir, normal));
    vec3 result = light * color;

    out_color = vec4(result, 1);
}
