#include "InGame.h"

InGame::InGame(RenderWindow* window, Event* event, int* state)
{
	loadTextureAll();
	this->stateGame = state;
	this->window = window;
	this->event = event;
}

void InGame::DRAW()
{
	//this->T_Map[0].loadFromFile("Texture/Map/map0.jpg");
	//this->T_Map[1].loadFromFile("Texture/Map/map1.jpg");
	if (B_nowusemap)
	{	
		window->draw(this->S_new_Map);
		window->draw(this->S_cur_Map);
	}
	else
	{	
		window->draw(this->S_cur_Map);
		window->draw(this->S_new_Map);
	}
	
	moveMap();
	//window->draw(this->S_new_Map);
}

void InGame::loadTextureAll()
{
	this->T_Map[0].loadFromFile("Texture/Map/map0.jpg");
	this->T_Map[1].loadFromFile("Texture/Map/map1.jpg");
	this->T_Map[2].loadFromFile("Texture/Map/map2.jpg");
	this->T_Map[3].loadFromFile("Texture/Map/map3.1.jpg");
	this->T_Map[4].loadFromFile("Texture/Map/map3.2.jpg");
	this->T_Map[5].loadFromFile("Texture/Map/map3.3.jpg");
	this->T_Map[6].loadFromFile("Texture/Map/map3.4.jpg");
	this->T_Map[7].loadFromFile("Texture/Map/map3.5.jpg");
	this->S_cur_Map.setTexture(this->T_Map[0]);
}

void InGame::mapManage()
{

}

void InGame::moveMap()
{
	if (B_nowusemap)
	{
		this->S_cur_Map.move(-50, 0);

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next -1].getSize().x != 0)
		{
			this->S_new_Map.move(-50, 0);
		}

		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)
		{
			this->next++;
			B_nowusemap = !B_nowusemap;
			this->S_new_Map.setTexture(this->T_Map[this->next]);
			this->S_new_Map.setPosition(1800.0f, 0.0f);
		}
	}
	else
	{
		this->S_new_Map.move(-50, 0);
		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next-1].getSize().x != 0)
		{
			this->S_cur_Map.move(-50, 0);
		}
		if (this->S_new_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)
		{
			B_nowusemap = !B_nowusemap;
			this->next++;
			this->S_cur_Map.setTexture(T_Map[this->next]);
			this->S_cur_Map.setPosition(1800.0f, 0.0f);
		}
	}
	if (this->next == 7)
	{
		*this->stateGame = 2;
	}
	
}
