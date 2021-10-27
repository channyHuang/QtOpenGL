#version 440 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

uniform mat4 mv_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec3 light_pos = vec3(100.f, 100.f, 100.f);
uniform vec3 diffuse_albedo = vec3(0.5f, 0.2f, 0.7f);
uniform vec3 specular_albedo = vec3(0.7f);
uniform float specular_power = 128.f;
uniform vec3 ambient = vec3(0.1f, 0.1f, 0.1f);

out VS_OUT
{
    vec3 color;
} vs_out;

void main(void)
{
    vec4 P = mv_matrix * position;
    vec3 N = mat3(mv_matrix) * normal;
    vec3 L = light_pos - P.xyz;
    vec3 V = -P.xyz;

    N = normalize(N);
    L = normalize(L);
    V = normalize(V);

    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.f) * diffuse_albedo;
    vec3 specular = pow(max(dot(R, V), 0.f), specular_power) * specular_albedo;

    vs_out.color = ambient + diffuse + specular;

    gl_Position = proj_matrix * P;
}

