#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
//vec4 Color = vec4(gl_FragCoord.x / 480.0f, gl_FragCoord.y / 640.0f, 0.0f, 1.0f);
in vec2 v_TexCoord;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
	color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
};