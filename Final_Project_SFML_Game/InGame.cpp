#include "InGame.h"
#include "PositionItem.h"
#include <stdlib.h>
#include <time.h>
InGame::InGame(RenderWindow* window, Event* event, int* state) :
	player(window, event,&this->pause),
	bar(window,event)
{
	player.updateRec(this->indexPlayer);
	player.setPointerToY(&this->yPos);
	loadTextureAll();
	this->stateGame = state;
	this->window = window;
	this->event = event;
	//this->indexPlayer++;

	//bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], &this->Status[0], &this->Status[1], &this->Status[2], &this->Status[3], &this->Status[4], &this->Status[5]);
	updateBar();

	//npcList.push_back(new NPC());
	//npcList[0]->setDATA(this->T_NPC[0], 2000,&this->yPos, 01, this->window, this->event);

	this->S_door.setPosition(-200, 0);
	loadItems();
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
	//loadItems();
	//cout << itemList.size() << endl;
	for (int i = 0; i < itemList.size(); i++)
	{
		if(!pause) this->itemList[i]->DRAW();
		if (this->itemList[i]->deleteMe())
		{
			
			//cout << "del Item" << endl;
			Item* p;
			if (this->itemList.size() == 1)
			{
				//cout << "aaaa" << endl;
				p = itemList.at(0);
				this->itemList.clear();
			}
			else
			{
				p = itemList.at(i);
				this->itemList.erase(this->itemList.begin() + i);
			}
			delete p;
			//cout << i << endl;
			continue;
			//cout << itemList.size() << " -- " << i << endl;
		}
		if (this->checkColilistion(this->itemList[i]))
		{
			//cout << "colision Item ID" << this->itemList[i]->getID() << endl;
			showFaceEffect(this->itemList[i]->getID());
			Item* p = itemList.at(i);
			delete p;
			this->itemList.erase(this->itemList.begin() + i);
			continue;
		}
		//cout << this->itemList.size() << endl;
		if (this->itemList.size() <= 0)
		{
			break;
		}
	}

	if(!pause)
	for (int j = 0; j < npcList.size(); j++) // <-- Press F to action something
	{
		//cout << "do" << endl;
		this->npcList[j]->DRAW();
		if (this->npcList[j]->checkState() == 1) // Press F
		{
		//	cout << "Press F" << endl;
			this->indexPlayer = this->npcList[j]->getID();
			updateChalacter(false);
			NPC* p = npcList.at(j);
			delete p;
			this->npcList.erase(this->npcList.begin() + j);
		}
		else if (this->npcList[j]->checkState() == 2) // <0
		{
			//cout << "DEl npc" << endl;
			NPC* p = npcList.at(j);
			delete p;
			this->npcList.erase(this->npcList.begin() + j);
		}
	}
	
	player.DRAW();

	for (int k = 0; k < faceList.size(); k++)
	{
		this->faceList[k]->DRAW(this->window);
		if (this->faceList[k]->getDelete())
		{
			statusFace* temp = faceList.at(k);
			delete temp;
			this->faceList.erase(this->faceList.begin() + k);
		}
	}
	this->window->draw(this->S_door);
	bar.DRAW();
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

	this->T_door.loadFromFile("Texture/Map/door.png");
	this->S_door.setTexture(this->T_door);

	//ITEM
	this->T_items[0].loadFromFile("Texture/items/bear.png");
	this->T_items[1].loadFromFile("Texture/items/candy.png");
	this->T_items[2].loadFromFile("Texture/items/food.png");
	this->T_items[3].loadFromFile("Texture/items/food2.png");
	this->T_items[4].loadFromFile("Texture/items/football.png");
	this->T_items[5].loadFromFile("Texture/items/milk.png");
	this->T_items[6].loadFromFile("Texture/items/money.png");
	this->T_items[7].loadFromFile("Texture/items/painter.png");
	this->T_items[8].loadFromFile("Texture/items/teacher.png");
	this->T_items[9].loadFromFile("Texture/items/wrench.png");

	//NPC
	this->T_NPC[0].loadFromFile("Texture/NPC/NPC01.png");
	this->T_NPC[1].loadFromFile("Texture/NPC/NPC02.png");
	//Face
	this->T_face[0].loadFromFile("Texture/items/happy.png");
	this->T_face[1].loadFromFile("Texture/items/sad.png");
	this->T_face[2].loadFromFile("Texture/items/hpUp.png");
	this->T_face[3].loadFromFile("Texture/items/hpDown.png");
	this->T_face[4].loadFromFile("Texture/items/moneyP.png");
	this->T_face[5].loadFromFile("Texture/items/moneyD.png");
}

