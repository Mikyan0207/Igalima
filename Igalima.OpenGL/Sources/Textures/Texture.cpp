#include "..\..\Headers\Textures\Texture.h"

Texture::Texture(const std::string& path)
{
	TextureId = 0;
	Width = 0;
	Height = 0;
	Channels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &Width, &Height, &Channels, 0);

	if (data == nullptr)
	{
		std::cerr << "Failed to load texture." << std::endl;
		return;
	}

	GLenum format = GL_RGB;
	if (Channels == 1)
		format = GL_RED;
	else if (Channels == 3)
		format = GL_RGB;
	else if (Channels == 4)
		format = GL_RGBA;

	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextureId);
}
