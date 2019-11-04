#include "InGame.h"

InGame::InGame(RenderWindow* window, Event* event, int* state) 
{
	loadTextureAll();
	this->stateGame = state;
	this->window = window;
	this->event = event;
	loadMapCode();
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
	for (int i = 0; i < itemList.size(); i++)
	{
		this->itemList[i]->DRAW();
		if (this->itemList[i]->deleteMe())
		{
			Item* p = itemList.at(i);
			delete p;
			this->itemList.erase(this->itemList.begin()+i);
			cout << itemList.size() << " -- " << i << endl;
		}
	}
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

	this->T_items[0].loadFromFile("Texture/items/bear.png");
}

void InGame::mapManage()
{

}

void InGame::moveMap()
{
	if (B_nowusemap)
	{
		this->S_cur_Map.move(-4, 0);

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next -1].getSize().x != 0)
		{
			this->S_new_Map.move(-4, 0);
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
		this->S_new_Map.move(-4, 0);
		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next-1].getSize().x != 0)
		{
			this->S_cur_Map.move(-4, 0);
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
	cout << "PosNow : " << this->positionNow() << endl;
	if (this->posItems.size() > 0 && this->posItems[0] == this->positionNow())
	{
		this->itemList.push_back(new Item());
		this->itemList[itemList.size()-1]->loadData(this->T_items[0], this->window, Vector2f(positionNow(), 450.0f));
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
