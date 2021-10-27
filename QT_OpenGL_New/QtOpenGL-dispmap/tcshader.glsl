#version 440 core

layout (vertices = 4) out;
uniform mat4 mvp_matrix;

in VS_OUT {
    vec2 tc;
} tcs_in[];

out TCS_OUT {
    vec2 tc;
} tcs_out[];

void main(void)
{
    if (gl_InvocationID == 0) {
        vec4 p0 = mvp_matrix * gl_in[0].gl_Position;
        vec4 p1 = mvp_matrix * gl_in[1].gl_Position;
        vec4 p2 = mvp_matrix * gl_in[2].gl_Position;
        vec4 p3 = mvp_matrix * gl_in[3].gl_Position;

        p0 /= p0.w;
        p1 /= p1.w;
        p2 /= p2.w;
        p3 /= p3.w;

        if (p0.z <= 0.f || p1.z <= 0.f || p2.z <= 0.f || p3.z <= 0.f) {
            gl_TessLevelOuter[0] = 0.f;
            gl_TessLevelOuter[1] = 0.f;
            gl_TessLevelOuter[2] = 0.f;
            gl_TessLevelOuter[3] = 0.f;
        } else {
            float l0 = length(p2.xy - p0.xy) * 16.f + 1.f;
            float l1 = length(p3.xy - p2.xy) * 16.f + 1.f;
            float l2 = length(p3.xy - p1.xy) * 16.f + 1.f;
            float l3 = length(p1.xy - p0.xy) * 16.f + 1.f;

            gl_TessLevelOuter[0] = l0;
            gl_TessLevelOuter[1] = l1;
            gl_TessLevelOuter[2] = l2;
            gl_TessLevelOuter[3] = l3;

            gl_TessLevelInner[0] = min(l1, l3);
            gl_TessLevelInner[1] = min(l0, l2);
        }
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out[gl_InvocationID].tc = tcs_in[gl_InvocationID].tc;
}
