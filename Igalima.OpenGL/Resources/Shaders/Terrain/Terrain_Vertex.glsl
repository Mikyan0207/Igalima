#version 460 core
layout(location = 0) in vec2 mPos;

out vec2 TexCoords;
out float Height;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform sampler2D NoiseTexture; // Heightmap
uniform float GridSize;
uniform int GridDimensions;

vec2 GetUVCoords(vec2 pos)
{
  return (pos + vec2(GridSize / 2.0)) / GridSize;
}

vec3 Get3DCoords(vec2 pos)
{
  vec2 uv = GetUVCoords(pos);
  float h = texture(NoiseTexture, uv).r;

  return vec3(pos.x, h, pos.y);
}

void main()
{
  vec4 worldPos = model * vec4(Get3DCoords(mPos), 1.0);

  gl_Position = projection * view * worldPos;
  TexCoords = GetUVCoords(mPos);
}