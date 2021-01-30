#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
}; 

struct Light {
    vec3 Position;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
	
    float Constant;
    float Linear;
    float Quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.Ambient * texture(material.Diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.Position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.Diffuse * diff * texture(material.Diffuse, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    vec3 specular = light.Specular * spec * texture(material.Specular, TexCoords).rgb;
    
    // attenuation
    float distance = length(light.Position - FragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 