#include "Render.h"

void Update(Plansza &plansza, SDL_Event e, int &zabezpieczenie, bool &start, ClassButton &przycisk, char &tura, bool &gramy)
{
	int curX, curY;
	int pos[2] = {-1, -1};
	SDL_GetMouseState(&curX, &curY);

	int win = plansza.CheckWin();
	if(win == 1)
	{
		gramy = false;
		std::cout << "Czarne wygraly";
	}
	if(win == 2)
	{
		gramy = false;
		std::cout << "Biale wygraly";
	}

	if(gramy == true)
	{
		if(start == true)
			start = false;

		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(zabezpieczenie == 0)
			{
				if(przycisk.CheckCollision(curX, curY) == true)
				{
					if(tura == 'b')
					{
						//plansza.WhiteDestroy();
						tura = 'c';
						plansza.ClearMoves();
						plansza.CheckMoves();
						////////////////////// Tutaj zrzut planszy
						plansza.DaneUczacePlansza();
						plansza.RunNetwork();
						plansza.CheckMoves();
					}
					else
					{
						////////////////////// Tutaj zapisz ruch
						plansza.DaneUczaceRuch();
						//plansza.BlackDestroy();
						tura = 'b';
						plansza.ClearMoves();
					}
					start = true;
				}

				plansza.CheckMoves();
				plansza.UpdateMoves();
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					if(tura == 'b')
						plansza.WhitePawnsCollision(curX, curY);
					if(tura == 'c')
						plansza.BlackPawnsCollision(curX, curY);
				}
				if(e.button.button == SDL_BUTTON_RIGHT)
				{
					plansza.CheckBoardCollision(curX, curY, pos);
					if(tura == 'c')
						plansza.BlackMove(pos);
					if(tura == 'b')
						plansza.WhiteMove(pos);
				}
			}

			zabezpieczenie++;
		}
		if(e.type == SDL_MOUSEBUTTONUP)
			zabezpieczenie = 0;
	}
}

void Render(Window window, Plansza &plansza, ClassButton &przycisk)
{
	glViewport(0,0, window.GetWidth(), window.GetHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.GetWidth(), window.GetHeight(), 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	plansza.Draw(window);
	plansza.DrawPawns(window);
	przycisk.Draw(window);

	window.SwapBuffers();
}