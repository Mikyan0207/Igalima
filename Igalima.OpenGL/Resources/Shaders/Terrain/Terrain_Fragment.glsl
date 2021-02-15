#version 460 core

in vec2 TexCoords;
in float Height;

out vec4 FragColor;

// Textures
uniform sampler2D GrassTexture;
uniform sampler2D StoneTexture;
uniform sampler2D SnowTexture;

// vec3 ComputeColor()
// {
//   vec3 grass = texture(GrassTexture, TexCoords).rgb;
//   vec3 stone = texture(StoneTexture, TexCoords).rgb;
//   vec3 snow = texture(SnowTexture, TexCoords).rgb;
// }

void main()
{
  if (Height <= 0.5)
    FragColor = mix(texture(GrassTexture, TexCoords), texture(StoneTexture, TexCoords), 1.0);
  else if (Height <= 1.50)
    FragColor = texture(StoneTexture, TexCoords);
  else
    FragColor = texture(SnowTexture, TexCoords);
}