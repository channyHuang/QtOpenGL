#version 440 core

uniform sampler2D tex_envmap;

in VS_OUT {
    vec3 normal;
    vec3 view;
} fs_in;

out vec4 color;

void main(void)
{
    vec3 u = normalize(fs_in.view);
    vec3 r = reflect(u, normalize(fs_in.normal));

    r.z += 1.f;
    float m = 0.5f * inversesqrt(dot(r, r));

    color = texture(tex_envmap, r.xy * m + vec2(.5f));
}
