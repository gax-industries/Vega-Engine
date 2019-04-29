#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv_albedo;

layout(location = 0) out vec3 pos_out;
layout(location = 1) out vec3 normal_out;
layout(location = 2) out vec2 uv_albedo_out;

uniform mat4 mvp;
uniform mat4 world;
uniform mat4 rot;

void main(void)
{
    vec4 p = vec4((pos - 0.5) * 16000.0, 1.0);
    vec4 n = vec4(normal, 1.0);
    vec4 p_s = mvp * p;

    gl_Position = p_s;
    pos_out = (world * p).xyz;
    normal_out = (rot * n).xyz;
    uv_albedo_out = uv_albedo;
}
