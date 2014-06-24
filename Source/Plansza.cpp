#include "Plansza.h"


Plansza::Plansza(void)
{
	iloscBialych = 0;
	iloscCzarnych = 0;
	bialyRuch = -1;
	czarnyRuch = -1;
	iloscPrzejsc = 0;
	rodzajRuchu = -1;

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
			plansza[i][j].wolne = true;
	}
}

Plansza::~Plansza(void)
{
}

void Plansza::Init()
{
	pole.Init(50, 50, "Textury\\BialePole.jpg");
	bialyPionek.Init(50, 50, "Textury\\BialyPionek.png");
	//czarnyPionek.Init(50, 50, "Textury\\CzarnyPionek.png");
	bialaDamka.Init(50, 50, "Textury\\BialaDamka.png");
	czarnaDamka[0].Init(50, 50, "Textury\\CzarnaDamka0.png");
	czarnaDamka[1].Init(50, 50, "Textury\\CzarnaDamka1.png");
	czarnaDamka[2].Init(50, 50, "Textury\\CzarnaDamka2.png");
	czarnaDamka[3].Init(50, 50, "Textury\\CzarnaDamka3.png");
	czarnaDamka[4].Init(50, 50, "Textury\\CzarnaDamka4.png");
	czarnaDamka[5].Init(50, 50, "Textury\\CzarnaDamka5.png");
	czarnaDamka[6].Init(50, 50, "Textury\\CzarnaDamka6.png");
	czarnaDamka[7].Init(50, 50, "Textury\\CzarnaDamka7.png");
	czarnyPionek[0].Init(50, 50, "Textury\\Czrny0.png");
	czarnyPionek[1].Init(50, 50, "Textury\\Czrny1.png");
	czarnyPionek[2].Init(50, 50, "Textury\\Czrny2.png");
	czarnyPionek[3].Init(50, 50, "Textury\\Czrny3.png");
	czarnyPionek[4].Init(50, 50, "Textury\\Czrny4.png");
	czarnyPionek[5].Init(50, 50, "Textury\\Czrny5.png");
	czarnyPionek[6].Init(50, 50, "Textury\\Czrny6.png");
	czarnyPionek[7].Init(50, 50, "Textury\\Czrny7.png");

	std::fstream file;
	file.open("plansza.data");
	char temp;

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			file >> temp;
			plansza[i][j].kolor = temp;
		}
	}

	file.close();

	network = fann_create_from_file("Warcaby.net");
}

void Plansza::DestroyNetwork()
{
	fann_destroy(network);
}

void Plansza::RunNetwork()
{
	fann_type input[64];
	fann_type *out;
	for(int i=0; i<64; i++)
		input[i] = 0;

	for(int i=0; i<8; i++)
	{
		int x, y;
		float temp;
		if(czarne[i].GetActive() == true)
		{
			x = czarne[i].GetX();
			y = czarne[i].GetY();
			temp = i * 0.1f + 0.1f;
			if(czarne[i].GetRodzaj() == 2)
				temp += 0.05f;
			input[x*8+y] = temp;
		}
		if(biale[i].GetActive() == true)
		{
			x = biale[i].GetX();
			y = biale[i].GetY();
			temp = i * (-0.1f) - 0.1f;
			if(biale[i].GetRodzaj() == 2)
				temp -= 0.05f;
			input[x*8+y] = temp;
		}
	}

	out = fann_run(network, input);

	int indexPionka;
	fann_type temp = 0;
	for(int i=0; i<8; i++)
	{
		if(temp < out[i] && czarne[i].GetMove() != 0 && czarne[i].GetActive() == true)
		{
			temp = out[i];
			indexPionka = i;
		}
	}
	std::cout << indexPionka << std::endl;
	temp = -2;
	int indexRuchu;
	
	ClearMoves();
	int x = czarne[indexPionka].GetX();
	int y = czarne[indexPionka].GetY();

	if(CheckIfOnBoard(x-1, y+1))
	{
		BlackCheckMove(x-1, y+1, indexPionka);
		if(czarne[indexPionka].GetMove() != 0)
		{
			if(temp < out[8])
			{
				temp = out[8];
				indexRuchu = 0;
			}
		}
	}
	if(CheckIfOnBoard(x+1, y+1))
	{
		BlackCheckMove(x+1, y+1, indexPionka);
		if(czarne[indexPionka].GetMove() != 0)
		{
			if(temp < out[9])
			{
				temp = out[9];
				indexRuchu = 1;
			}
		}
	}
	if(czarne[indexPionka].GetRodzaj() == 2)
	{
		if(CheckIfOnBoard(x-1, y-1))
		{
			BlackCheckMove(x-1, y-1, indexPionka);
			if(czarne[indexPionka].GetMove() != 0)
			{
				if(temp < out[11])
				{
					temp = out[11];
					indexRuchu = 3;
				}
			}
		}
		if(CheckIfOnBoard(x+1, y-1))
		{
			BlackCheckMove(x+1, y-1, indexPionka);
			if(czarne[indexPionka].GetMove() != 0)
			{
				if(temp < out[10])
				{
					temp = out[10];
					indexRuchu = 2;
				}
			}
		}
	}
	std::cout << indexRuchu << std::endl << std::endl;
}

