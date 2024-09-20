#version 330 core

out vec4 outCol;
uniform float u;

void main()
{
	outCol = vec4(0.0, 0.0+u, 0.0+u, 1.0);
}