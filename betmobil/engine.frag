#version 330 core 

out vec4 outCol; 
uniform float u;

void main() 
{
	outCol = vec4(1.0,1.0-u,1.0-u,1.0);
}