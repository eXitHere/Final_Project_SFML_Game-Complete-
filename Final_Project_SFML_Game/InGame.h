#include"initial.h"

class InGame
{
public:
	InGame(RenderWindow *window,Event *event, int* state);
	~InGame() { cout << "delete 'ingame' complete" << endl; };
	void DRAW();
	 
private:
	// Fuction
	void loadTextureAll();
	void mapManage();
	void moveMap();
	// Variable
	
	Texture T_Map[8];
	Sprite S_cur_Map, S_new_Map;
	bool B_nowusemap = true;

	int next = 1;

	RenderWindow* window;
	Event* event;
	int* stateGame;
};

