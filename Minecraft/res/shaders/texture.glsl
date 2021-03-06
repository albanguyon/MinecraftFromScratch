#shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

// uniform mat4 u_ProjectionView;

out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	
	gl_Position = vec4(a_Position, 1.0, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;

// uniform sampler2D u_Texture;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}