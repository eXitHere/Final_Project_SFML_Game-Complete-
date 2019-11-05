#include"initial.h"
#include "Item.h"
#include "Player.h"
#include "barManager.h"

#include<vector>
#include<fstream>

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
	void loadMapCode();
	void loadItems();
	int positionNow();
	// Variable for Items
	Texture T_items[4];
	vector<Item*> itemList;
	vector<int> posItems;
	fstream myFile;
	// Variable
	
	
	// Player
	Player player;
	int indexPlayer = 0;

	// Bar
	barManager bar;


	Texture T_Map[8];
	Sprite S_cur_Map, S_new_Map;
	bool B_nowusemap = true;
	
	int next = 1;

	RenderWindow* window;
	Event* event;
	int* stateGame;
};

