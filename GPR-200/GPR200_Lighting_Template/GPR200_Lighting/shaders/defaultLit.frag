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
uniform float uSpecularK;

void main(){
    vec3 ambiant = uLightColor * uAmbiantK;
    
    vec3 toLight = normalize(uLightPos - WorldPos);
    float d = max(dot(toLight,WorldNormal),0);
    vec3 diffuse = uLightColor * d * uDiffuseK;

    vec3 toEye = normalize(uEyePos - WorldPos);
    vec3 reflectDir = reflect(-toLight,WorldNormal);
    float s = max(dot(reflectDir,toEye),0);
    vec3 specular = uLightColor * s * uSpecularK;

    FragColor = vec4(Color * (ambiant + diffuse + specular),1.0f);
}
