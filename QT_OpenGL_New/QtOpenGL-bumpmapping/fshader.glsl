#version 440 core

out vec4 color;

layout (binding = 0) uniform sampler2D tex_color;
layout (binding = 1) uniform sampler2D tex_normal;

in VS_OUT
{
    vec2 texcoord;
    vec3 eyeDir;
    vec3 lightDir;
    vec3 normal;
} fs_in;

void main(void)
{
    vec3 V = normalize(fs_in.eyeDir);
    vec3 L = normalize(fs_in.lightDir);
    vec3 N = normalize(texture(tex_normal, fs_in.texcoord).rgb * 2.f - vec3(1.f));
    vec3 R = reflect(-L, N);

    vec3 diffuse_albedo = texture(tex_color, fs_in.texcoord).rgb;
    vec3 diffuse = max(dot(N, L), 0.f) * diffuse_albedo;

    vec3 specular_albedo = vec3(1.f);
    vec3 specular = max(pow(dot(R, V), 20.f), 0.f) * specular_albedo;

    color = vec4(diffuse + specular, 1.f);
}