void Plansza::StartGame()
{
	biale[0].Start(1,7);
	biale[1].Start(3,7);
	biale[2].Start(5,7);
	biale[3].Start(7,7);
	biale[4].Start(6,6);
	biale[5].Start(4,6);
	biale[6].Start(2,6);
	biale[7].Start(0,6);

	czarne[0].Start(0,0);
	czarne[1].Start(2,0);
	czarne[2].Start(4,0);
	czarne[3].Start(6,0);
	czarne[4].Start(7,1);
	czarne[5].Start(5,1);
	czarne[6].Start(3,1);
	czarne[7].Start(1,1);

	iloscBialych = 8;
	iloscCzarnych = 8;

	for(int i=0; i<8; i++)
	{
		if(biale[i].GetActive() == true)
		{
			int x = biale[i].GetX();
			int y = biale[i].GetY();
			plansza[x][y].wolne = false;
			x = czarne[i].GetX();
			y = czarne[i].GetY();
			plansza[x][y].wolne = false;
		}
	}
}

void Plansza::DaneUczacePlansza()
{
	zrzutPlanszy.push_back(Zrzut());

	for(int i=0; i<8; i++)
	{
		int x, y;
		float temp;
		if(czarne[i].GetActive() == true)
		{
			x = czarne[i].GetX();
			y = czarne[i].GetY();
			temp = i * 0.1f + 0.1f;
			if(czarne[i].GetRodzaj() == 2)
				temp += 0.05f;
			zrzutPlanszy[iloscPrzejsc].pole[x][y] = temp;
		}
		if(biale[i].GetActive() == true)
		{
			x = biale[i].GetX();
			y = biale[i].GetY();
			temp = i * (-0.1f) - 0.1f;
			if(biale[i].GetRodzaj() == 2)
				temp -= 0.05f;
			zrzutPlanszy[iloscPrzejsc].pole[x][y] = temp;
		}
	}

	iloscPrzejsc++;
}

void Plansza::DaneUczaceRuch()
{
	zrzutPlanszy[iloscPrzejsc-1].wyjscia[czarnyRuch] = 1;
	if(rodzajRuchu >= 0)
		zrzutPlanszy[iloscPrzejsc-1].wyjscia[rodzajRuchu+8] = 1;
}

void Plansza::ZapiszDaneUczace()
{
	std::fstream file;
	file.open("Partia.data", std::ios::out);

	file << iloscPrzejsc << std::endl;

	for(int k=0; k<iloscPrzejsc; k++)
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				file << zrzutPlanszy[k].pole[i][j] << " ";
			}
		}
		file << std::endl;
		for(int i=0; i<12; i++)
			file << zrzutPlanszy[k].wyjscia[i] << " ";
		file << std::endl;
	}

	file.close();
}

void Plansza::WhiteDestroy()
{
	CheckMoves();

	for(int i=0; i<8; i++)
	{
		if(bialyRuch == i)
			continue;

		if(biale[i].GetActive() == true)
		{
			if(biale[i].GetMove() == 2)
			{
				biale[i].SetActive(false);
				plansza[biale[i].GetX()][biale[i].GetY()].wolne = true;
				iloscBialych--;
			}
		}
	}

	bialyRuch = -1;
}

