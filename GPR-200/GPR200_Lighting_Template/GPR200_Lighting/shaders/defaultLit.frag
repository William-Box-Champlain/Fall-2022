#version 330
out vec4 FragColor;

in vec3 Color;

in vec3 WorldPos;
in vec3 WorldNormal;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

uniform Light light;

uniform vec3 uEyePos;

void main(){
    vec3 ambient = light.ambient * material.ambient;
    
    vec3 toLight = normalize(light.position - WorldPos);
    float d = max(dot(toLight,WorldNormal),0);
    vec3 diffuse = light.diffuse * d * material.diffuse;

    vec3 toEye = normalize(uEyePos - WorldPos);
    vec3 reflectDir = reflect(-toLight,WorldNormal);
    float s = pow(max(dot(reflectDir,toEye),0),material.shininess);
    vec3 specular = light.specular * s * material.specular;

    FragColor = vec4((ambient + diffuse + specular),1.0f);
}
