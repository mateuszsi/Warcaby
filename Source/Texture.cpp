#include "Texture.h"

Texture::Texture(void)
{
	glGenTextures(1, &textureID);
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &textureID);
}

void Texture::LoadTexture(const char *path)
{
	int width, height;

	unsigned char *texture = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}