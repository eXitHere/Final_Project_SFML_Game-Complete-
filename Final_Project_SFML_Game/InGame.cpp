#include "InGame.h"

InGame::InGame(RenderWindow* window, Event* event, int* state)
{
	loadTextureAll();
	this->stateGame = state;
}

void InGame::DRAW()
{
}

void InGame::loadTextureAll()
{
	this->T_Map[0]->loadFromFile("Texture/Map/map0.jpg");
	this->T_Map[1]->loadFromFile("Texture/Map/map1.jpg");
	/*this->T_Map[1].loadFromFile("Texture/Map/map1.jpg");
	this->T_Map[2].loadFromFile("Texture/Map/map2.jpg");
	this->T_Map[3].loadFromFile("Texture/Map/map3.1.jpg");
	this->T_Map[4].loadFromFile("Texture/Map/map3.2.jpg");
	this->T_Map[5].loadFromFile("Texture/Map/map3.3.jpg");
	this->T_Map[6].loadFromFile("Texture/Map/map3.4.jpg");
	this->T_Map[7].loadFromFile("Texture/Map/map3.5.jpg");*/
}

void InGame::mapManage()
{
}
