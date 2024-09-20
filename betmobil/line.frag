#version 330 core 

out vec4 outCol;
uniform float u;

void main() 
{
	outCol = vec4(abs(0.7-u),abs(0.3-u),abs(0.5-u),1.0);
}