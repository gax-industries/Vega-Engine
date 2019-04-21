#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv_albedo;
layout (location = 3) in vec2 uv_lightmap;

layout (binding = 0) uniform sampler2D tex_lightmap;
layout (binding = 1) uniform sampler2D tex_albedo;

out vec4 color;

uniform float aperture;
uniform vec3 l_dir;
uniform vec3 p_cam;

void main(void)
{
	vec3 blue = (vec3(94.0, 155.0, 255.0) / 255.0) * 0.001;
	vec3 light = texture(tex_lightmap, uv_lightmap).xyz + blue;

    light = vec3(max(0.0, dot(normal, l_dir)));
    float ff = pos.y < -42.0 ? (1.0 - min(1.0, (-pos.y - 42.0) / 40.0)) * 0.6 + 0.1 : 1.0;
	color = vec4(light * texture(tex_albedo, uv_albedo).xyz * vec3(ff, ff, 1.0), 1.0);
}