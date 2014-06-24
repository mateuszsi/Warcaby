#pragma once

#include "Headers.h"
#include "Model.h"
#include "Window.h"
#include "Pionek.h"
#include <vector>
#include <fstream>
#include <FANN\fann.h>

#pragma comment(lib, "fannfloat.lib")

struct Pole
{
	char kolor;
	bool wolne;
};

struct Zrzut
{
	float pole[8][8];
	int wyjscia[12];

	Zrzut()
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				pole[i][j] = 0;
			}
		}

		for(int i=0; i<12; i++)
			wyjscia[i] = 0;
	}
};

class Plansza
{
private:
	Pole plansza[8][8];
	Pionek biale[8];
	Pionek czarne[8];
	Model pole;
	Model bialyPionek;
	Model czarnyPionek[8];
	Model bialaDamka;
	Model czarnaDamka[8];
	int iloscBialych;
	int iloscCzarnych;
	int czarnyRuch;
	int bialyRuch;
	int rodzajRuchu;

	int iloscPrzejsc;
	std::vector <Zrzut> zrzutPlanszy;

	struct fann *network;
	
public:
	Plansza(void);
	~Plansza(void);

	void Init();
	void StartGame();
	void CheckBoardCollision(int x, int y, int *tab);
	void Draw(Window window);
	void DrawPawns(Window window);
	void ClearMoves();
	void UpdateMoves();

	void DaneUczacePlansza();
	void ZapiszDaneUczace();
	void DaneUczaceRuch();
	void DestroyNetwork();
	void RunNetwork();

	void WhitePawnsCollision(int x, int y);
	void WhiteCheckMoves(int i);
	void WhiteMove(int *pos);
	void WhiteChangePosition(int x, int y, int *pos, int a, int i);
	void WhiteCheckMove(int x, int y, int i);
	void WhiteDestroy();
	void CheckMoves();

	void BlackPawnsCollision(int x, int y);
	void BlackCheckMove(int x, int y, int i);
	void BlackChangePosition(int x, int y, int *pos, int a, int i);
	void BlackMove(int *pos);
	void BlackCheckMoves(int i);
	void BlackDestroy();

	bool CheckIfOnBoard(int x, int y);
	int CheckWin();
};

