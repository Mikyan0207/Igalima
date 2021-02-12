#version 460 core
layout(location = 0) in vec3 mPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D NoiseTexture; // Heightmap
uniform float GridSize;

vec2 GetTextureCoordinates(vec2 pos)
{
  return (pos + vec2(GridSize / 2.0)) / GridSize;
}

vec3 Get3DPos(vec2 pos)
{
  float h = texture(NoiseTexture, GetTextureCoordinates(pos)).r;
  return vec3(pos, h);
}

void main()
{
  gl_Position = projection * view * model * vec4(mPos, 1.0);
}