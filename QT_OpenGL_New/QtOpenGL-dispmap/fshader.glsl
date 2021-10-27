#version 440 core

out vec4 color;
layout (binding = 1) uniform sampler2D tex_color;
uniform bool enable_fog = true;
uniform vec4 fog_color = vec4(0.7f, 0.8f, 0.9f, 0.0f);

in VS_OUT {
    vec2 tc;
    vec3 world_coord;
    vec3 eye_coord;
} fs_in;

vec4 fog(vec4 c) {
    float z = length(fs_in.eye_coord);
    float de = 0.025f * smoothstep(0.f, 6.f, 10.f - fs_in.world_coord.y);
    float di = 0.045f * smoothstep(0.f, 40.f, 20.f - fs_in.world_coord.y);

    float extinction = exp(-z * de);
    float inscattering = exp(-z * di);

    return c * extinction + fog_color * (1.f - inscattering);
}

void main(void)
{
    vec4 landscape = texture(tex_color, fs_in.tc);

    if (enable_fog) {
        color = fog(landscape);
    } else {
        color = landscape;
    }
}