void Plansza::BlackDestroy()
{
	CheckMoves();

	for(int i=0; i<8; i++)
	{
		if(czarnyRuch == i)
			continue;

		if(czarne[i].GetActive() == true)
		{
			if(czarne[i].GetMove() == 2)
			{
				czarne[i].SetActive(false);
				plansza[czarne[i].GetX()][czarne[i].GetY()].wolne = true;
				iloscCzarnych--;
			}
		}
	}

	czarnyRuch = -1;
}

void Plansza::WhitePawnsCollision(int x, int y)
{
	for(int i=0; i<8; i++)
		biale[i].SetFocus(false);

	for(int i=0; i<8; i++)
		if(biale[i].GetActive() == true)
		{
			if(biale[i].CheckCollision(x, y))
				biale[i].SetFocus(true);
		}
}

void Plansza::BlackPawnsCollision(int x, int y)
{
	for(int i=0; i<8; i++)
		czarne[i].SetFocus(false);

	for(int i=0; i<8; i++)
		if(czarne[i].GetActive() == true)
		{
			if(czarne[i].CheckCollision(x, y))
				czarne[i].SetFocus(true);
		}
}

void Plansza::CheckBoardCollision(int x, int y, int *tab)
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if((x > i*50) && (x < i*50+50))
			{
				if((y > j*50) && (y < j*50+50))
				{
					tab[0] = i;
					tab[1] = j;
				}
			}
		}
	}
}

void Plansza::ClearMoves()
{
	for(int i=0; i<8; i++)
	{
		biale[i].SetMove(0);
		biale[i].SetMoveDone(false);
		czarne[i].SetMove(0);
		czarne[i].SetMoveDone(false);
	}
}

void Plansza::UpdateMoves()
{
	for(int i=0; i<8; i++)
	{
		biale[i].SetMove(0);
		czarne[i].SetMove(0);
	}
}

void Plansza::WhiteCheckMove(int x, int y, int i)
{
	if(plansza[x][y].wolne == true)
	{
		if(biale[i].GetMove() == 0)
			biale[i].SetMove(1);
	}
	else
	{
		for(int j=0; j<8; j++)
		{
			if(czarne[j].GetX() == x && czarne[j].GetY() == y)
			{
				int a = x - biale[i].GetX();
				int b = y - biale[i].GetY();
				a += x;
				b += y;
				if(CheckIfOnBoard(a, b))
				{
					if(plansza[a][b].wolne == true)
						biale[i].SetMove(2);
					else
					{
						if(biale[i].GetMove() == 0)
							biale[i].SetMove(0);	
					}
				}
				else
				{
					if(biale[i].GetMove() == 0)
						biale[i].SetMove(0);
				}
			}
			else
			{
				if(biale[i].GetMove() == 0)
					biale[i].SetMove(0);
			}
		}
	}
}

void Plansza::BlackCheckMove(int x, int y, int i)
{
	if(plansza[x][y].wolne == true)
	{
		if(czarne[i].GetMove() == 0)
			czarne[i].SetMove(1);
	}
	else
	{
		for(int j=0; j<8; j++)
		{
			if(biale[j].GetX() == x && biale[j].GetY() == y)
			{
				int a = x - czarne[i].GetX();
				int b = y - czarne[i].GetY();
				a += x;
				b += y;
				if(CheckIfOnBoard(a, b))
				{
					if(plansza[a][b].wolne == true)
						czarne[i].SetMove(2);
					else
					{
						if(czarne[i].GetMove() == 0)
							czarne[i].SetMove(0);	
					}
				}
				else
				{
					if(czarne[i].GetMove() == 0)
						czarne[i].SetMove(0);
				}
			}
			else
			{
				if(czarne[i].GetMove() == 0)
					czarne[i].SetMove(0);
			}
		}
	}
}


void Plansza::CheckMoves()
{
	for(int i=0; i<8; i++)
	{
		WhiteCheckMoves(i);
		BlackCheckMoves(i);
	}
}

void Plansza::WhiteChangePosition(int x, int y, int *pos, int a, int i)
{
	if(a == 1)
	{
		plansza[x][y].wolne = true;
		plansza[pos[0]][pos[1]].wolne = false;
		biale[i].SetPosition(pos[0], pos[1]);
	}
	else
	{
		plansza[x][y].wolne = true;
		int a = 2 * pos[0] - x;
		int b = 2 * pos[1] - y;
		plansza[a][b].wolne = false;
		plansza[pos[0]][pos[1]].wolne = true;
		biale[i].SetPosition(a, b);
	}
}

