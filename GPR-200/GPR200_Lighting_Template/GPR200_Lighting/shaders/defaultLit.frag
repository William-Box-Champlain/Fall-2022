#version 330                          
out vec4 FragColor;

in vec3 Color;

in vec3 WorldPos;
in vec3 WorldNormal;

uniform vec3 uLightPos;
uniform vec3 uEyePos;
uniform vec3 uLightColor;

uniform float uAmbiantK;
uniform float uDiffuseK;

void main(){
    vec3 toLight = normalize(uLightPos - WorldPos);
    float d = max(dot(toLight,WorldNormal),0);
    vec3 Diffuse = uLightColor * d * uDiffuseK;

    FragColor = vec4(Color * (uAmbiantK + Diffuse),1.0f);
}
