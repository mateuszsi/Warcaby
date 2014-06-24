#pragma once
#include "Headers.h"

class Texture
{
private:
	GLuint textureID;

public:
	Texture(void);
	~Texture(void);

	void BindTexture();
	void LoadTexture(const char *path);
};

