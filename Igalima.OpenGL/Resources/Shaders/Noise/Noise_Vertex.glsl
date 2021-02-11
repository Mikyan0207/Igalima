#version 460 core

layout(location = 0) in vec3 mPosition;

in vec2 mTexCoords;

out vec2 TexCoords;

void main()
{
  gl_Position = vec4(mPosition, 1.0);
  TexCoords = mTexCoords;
}