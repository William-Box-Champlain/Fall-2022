#version 330                          
layout (location = 0) in vec3 in_Pos;  
layout (location = 1) in vec4 in_Color; 
layout (location = 2) in vec2 in_TexCoords;

uniform float iTime;

out vec4 Color;
out vec2 TexCoords;

out vec2 CharCoords;

void main(){
    Color = in_Color;
    TexCoords = in_TexCoords;
    vec4 netPos = vec4(in_Pos,1.0);
    netPos.x /= 2;
    netPos.y /= 2;

    netPos.x += cos(iTime)/2;
    netPos.y += sin(iTime)/2;

    gl_Position = netPos;    
}
