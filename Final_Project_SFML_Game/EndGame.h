#include"initial.h"

class EndGame
{
public:
	EndGame(RenderWindow* window, Event* event, int* state);
	void DRAW();
	void setPointer(string *P,float *F);
private:
	Font font;
	Text Text_score;
	string* PName;
	float* PScore;
	void mouseCheck();
	bool hold = false;
	Event* event;
	RenderWindow* window;
	int* stateGame;
	Texture T_bg, T_status[2], T_logo, T_BlockLogo, T_score,T_exit[2];
	Sprite S_bg, S_status, S_logo, S_blockLogo, S_score,S_exit;
};

