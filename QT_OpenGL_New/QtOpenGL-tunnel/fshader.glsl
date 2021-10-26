#version 420 core

layout (binding = 0) uniform sampler2D tex;

in VS_OUT
{
    vec2 tc;
} fs_in;

layout (location = 0) out vec4 color;

void main(void)
{
    color = texture(tex, fs_in.tc);
}
