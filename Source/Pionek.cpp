#include "Pionek.h"

Pionek::Pionek(void)
{
	rodzaj = 0;
	move = 0;
	x = y = 0;
	focus = false;
	active = false;
}

Pionek::~Pionek(void)
{
}

void Pionek::Start(int x, int y)
{
	rodzaj = 1;
	this->x = x;
	this->y = y;
	active = true;
	moveDone = false;
}

void Pionek::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Pionek::CheckCollision(int x, int y)
{
	if((x > this->x*50) && (x < this->x*50+50))
	{
		if((y > this->y*50) && (y < this->y*50+50))
			return true;
	}

	return false;
}