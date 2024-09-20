#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inCol;
out vec3 chCol;

void main()
{
	
	if(inPos.x==-0.75 && inPos.y==0.5)
	{
		gl_Position = vec4(inPos, 0.0, 1.0);
	}
	else
	{
		gl_Position = vec4(inPos.x-0.75,inPos.y+0.5, 0.0, 1.0);
	}
	chCol = inCol;
}