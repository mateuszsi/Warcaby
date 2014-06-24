#pragma once
#include "Headers.h"
#include "Texture.h"

class Model
{
private:
	int width, height;
	int position[2];

	Texture texture;

public:
	Model(void);
	~Model(void);

	void Init(int width, int height, const char *path);
	void SetPosition(int x, int y);
	void Draw();

	int GetWidth(){return width;}
	int GetHeight(){return height;}
};

