#version 440 core

out VS_OUT
{
    vec2 tc;
} vs_out;

void main(void)
{
    const vec4 vertices[] = vec4[](vec4(-0.5f, 0.f, -0.5f, 1.f),
                                    vec4(0.5f, 0.f, -0.5f, 1.f),
                                    vec4(-0.5f, 0.f, 0.5f, 1.f),
                                    vec4(0.5f, 0.f, 0.5f, 1.f));

    int x = gl_InstanceID & 63;
    int y = gl_InstanceID >> 6;
    vec2 offs = vec2(x, y);

    vs_out.tc = (vertices[gl_VertexID].xz + offs + vec2(0.5f)) / 64.f;

    gl_Position = vertices[gl_VertexID] + vec4(float(x - 32), 0.f, float(y - 32), 0.f);
}

