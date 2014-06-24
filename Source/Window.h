#pragma once

#include "Headers.h"

class Window
{
private:
	SDL_Window *window;
	SDL_GLContext context;
	int width, height;
	std::string name;

public:
	Window(void);
	~Window(void);

	int InitWindow(int w, int h, std::string name);
	int GetWidth(){return width;}
	int GetHeight(){return height;}
	void CloseWindow();
	void SwapBuffers();
	void SetDrawingCursor(int x, int y);
};

