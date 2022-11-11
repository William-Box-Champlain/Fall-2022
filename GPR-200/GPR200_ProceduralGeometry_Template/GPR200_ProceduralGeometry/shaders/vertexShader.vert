#version 330                          
layout (location = 0) in vec3 in_Pos;  
layout (location = 1) in vec3 in_Color; 

out vec3 Color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){       
    Color = in_Color;
    vec4 WorldPos = Model * vec4(in_Pos,1.0);
    gl_Position = Projection * View * WorldPos;
}
