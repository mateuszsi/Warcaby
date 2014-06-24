#include "ClassButton.h"

ClassButton::ClassButton(void)
{
	x = y = 0;
}

ClassButton::~ClassButton(void)
{
}

void ClassButton::Init()
{
	button.Init(400, 100, "Textury\\Tura.jpg");
	x = 0;
	y = 400;
}

bool ClassButton::CheckCollision(int x, int y)
{
	if((x > this->x) && (x < this->x+400))
	{
		if((y > this->y) && (y < this->y+100))
			return true;
	}

	return false;
}

void ClassButton::Draw(Window window)
{
	window.SetDrawingCursor(x, y);
	button.Draw();
}