#include "InGame.h"

InGame::InGame(RenderWindow* window, Event* event, int* state) :
	player(window, event),
	bar(window,event)
{
	player.updateRec(this->indexPlayer);
	player.setPointerToY(&this->yPos);
	loadTextureAll();
	this->stateGame = state;
	this->window = window;
	this->event = event;
	loadMapCode();
	this->indexPlayer++;


	//test
	bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], &this->Status[0], &this->Status[1], &this->Status[2], &this->Status[3], &this->Status[4], &this->Status[5]);
	
	npcList.push_back(new NPC());
	npcList[0]->setDATA(this->T_NPC[0], 2000,&this->yPos, 01, this->window, this->event);

	this->S_door.setPosition(-200, 0);
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
	loadItems();
	//cout << itemList.size() << endl;
	for (int i = 0; i < itemList.size(); i++)
	{
		this->itemList[i]->DRAW();
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

	player.DRAW();

	for (int j = 0; j < npcList.size(); j++)
	{
		//cout << "do" << endl;
		this->npcList[j]->DRAW();
		if (this->npcList[j]->checkState() == 1) // Press F
		{
		//	cout << "Press F" << endl;
			NPC* p = npcList.at(j);
			delete p;
			this->npcList.erase(this->npcList.begin() + j);
			this->indexPlayer = 1;
			this->player.updateRec(this->indexPlayer);
		}
		else if (this->npcList[j]->checkState() == 2) // <0
		{
			//cout << "DEl npc" << endl;
			NPC* p = npcList.at(j);
			delete p;
			this->npcList.erase(this->npcList.begin() + j);
		}
	}
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

	//Face
	this->T_face[0].loadFromFile("Texture/items/happy.png");
	this->T_face[1].loadFromFile("Texture/items/sad.png");
	this->T_face[2].loadFromFile("Texture/items/hpUp.png");
	this->T_face[3].loadFromFile("Texture/items/hpDown.png");
	this->T_face[4].loadFromFile("Texture/items/moneyP.png");
	this->T_face[5].loadFromFile("Texture/items/moneyD.png");
}

void InGame::mapManage()
{

}

void InGame::moveMap()
{
	if (B_nowusemap)
	{
		this->S_cur_Map.move(-4 * gameSpeed, 0);

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next -1].getSize().x != 0)
		{
			this->S_new_Map.move(-4 * gameSpeed, 0);
		}

		//cout << S_cur_Map.getPosition().x << endl;
		if (this->S_cur_Map.getPosition().x == 400)
		{
			player.updateRec(this->indexPlayer);
			indexPlayer++;
		}

		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)// Load New Map
		{
			this->next++;
			B_nowusemap = !B_nowusemap;
			this->S_new_Map.setTexture(this->T_Map[this->next]);
			this->S_new_Map.setPosition(1800.0f, 0.0f);
			this->S_door.setPosition(1800.0f, 0.0f);
		}
	}
	else
	{
		this->S_new_Map.move(-4 * gameSpeed, 0);
		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next-1].getSize().x != 0)
		{
			this->S_cur_Map.move(-4 * gameSpeed, 0);
		}
		if (int(this->S_new_Map.getPosition().x) ==400)
		{
			player.updateRec(this->indexPlayer);
			indexPlayer++;
		}

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)
		{
			B_nowusemap = !B_nowusemap;
			this->next++;
			this->S_cur_Map.setTexture(T_Map[this->next]);
			this->S_cur_Map.setPosition(1800.0f, 0.0f);
			this->S_door.setPosition(1800, 0.0f);
		}
	}
	if (this->next == 3)
	{
		*this->stateGame = 2;
	}
	this->S_door.move(-4 * gameSpeed, 0);
}

void InGame::loadMapCode()
{
	this->myFile.open("database/codeMap.txt");
	string temp;
	string temp2;
	int tempint;
	int tempP = 1;
	int tempResult =0;
	int tempIndex = 0;
	while (!this->myFile.eof())
	{
		getline(this->myFile, temp);
		for (int i = 0; i < temp.length(); i++)
		{
			if (temp[i] == ',' || temp[i+1] == '\0')
			{
				if (temp[i + 1] == '\0')
				{
					temp2 += temp[i];
				}
				//cout << "size of temp2 : " << temp2.length() << endl;
				for (int j = temp2.length()-1,tempP = 1; j >= 0; j--,tempP*=10)
				{
					tempResult += (temp2[j] - '0') * tempP;
				//	cout << " ----- " << temp2[j];
				}
				//cout << endl;
				//cout << tempResult << endl;
				this->posItems.push_back(tempResult);
				tempResult = 0;
				temp2.clear();
			}
			else
			{
				temp2 += temp[i];
			}
		}
	}
	this->myFile.close();
}

void InGame::loadItems()
{
	//cout << "PosNow : " << this->positionNow() << endl;
	if (this->posItems.size() > 0 && this->posItems[0] == this->positionNow())
	{
		this->itemList.push_back(new Item());
		this->itemList[itemList.size()-1]->loadData(this->T_items[testItem++],testItem,this->window, Vector2f(positionNow(), 450.0f));
		this->posItems.erase(posItems.begin());
		
	}
	/*this->itemList.push_back(new Item());
	for (int i = 0; i < 5; i++)
	{		
		this->itemList[i]->loadData(this->T_items[0], this->window,Vector2f(800+i*200,450));
	}*/
}

int InGame::positionNow()
{
	if (B_nowusemap)
	{
		return fabs(this->S_cur_Map.getPosition().x);
	}
	else
	{
		return fabs(this->S_new_Map.getPosition().x);
	}
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
