#include"initial.h"

class InGame
{
public:
	InGame(RenderWindow *window,Event *event, int* state);
	void DRAW();

private:
	// Fuction
	void loadTextureAll();
	void mapManage();

	// Variable
	int* stateGame;
	Texture* T_Map[2];
	Sprite S_cur_Map, S_last_Map;
	bool B_nowusemap = false;
};

