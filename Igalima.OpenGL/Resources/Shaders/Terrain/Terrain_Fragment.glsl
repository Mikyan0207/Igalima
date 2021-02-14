#version 460 core

in vec2 TexCoords;

out vec4 FragColor;

// Textures
uniform sampler2D GrassTexture;

void main()
{
  FragColor = texture(GrassTexture, TexCoords);
}