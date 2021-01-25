#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <cstdint>
#include <iostream>

class Texture
{
public:
	Texture();
	Texture(const Texture&) = default;
	Texture(Texture&&) noexcept = default;
	~Texture() = default;

public:
	Texture& operator=(const Texture&) = default;
	Texture& operator=(Texture&&) noexcept = default;

public:
	void Bind();

public:
	uint32_t TextureId;
	int Width;
	int Height;
	int Channels;
};