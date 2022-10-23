#version 330                          
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoords;

in vec3 CharPos;
in vec2 CharCoords;

uniform float iTime;

uniform sampler2D iTexture;
uniform sampler2D iNoiseTexture;

void main(){

    const float sampleSize = 0.1;
    const float mixRatio = 0.5;

    //noise stuff
    vec2 noiseColor = texture(iNoiseTexture,TexCoords+iTime).rr * sampleSize;

    //create backgroun and add noise to it
    vec4 color = Color * texture(iTexture,TexCoords + noiseColor);

    color.z *= sin(iTime);

    FragColor = color;
}
