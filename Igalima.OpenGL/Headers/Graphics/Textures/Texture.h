#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <cstdint>
#include <iostream>

// TODO(mikyan): Rename to GLTexture & move file to OpenGL/
// More configurable options when creating a new texture using a struct (TextureSettings)?

class Texture
{
    public:
    Texture() = default;
	explicit Texture(const std::string& path);
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