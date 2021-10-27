#version 440 core

layout (location = 0) in vec3 position;
out vec4 particle_color;

void main(void)
{
    particle_color = vec4(0.6f, 0.8f, 0.8f, 1.0f) * (smoothstep(-10.f, 10.f, position.z) * 0.6f + 0.4f);
    gl_Position = vec4(position * 0.2f, 1.0f);
}

