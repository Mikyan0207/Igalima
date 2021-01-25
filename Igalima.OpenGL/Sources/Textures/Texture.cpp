#include "..\..\Headers\Textures\Texture.h"

Texture::Texture()
{
	TextureId = 0;
	Width = 0;
	Height = 0;
	Channels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Resources/peko.jpg", &Width, &Height, &Channels, 0);

	if (data == nullptr)
	{
		std::cerr << "Failed to load texture." << std::endl;
		return;
	}

	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextureId);
}
