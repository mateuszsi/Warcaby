#pragma once

#include "Headers.h"
#include "Model.h"
#include "Window.h"

class ClassButton
{
private:
	Model button;
	int x, y;

public:
	ClassButton(void);
	~ClassButton(void);

	void Init();
	bool CheckCollision(int x, int y);
	void Draw(Window window);
};

