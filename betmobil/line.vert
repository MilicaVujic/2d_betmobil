#version 330 core


layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inCol;
uniform vec2 uPos;



void main()
{

	if(inPos.x==0 && inPos.y==0)
	{
		gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0); 
	}
	else{
		gl_Position = vec4(-uPos.x, uPos.y, 0.0, 1.0); 
	}
}