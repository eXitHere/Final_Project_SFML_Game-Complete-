#ifndef HEADER_H_
#define HEADER_H_
#include "soundPlayBack.h"
#include"initial.h"
#endif


#include "Item.h"
#include "Player.h"
#include "MutiChoice.h"
#include "barManager.h"
#include "NPC.h"
#include "statusFace.h"
#include <vector>
#include <fstream>

class InGame
{
public:
	InGame(RenderWindow *window,Event *event, int* state,soundPlayBack *soundManage);
	~InGame() { cout << "delete 'ingame' complete" << endl; };
	void DRAW();
	
	 
private:

	int way = -1;
	int counterASD[3] = { 0,0,0 };
	int useMap = -1;
	int money = 0;

	int calBase(int val);

	MutiChoice mutiChoice;
	int countChoice = 0;
	int mainArchiveChoice = 0;

	Clock clockMain;
	double mainTime = 0.0;

	soundPlayBack* soundManage;

	bool pause = false;
	// Fuction
	void loadTextureAll();
	void moveMap();
	void loadItems();
	int positionNow();
	void updateChalacter(bool state);

	// Funcion local
	bool checkColilistion(Item *item);
	void showFaceEffect(int index);
	void addFace(Texture texture);

	void firstArchive(int index);

	void updateBar();

	int mainArchive = 0; //// <----------  -----------> \\\\\\\\\\\

	int calc(int idNPC);

	// Variable counter Item all
	int counter[44] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int countSpawn[4] = { 0,0,0,0 };


	// Variable for Items
	//int testItem = 0;
	Texture T_items[11];
	vector<Item*> itemList;
	fstream myFile;
	// Variable
	
	//
	
	// Player
	Player player;
	int indexPlayer = 0;

	// Bar
	int Object = 3, *Status[6], ID[6] = { 1,2,3,4,1,1 };
	bool Object2[2] = { true,false };
	barManager bar;

	// NPC
	float yPos;
	Texture T_NPC[37];
	vector<NPC*> npcList;

	// Face
	int boxForFace[6] = { -100,50,0,-50,100 }, indexFaceX = 0, indexFaceY = 2; // <-->
	Texture T_face[6];
	vector<statusFace*> faceList;
	statusFace* tempFace;

	// MAP
	Texture T_Map[11],T_door;
	Sprite S_cur_Map, S_new_Map,S_door;
	bool B_nowusemap = true;
	
	int next = 1;

	RenderWindow* window;
	Event* event;
	int* stateGame;



	

};