void InGame::moveMap()
{
	if(!pause)
	if (B_nowusemap)
	{
		this->S_cur_Map.move(-6 * gameSpeed, 0);

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next -1].getSize().x != 0)
		{
			this->S_new_Map.move(-6 * gameSpeed, 0);
		}

		//cout << S_cur_Map.getPosition().x << endl;
		if (this->S_cur_Map.getPosition().x == 402)
		{
			updateChalacter(true);
			updateBar();
			loadItems();
		}

		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)// Load New Map
		{
			B_nowusemap = !B_nowusemap;
			this->S_new_Map.setTexture(this->T_Map[this->next]);
			this->S_new_Map.setPosition(1800.0f, 0.0f);
			this->S_door.setPosition(1800.0f, 0.0f);
			this->next++;
		}
	}
	else
	{
		this->S_new_Map.move(-6 * gameSpeed, 0);
		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next-1].getSize().x != 0)
		{
			this->S_cur_Map.move(-6 * gameSpeed, 0);
		}
		if (int(this->S_new_Map.getPosition().x) ==402)
		{
			//player.updateRec(this->indexPlayer);
			//indexPlayer++;
			updateChalacter(true);
			updateBar();
			loadItems();
		}

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)
		{
			B_nowusemap = !B_nowusemap;
			this->S_cur_Map.setTexture(T_Map[this->next]);
			this->S_cur_Map.setPosition(1800.0f, 0.0f);
			this->S_door.setPosition(1800, 0.0f);
			this->next++;
		}
	}
	if (this->next == 6)
	{
		*this->stateGame = 2;
	}
	this->S_door.move(-6 * gameSpeed, 0);
}


void InGame::loadItems()
{
	srand(time(NULL));
	int tempPos[5] = { 250,450,250,350,290 };
	switch (this->next-1)
	{
	case 0:
		for (int j = 0; j < 12; j++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size()-1]->loadData(this->T_items[idItem[this->next	-1][j] - 1], idItem[this->next-1][j], this->window, Vector2f(positionItem[this->next-1][j] + rand() % 200, tempPos[(j + rand() % 5) % 5]));
		}
		for (int j = 0; j < 1; j++) 
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size()-1]->setDATA(T_NPC[idNPC[this->next - 1][j]], positionNPC[this->next-1][j], &this->yPos, 01, this->window, this->event);
		}
		break;
	case 1:
		for (int j = 0; j < 12; j++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size()-1]->loadData(this->T_items[idItem[this->next-1][j] - 1], idItem[this->next-1][j], this->window, Vector2f(positionItem[this->next-1][j] + rand() % 200, tempPos[(j + rand() % 5) % 5]));
		}
		for (int j = 0; j < 3; j++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size()-1]->setDATA(T_NPC[idNPC[this->next - 1][j]], positionNPC[this->next - 1][j], &this->yPos, 03, this->window, this->event);
		}
		break;
	}
}

int InGame::positionNow()
{
	if (B_nowusemap)
	{
		return round(fabs(this->S_cur_Map.getPosition().x));
	}
	else
	{
		return round(fabs(this->S_new_Map.getPosition().x));
	}
}


void InGame::updateChalacter(bool state)
{
	if (state)
	{
		switch (this->indexPlayer)
		{
		case 0: case 1: this->indexPlayer = 2;
			break;
		}
	}
	else
	{
		switch (this->indexPlayer)
		{
		case 3:
			this->pause = true;
			//cout << "Pause" << endl;
			break;
		}
	}
	
	player.updateRec(this->indexPlayer);
	
}

bool InGame::checkColilistion(Item* item)
{
	//cout << "Player : "<< this->player.getPosition().x << " " << this->player.getPosition().y << endl;
	//cout << "Item : " << item->getPosition().x << " " << item->getPosition().y << endl;
	return (abs(this->player.getPosition().x-item->getPosition().x) < this->player.getHalfsize().x + item->getHalfsize().x &&
			abs(this->player.getPosition().y-item->getPosition().y) < this->player.getHalfsize().y + item->getHalfsize().y);
}

void InGame::showFaceEffect(int index)
{
	switch (index)
	{
	case ID_BEAR:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPDOWN]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_MONEYDOWN]);
		this->faceList.push_back(tempFace);
		break;
	case ID_CANDY:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPDOWN]);
		this->faceList.push_back(tempFace);
		break;
	case ID_FOOD:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_MONEYDOWN]);
		this->faceList.push_back(tempFace);
		break;
	case ID_FOOD2:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_MONEYDOWN]);
		this->faceList.push_back(tempFace); 
		break;
	case ID_FOOTBALL:
		break;
	case ID_MILK:
		this->counter[ID_MILK]++;
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		break;
	case ID_MONEY:
		break;
	case ID_PAINTER:
		break;
	case ID_TEACHER:
		break;
	case ID_WRENCH:
		break;
	}
}

void InGame::addFace(Texture texture)
{
	this->tempFace = new statusFace(texture, this->player.getPosition() + Vector2f(this->boxForFace[this->indexFaceX], this->boxForFace[this->indexFaceY]));
	this->indexFaceX = (this->indexFaceX > 4 ? 0 : this->indexFaceX + 1);
	this->indexFaceY = (this->indexFaceY > 4 ? 0 : this->indexFaceY + 1);
}

void InGame::updateBar()
{
	switch (this->next-1)
	{
	case 0:
		this->Object = 0;
		this->Object2[0] = false;
		this->Object2[1] = false;
		for (int i = 0; i < 6; i++)
		{
			this->ID[i] = 0;
			this->Status[i] = 0;
		}
		this->ID[0] = ID_SHOWBAR_MILK;
		this->Status[0] = &this->counter[ID_MILK];
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5]);
		break;
	case 1:
		//cout << "This case 1" << endl;
		break;
	}
}
