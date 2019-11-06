#include"initial.h"
#include "Item.h"
#include "Player.h"
#include "barManager.h"
#include "NPC.h"
#include"statusFace.h"
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


	// Funcion local
	bool checkColilistion(Item *item);
	void showFaceEffect(int index);
	void addFace(Texture texture);

	// Variable for Items
	int testItem = 0;
	Texture T_items[10];
	vector<Item*> itemList;
	vector<int> posItems;
	fstream myFile;
	// Variable
	
	//
	
	// Player
	Player player;
	int indexPlayer = 0;

	// Bar
	int Object = 3, Status[6] = { 0,0,0,0,0,0 }, ID[6] = { 1,2,3,4,1,1 };
	bool Object2[2] = { true,false };
	barManager bar;

	// NPC
	float yPos;
	Texture T_NPC[1];
	vector<NPC*> npcList;

	// Face
	int boxForFace[6] = { -100,50,0,-50,100 }, indexFaceX = 0, indexFaceY = 2; // <-->
	Texture T_face[6];
	vector<statusFace*> faceList;
	statusFace* tempFace;

	// MAP
	Texture T_Map[8];
	Sprite S_cur_Map, S_new_Map;
	bool B_nowusemap = true;
	
	int next = 1;

	RenderWindow* window;
	Event* event;
	int* stateGame;
};

