#include "Headers.h"
#include "Render.h"

int main(int argc, char *argv[])
{
	Window window;
	window.InitWindow(400, 500, "Warcaby");

	Plansza plansza;
	ClassButton przycisk;
	
	SDL_Event e;

	glClearColor(0,0,0,0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	przycisk.Init();
	plansza.Init();
	plansza.StartGame();

	bool gramy = true;
	bool start = true;
	int zabezpieczenie = 0;
	char tura = 'b';
	while(gramy)
	{
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
			break;

		Update(plansza, e, zabezpieczenie, start, przycisk, tura, gramy);
		Render(window, plansza, przycisk);
	}

	plansza.ZapiszDaneUczace();
	plansza.DestroyNetwork();

	window.CloseWindow();

	return 0;
}