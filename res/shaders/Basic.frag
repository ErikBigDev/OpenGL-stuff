#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
vec4 Color = vec4(gl_FragCoord.x / 480.0f, gl_FragCoord.y / 640.0f, 0.0f, 1.0f);

void main()
{
	color = Color;//u_Color;
};