#version 440 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 4) in vec2 texcoord;

uniform vec3 light_pos = vec3(0.f, 0.f, 100.f);
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out VS_OUT
{
    vec2 texcoord;
    vec3 eyeDir;
    vec3 lightDir;
    vec3 normal;
} vs_out;

void main(void)
{
    vec4 P = mv_matrix * position;
    vec3 N = normalize(mat3(mv_matrix) * normal);
    vec3 L = light_pos - P.xyz;
    vec3 V = P.xyz;
    vec3 T = normalize(mat3(mv_matrix) * tangent);
    vec3 B = cross(N, T);

    vs_out.lightDir = normalize(vec3(dot(L, T), dot(L, B), dot(L, N)));
    vs_out.texcoord = texcoord;
    vs_out.normal = N;
    vs_out.eyeDir = normalize(vec3(dot(V, T), dot(V, B), dot(V, N)));

    gl_Position = proj_matrix * P;
}

