#version 330 core

layout(location = 0) in vec2 inPos; 
uniform float uP;
void main()
{
	if(inPos.y==-0.85)
	{
		gl_Position = vec4(inPos, 0.0, 1.0); 
	}
	else
	{
			gl_Position = vec4(inPos.x,inPos.y+uP, 0.0, 1.0); 
	}

}