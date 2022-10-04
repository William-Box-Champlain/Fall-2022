#version 330                          
layout (location = 0) in vec3 in_Pos;  
layout (location = 1) in vec4 in_Color; 
layout (location = 2) in vec2 in_TexCoords;

out vec4 Color;
out vec2 TexCoords;

void main(){
    Color = in_Color;
    TexCoords = in_TexCoords;
    gl_Position = vec4(in_Pos,1.0);    
}
