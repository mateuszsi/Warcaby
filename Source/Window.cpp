#include "Window.h"

Window::Window(void)
{
	width = height = 0;
	name = "";
	window = NULL;
	context = NULL;
}

Window::~Window(void)
{
}

int Window::InitWindow(int w, int h, std::string name)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 0;

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	width = w;
	height = h;
	this->name = name;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	context = SDL_GL_CreateContext(window);
}

void Window::CloseWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Window::SetDrawingCursor(int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0);
}