#version 460 core
layout(location = 0) in vec3 mPos;
layout(location = 1) in vec2 mTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D NoiseTexture; // Heightmap

void main()
{
  float height = texture(NoiseTexture, mTexCoords).r;

  height = height * 400.0;

  vec4 worldPos = model * vec4(mPos.x, height, mPos.z, 1.0);

  gl_Position = projection * view * worldPos;
}