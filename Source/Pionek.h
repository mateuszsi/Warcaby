#pragma once

class Pionek
{
private:
	int rodzaj;
	int move;
	int x, y;
	bool focus;
	bool active;
	bool moveDone;

public:
	Pionek(void);
	~Pionek(void);

	void SetPosition(int x, int y);
	void SetFocus(bool f){focus = f;}
	void SetActive(bool a){active = a;}
	void SetRodzaj(int r){rodzaj = r;}
	void SetMove(int m){move = m;}
	void Start(int x, int y);
	void SetMoveDone(bool md){moveDone = md;}
	int GetRodzaj(){return rodzaj;}
	int GetMove(){return move;}
	int GetX(){return x;}
	int GetY(){return y;}
	bool GetActive(){return active;}
	bool GetFocus(){return focus;}
	bool GetMOveDone(){return moveDone;}
	bool CheckCollision(int x, int y);
};

