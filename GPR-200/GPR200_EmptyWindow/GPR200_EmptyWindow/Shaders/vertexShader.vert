#version 330							
layout (location = 0) in vec3 in_Pos;	
layout (location = 1) in vec4 in_Color;
										
out vec4 Color;						
uniform float iTime;					
void main()							
{										
	Color = in_Color;					
	vec3 pos = in_Pos;					
	pos.y += sin(iTime)/3;				
	pos.y += sin(pos.x + iTime)/3;		
	pos.x += cos(iTime)/3;				
	pos.x += cos(pos.y + iTime)/3;		
	gl_Position = vec4(pos,1.0);		
};										