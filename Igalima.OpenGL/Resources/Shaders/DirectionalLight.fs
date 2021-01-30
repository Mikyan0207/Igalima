#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
  sampler2D Diffuse;
  sampler2D Specular;
  float Shininess;
};

struct Light {
  vec3 Direction;

  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
  vec3 ambient  = light.Ambient  * vec3(texture(material.Diffuse, TexCoords));

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(-light.Direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.Diffuse * diff * vec3(texture(material.Diffuse, TexCoords));

  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
  vec3 specular = light.Specular * spec * vec3(texture(material.Specular, TexCoords));

  FragColor = vec4(ambient + diffuse + specular, 1.0);
}
