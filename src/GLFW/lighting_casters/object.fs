#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 衰减系数
    float constant;
    float linear;
    float quadratic;
};
uniform Material material;
uniform Light light;

out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
  
uniform vec3 viewPos;

void main()
{
    
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.specular, TexCoords));
    // ambient *= attenuation;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation;

    float theta = dot(lightDir, normalize(-light.direction));
    float episilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / episilon, 0.0, 1.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 s = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * spec * vec3(s.x, s.y, s.z);
    specular *= attenuation;
            
    // if (theta > light.outerCutOff) {
    //     FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    //     return;
    // }
    // if (theta > light.cutOff) {
    //     diffuse *= intensity;
    //     specular *= intensity;
    // }
    if (theta <= light.outerCutOff) {
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
        return;
    }
    if (theta <= light.cutOff) {
        diffuse *= intensity;
        specular *= intensity;
    }
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
} 