void Plansza::BlackChangePosition(int x, int y, int *pos, int a, int i)
{
	if(a == 1)
	{
		plansza[x][y].wolne = true;
		plansza[pos[0]][pos[1]].wolne = false;
		czarne[i].SetPosition(pos[0], pos[1]);
	}
	else
	{
		plansza[x][y].wolne = true;
		int a = 2 * pos[0] - x;
		int b = 2 * pos[1] - y;
		plansza[a][b].wolne = false;
		plansza[pos[0]][pos[1]].wolne = true;
		czarne[i].SetPosition(a, b);
	}
}

void Plansza::WhiteCheckMoves(int i)
{
	int y = biale[i].GetY() - 1;
	int x = biale[i].GetX() + 1;
	WhiteCheckMove(x, y, i);
	x = biale[i].GetX() - 1;
	WhiteCheckMove(x, y, i);
	if(biale[i].GetRodzaj() == 2)
	{
		y = biale[i].GetY() + 1;
		WhiteCheckMove(x, y, i);
		x = biale[i].GetX() + 1;
		WhiteCheckMove(x, y, i);
	}
}

void Plansza::BlackCheckMoves(int i)
{
	int y = czarne[i].GetY() + 1;
	int x = czarne[i].GetX() + 1;
	BlackCheckMove(x, y, i);
	x = czarne[i].GetX() - 1;
	BlackCheckMove(x, y, i);
	if(czarne[i].GetRodzaj() == 2)
	{
		y = czarne[i].GetY() - 1;
		BlackCheckMove(x, y, i);
		x = czarne[i].GetX() + 1;
		BlackCheckMove(x, y, i);
	}
}

void Plansza::WhiteMove(int *pos)
{
	bool md = false;
	bool ad = false;

	for(int i=0; i<8; i++)
	{
		if(biale[i].GetFocus() == true && biale[i].GetMOveDone() == false)
		{
			if(pos[0] == biale[i].GetX()+1 || pos[0] == biale[i].GetX()-1)
			{
				if(biale[i].GetRodzaj() == 1)
				{
					if(pos[1] == biale[i].GetY()-1)
					{
						WhiteCheckMove(pos[0], pos[1], i);
						if(biale[i].GetMove() == 1)
						{
							WhiteChangePosition(biale[i].GetX(), biale[i].GetY(), pos, 1, i);
							md = true;
							bialyRuch = i;
						}

						if(biale[i].GetMove() == 2)
						{
							WhiteChangePosition(biale[i].GetX(), biale[i].GetY(), pos, 0, i);
							for(int j=0; j<8; j++)
							{
								if(czarne[j].GetX() == pos[0] && czarne[j].GetY() == pos[1])
								{
									md = true;
									ad = true;
									bialyRuch = i;
									czarne[j].SetActive(false);
									iloscCzarnych--;
								}
							}
						}
					}
				}
				if(biale[i].GetRodzaj() == 2)
				{
					if(pos[1] == biale[i].GetY()+1 || pos[1] == biale[i].GetY()-1)
					{
						WhiteCheckMove(pos[0], pos[1], i);
						if(biale[i].GetMove() == 1)
						{
							md = true;
							bialyRuch = i;
							WhiteChangePosition(biale[i].GetX(), biale[i].GetY(), pos, 1, i);
						}
							
						if(biale[i].GetMove() == 2)
						{
							WhiteChangePosition(biale[i].GetX(), biale[i].GetY(), pos, 0, i);
							for(int j=0; j<8; j++)
							{
								if(czarne[j].GetX() == pos[0] && czarne[j].GetY() == pos[1])
								{
									md = true;
									ad = true;
									bialyRuch = i;
									czarne[j].SetActive(false);
									iloscCzarnych--;
								}
							}
						}
					}
				}
			}

			if(biale[i].GetY() == 0)
				biale[i].SetRodzaj(2);

			for(int k=0; k<8; k++)
			{
				if(md == true)
					biale[k].SetMoveDone(true);
			}
			if(ad == true)
			{
				WhiteCheckMoves(i);
				if(biale[i].GetMove() == 2)
					biale[i].SetMoveDone(false);
			}
		}
	}
}

