#version 330                          
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoords;

uniform float iTime;
uniform sampler2D iTexture;

void main(){          
    vec4 color = texture(iTexture,TexCoords);
    FragColor = color;
}
