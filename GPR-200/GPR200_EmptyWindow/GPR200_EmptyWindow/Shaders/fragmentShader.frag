#version 330								
out vec4 FragColor;						
in vec4 Color;								
uniform float iTime;						
void main()								
{											
	FragColor = abs(sin(iTime))*Color;		
}											