void Plansza::BlackMove(int *pos)
{
	bool md = false;
	bool ad = false;

	for(int i=0; i<8; i++)
	{
		if(czarne[i].GetFocus() == true && czarne[i].GetMOveDone() == false)
		{
			if(pos[0] == czarne[i].GetX()+1 || pos[0] == czarne[i].GetX()-1)
			{
				if(czarne[i].GetRodzaj() == 1)
				{
					if(pos[1] == czarne[i].GetY()+1)
					{
						BlackCheckMove(pos[0], pos[1], i);
						if(czarne[i].GetMove() == 1)
						{
							md = true;
							czarnyRuch = i;
							if(pos[0] < czarne[i].GetX())
								rodzajRuchu = 0;
							if(pos[0] > czarne[i].GetX())
								rodzajRuchu = 1;
							BlackChangePosition(czarne[i].GetX(), czarne[i].GetY(), pos, 1, i);
						}

						if(czarne[i].GetMove() == 2)
						{
							BlackChangePosition(czarne[i].GetX(), czarne[i].GetY(), pos, 0, i);
							for(int j=0; j<8; j++)
							{
								if(biale[j].GetX() == pos[0] && biale[j].GetY() == pos[1])
								{
									md = true;
									ad = true;
									czarnyRuch = i;
									if(pos[0] < czarne[i].GetX())
										rodzajRuchu = 0;
									if(pos[0] > czarne[i].GetX())
										rodzajRuchu = 1;
									biale[j].SetActive(false);
									iloscBialych--;
								}
							}
						}
					}
				}
				if(czarne[i].GetRodzaj() == 2)
				{
					if(pos[1] == czarne[i].GetY()+1 || pos[1] == czarne[i].GetY()-1)
					{
						BlackCheckMove(pos[0], pos[1], i);
						if(czarne[i].GetMove() == 1)
						{
							md = true;
							czarnyRuch = i;
							if(pos[0] < czarne[i].GetX())
								rodzajRuchu = 3;
							if(pos[0] > czarne[i].GetX())
								rodzajRuchu = 2;
							BlackChangePosition(czarne[i].GetX(), czarne[i].GetY(), pos, 1, i);
						}
							
						if(czarne[i].GetMove() == 2)
						{
							BlackChangePosition(czarne[i].GetX(), czarne[i].GetY(), pos, 0, i);
							for(int j=0; j<8; j++)
							{
								if(biale[j].GetX() == pos[0] && biale[j].GetY() == pos[1])
								{
									md = true;
									ad = true;
									czarnyRuch = i;
									if(pos[0] < czarne[i].GetX())
										rodzajRuchu = 3;
									if(pos[0] > czarne[i].GetX())
										rodzajRuchu = 2;
									biale[j].SetActive(false);
									iloscBialych--;
								}
							}
						}
					}
				}
			}

			if(czarne[i].GetY() == 7)
				czarne[i].SetRodzaj(2);

			for(int k=0; k<8; k++)
			{
				if(md == true)
					czarne[k].SetMoveDone(true);
			}
			if(ad == true)
			{
				BlackCheckMoves(i);
				if(czarne[i].GetMove() == 2)
					czarne[i].SetMoveDone(false);
			}
		}
	}
}

void Plansza::Draw(Window window)
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			window.SetDrawingCursor(i*50, j*50);
			if(plansza[i][j].kolor == '1')
				pole.Draw();
		}
	}
}

void Plansza::DrawPawns(Window window)
{
	for(int i=0; i<8; i++)
	{
		if(biale[i].GetActive() == true)
		{
			window.SetDrawingCursor(biale[i].GetX()*50, biale[i].GetY()*50);
			if(biale[i].GetRodzaj() == 1)
				bialyPionek.Draw();
			if(biale[i].GetRodzaj() == 2)
				bialaDamka.Draw();
		}
		if(czarne[i].GetActive() == true)
		{
			window.SetDrawingCursor(czarne[i].GetX()*50, czarne[i].GetY()*50);
			if(czarne[i].GetRodzaj() == 1)
				czarnyPionek[i].Draw();
			if(czarne[i].GetRodzaj() == 2)
				czarnaDamka[i].Draw();
		}
	}
}

bool Plansza::CheckIfOnBoard(int x, int y)
{
	if(x < 8 && x >= 0)
	{
		if(y < 8 && y >= 0)
			return true;
	}

	return false;
}

int Plansza::CheckWin()
{
	if(iloscBialych <= 0)
		return 1;
	if(iloscCzarnych <= 0)
		return 2;

	return 0;
}