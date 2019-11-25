#include "InGame.h"
#include "PositionItem.h"
#include <stdlib.h>
#include <time.h>
InGame::InGame(RenderWindow* window, Event* event, int* state,soundPlayBack* soundManage) :
	player(window, event,&this->pause,soundManage),
	bar(window,event,&this->money),
	mutiChoice(window,event)
{
	this->soundManage = soundManage;
	//this->bar.setAr(&this->counter[]);
	this->bar.setAr(this->counterASD);
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
	if (this->npcList.size()>0 && this->npcList[0]->getID() == ID_NPC_FLOWER3)
	{
		//cout << "This Map" << endl;
		if (this->counter[ID_FLOWER1] != 0 || this->counter[ID_FLOWER2] != 0 || this->counter[ID_FLOWER3] != 0)
		{
			this->npcList[0]->setCanBuy(false);
			this->npcList[1]->setCanBuy(false);
			this->npcList[2]->setCanBuy(false);
		}
		else if (this->money >= 90-10 )
		{
			this->npcList[0]->setCanBuy(true);
			this->npcList[1]->setCanBuy(true);
			this->npcList[2]->setCanBuy(true);
		}
		else if (this->money >= 60-10)
		{
			this->npcList[0]->setCanBuy(false);
			this->npcList[1]->setCanBuy(true);
			this->npcList[2]->setCanBuy(true);
		}
		else if (this->money >= 30-10)
		{
			this->npcList[0]->setCanBuy(false);
			this->npcList[1]->setCanBuy(false);
			this->npcList[2]->setCanBuy(true);
		}
		else
		{
			this->npcList[0]->setCanBuy(false);
			this->npcList[1]->setCanBuy(false);
			this->npcList[2]->setCanBuy(false);
		}
		
		if (this->counter[ID_CARSHOW1] != 0 || this->counter[ID_CARSHOW2] != 0 || this->counter[ID_CARSHOW3] != 0)
		{
			this->npcList[3]->setCanBuy(false);
			this->npcList[4]->setCanBuy(false);
			this->npcList[5]->setCanBuy(false);
		}
		else if (this->money >= 500-50)
		{
			this->npcList[3]->setCanBuy(true);
			this->npcList[4]->setCanBuy(true);
			this->npcList[5]->setCanBuy(true);
		}
		else if (this->money >= 400-50)
		{
			this->npcList[3]->setCanBuy(false);
			this->npcList[4]->setCanBuy(true);
			this->npcList[5]->setCanBuy(true);
		}
		else if (this->money >= 300-50)
		{
			this->npcList[3]->setCanBuy(false);
			this->npcList[4]->setCanBuy(false);
			this->npcList[5]->setCanBuy(true);
		}
		else
		{
			this->npcList[3]->setCanBuy(false);
			this->npcList[4]->setCanBuy(false);
			this->npcList[5]->setCanBuy(false);
		}
	}

	if(!this->pause) this->mainTime += this->clockMain.restart().asSeconds();
	if (this->mainTime >= 3)
	{
		this->mainTime = 0;
		this->bar.hp(float(-0.2f * this->next));
		this->bar.happy(-0.2f * this->next);
	}

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
	//loadItems();
	//cout << itemList.size() << endl;
	for (int i = 0; i < itemList.size(); i++)
	{
		if(!this->pause) this->itemList[i]->Move(-4.8f);
		else this->itemList[i]->Move(-2.4f);
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
			this->soundManage->playHitItem();
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

	for (int j = 0; j < npcList.size(); j++) // <-- Press F to action something
	{
		//cout << "do" << endl;
		if(!this->npcList[j]->isSpacial()) this->npcList[j]->DRAW();
		if (this->npcList[j]->isSpacial() && this->npcList[j]->getPostiosion().x > -500)
		{
			this->npcList[j]->DRAW();
			if (!pause) this->npcList[j]->Move();
		}
		//this->npcList[j]->DRAW();
		if (!pause && !this->npcList[j]->isSpacial()) this->npcList[j]->Move();
		if (this->npcList[j]->checkState() == 1 ||
			(this->next-1==2 && this->npcList.size()>3 && this-> npcList[3]->getPostiosion().x < 400)) // Press F
		{
		//	cout << "Press F" << endl;
			if (this->next - 1 == 2)
			{
				//cout << this->npcList[3]->getPostiosion().x << endl;
			}
			switch (this->npcList[j]->getID())
			{
			case 0: this->indexPlayer = 1; updateChalacter(false); /*cout << "use BabyCar" << endl; */this->counter[ID_BABYCAR] = 1; break;
			case 1: this->indexPlayer = 3; updateChalacter(false); break;
			case ID_NPC_CAT: this->npcList[(__int64)j+1]->setPosition(this->npcList[j]->getPostiosion()); this->bar.happy(1); this->soundManage->playCat(); this->counter[ID_CAT]++; break;
			case ID_NPC_FOOTBALL: firstArchive(ID_NPC_FOOTBALL); continue; break;
			case ID_NPC_PAINTER:  firstArchive(ID_NPC_PAINTER);  continue; break;
			case ID_NPC_TEACHER:  firstArchive(ID_NPC_TEACHER);  continue; break;
			case ID_NPC_WRENCH:   firstArchive(ID_NPC_WRENCH);   continue; break;
			}
			//cout << "Del : " << j << endl;
			NPC* p = npcList.at(j);
			delete p;
			this->npcList.erase(this->npcList.begin() + j);
		}
		else if (this->npcList[j]->checkState() == 2) // <-500
		{
			//cout << "DEl npc" << endl;
			if (this->npcList[j]->getID() != ID_NPC_FOOTBALL &&
				this->npcList[j]->getID() != ID_NPC_PAINTER  &&
				this->npcList[j]->getID() != ID_NPC_TEACHER  &&
				this->npcList[j]->getID() != ID_NPC_WRENCH   &&
				this->npcList[j]->getID() != ID_NPC_FLOWER1  &&
				this->npcList[j]->getID() != ID_NPC_FLOWER2  &&
				this->npcList[j]->getID() != ID_NPC_FLOWER3  &&
				this->npcList[j]->getID() != ID_NPC_CARSHOW1 &&
				this->npcList[j]->getID() != ID_NPC_CARSHOW2 &&
				this->npcList[j]->getID() != ID_NPC_CARSHOW3 )
			{ /// <<--- don't delete npc
				//cout << "Delete " << this->npcList[j]->getID() << endl;
				NPC* p = npcList.at(j);
				delete p;
				this->npcList.erase(this->npcList.begin() + j);
			}
		}
		else if (this->npcList[j]->checkState() == 3)
		{
			//cout << this->npcList[j]->getID() << endl;
			switch (this->npcList[j]->getID())
			{
			case ID_NPC_FLOWER1:
				//cout << "EIEI1" << endl;
				if (this->counter[ID_FLOWER1] != 1)
				{
					this->counter[ID_FLOWER1] = 1;
					this->money -= 30;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_FLOWER2:
				//cout << "EIEI2" << endl;
				if (this->counter[ID_FLOWER2] != 1)
				{
					this->counter[ID_FLOWER2] = 1;
					this->money -= 60;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_FLOWER3:
				//cout << "EIEI3" << endl;
				if (this->counter[ID_FLOWER3] != 1)
				{
					this->counter[ID_FLOWER3] = 1;
					this->money -= 90;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_CARSHOW1:
				if (this->counter[ID_CARSHOW1] != 1)
				{
					this->counter[ID_CARSHOW1] = 1;
					this->money -= 300;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_CARSHOW2:
				if (this->counter[ID_CARSHOW2] != 1)
				{
					this->counter[ID_CARSHOW2] = 1;
					this->money -= 400;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_CARSHOW3:
				if (this->counter[ID_CARSHOW3] != 1)
				{
					this->counter[ID_CARSHOW3] = 1;
					this->money -= 500;
					addFace(this->T_face[ID_FACE_MONEYDOWN]);
					this->faceList.push_back(tempFace);
				}
				break;
			case ID_NPC_FRIEND1:
				if (counter[ID_FRIEND1] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FRIEND1));
					this->counter[ID_FRIEND1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-3);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(3);
					}
				}
				break;
			case ID_NPC_FRIEND2:
				if (counter[ID_FRIEND2] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FRIEND2));
					this->counter[ID_FRIEND2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-3);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(3);
					}
				}
				break;
			case ID_NPC_FRIEND3:
				if (counter[ID_FRIEND3] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FRIEND3));
					this->counter[ID_FRIEND3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-3);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(3);
					}
				}
				break;
			case ID_NPC_FRIEND4:
				if (counter[ID_FRIEND4] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FRIEND4));
					this->counter[ID_FRIEND4] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-3);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(3);
					}
				}
				break;
				//------//
			case ID_NPC_PAINT_1:
				if (counter[ID_PA1] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_PAINT_1));
					this->counter[ID_PA1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_PAINT_2:
				if (counter[ID_PA2] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_PAINT_2));
					this->counter[ID_PA2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_PAINT_3:
				if (counter[ID_PA3] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_PAINT_3));
					this->counter[ID_PA3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
				//------//
			case ID_NPC_OFFICE_1:
				if (counter[ID_OF1] == 0)
				{
					//cout << "CHECK" << endl;
					this->npcList[j]->setYesNo(this->calc(ID_NPC_OFFICE_1));
					this->counter[ID_OF1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_OFFICE_2:
				if (counter[ID_OF2] == 0)
				{
					//cout << "CHECK" << endl;
					this->npcList[j]->setYesNo(this->calc(ID_NPC_OFFICE_2));
					this->counter[ID_OF2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_OFFICE_3:
				if (counter[ID_OF3] == 0)
				{
					//cout << "CHECK" << endl;
					this->npcList[j]->setYesNo(this->calc(ID_NPC_OFFICE_3));
					this->counter[ID_OF3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
				//------//
			case ID_NPC_WRENCH_1:
				if (counter[ID_WR1] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_WRENCH_1));
					this->counter[ID_WR1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_WRENCH_2:
				if (counter[ID_WR2] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_WRENCH_2));
					this->counter[ID_WR2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_WRENCH_3:
				if (counter[ID_WR3] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_WRENCH_3));
					this->counter[ID_WR3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
				//------//
			case ID_NPC_FOOTBALL_1:
				if (counter[ID_FO1] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FOOTBALL_1));
					this->counter[ID_FO1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_FOOTBALL_2:
				if (counter[ID_FO2] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FOOTBALL_2));
					this->counter[ID_FO2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_FOOTBALL_3:
				if (counter[ID_FO3] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_FOOTBALL_3));
					this->counter[ID_FO3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
				//------//
			case ID_NPC_TEACHER_1:
				if (counter[ID_TA1] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_TEACHER_1));
					this->counter[ID_TA1] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_TEACHER_2:
				if (counter[ID_TA2] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_TEACHER_2));
					this->counter[ID_TA2] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			case ID_NPC_TEACHER_3:
				if (counter[ID_TA3] == 0)
				{
					this->npcList[j]->setYesNo(this->calc(ID_NPC_TEACHER_3));
					this->counter[ID_TA3] = 1;
					if (this->npcList[j]->getYesNo() == 1)
					{
						addFace(this->T_face[ID_FACE_SAD]);
						this->faceList.push_back(tempFace);
						this->bar.happy(-5);
					}
					else if (this->npcList[j]->getYesNo() == 2)
					{
						addFace(this->T_face[ID_FACE_HAPPY]);
						this->faceList.push_back(tempFace);
						this->bar.happy(5);
						addFace(this->T_face[ID_FACE_MONEYUP]);
						this->faceList.push_back(tempFace);
						this->money += 100;
					}
				}
				break;
			}
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
	player.DRAW();
	if (this->S_door.getPosition().x == 1590) this->soundManage->playDoor();
	this->window->draw(this->S_door);
	moveMap();


	if (this->countChoice > 1 && this->mainArchiveChoice ==0)
	{
		//cout << this->mutiChoice.getChoice() << endl;
		if (this->mainArchiveChoice == 0 && this->mutiChoice.getChoice()!=0)
		{
			this->mainArchiveChoice = this->mutiChoice.getChoice();
			this->pause = false;
			//cout << "Next Map : " << this->next << endl;
			switch (this->mainArchiveChoice)
			{
			case 1:
				//this->next = 5;
				this->useMap = 5;
				cout << "paint MAP " << endl; ////<<< ---- --
				break;
			case 3:
				//this->next = 7;
				this->useMap = 6;
				cout << "Wrench MAP" << endl;
				
				break;
			case 2:
				//this->next = 6;
				this->useMap = 7;
				cout << "Teacher MAP " << endl;
				break;
			case 4:
				//this->next = 8;
				this->useMap = 8;
				cout << "Football MAP" << endl;
				break;
			}
			this->way = this->useMap+1;
			//cout << this->useMap << endl;
		}
	}
	else if (this->countChoice == 1 && this->mainArchiveChoice ==0)
	{
		if (this->counter[ID_WRENCH] >= 6)
		{
			this->mainArchiveChoice = 3;
			this->useMap = 6;
			cout << "Wrench MAP" << endl;
		}
		else if (this->counter[ID_TEACHER] >= 6)
		{
			this->mainArchiveChoice = 2;
			this->useMap = 7;
			cout << "Teacher MAP" << endl;
		}
		else if (this->counter[ID_PAINTER] >= 6)
		{
			this->useMap = 5;
			this->mainArchiveChoice = 1;
			cout << "Painter MAP" << endl;
		}
		else if (this->counter[ID_FOOTBALL] >= 6)
		{
			this->useMap = 8;
			this->mainArchiveChoice = 4;
			cout << "FOOTBALL MAP" << endl;
		}
	}

	bar.DRAW();
}

int InGame::calBase(int val)
{
	return (val<=5?val*2:10+(val%5)*5);
}




void InGame::loadTextureAll()
{
	this->T_Map[0].loadFromFile("Texture/Map/map0.jpg");
	this->T_Map[1].loadFromFile("Texture/Map/map1.jpg");
	this->T_Map[2].loadFromFile("Texture/Map/map2.jpg");
	this->T_Map[3].loadFromFile("Texture/Map/map2.jpg");
	this->T_Map[4].loadFromFile("Texture/Map/map3.1.jpg");
	this->T_Map[5].loadFromFile("Texture/Map/map3.2.jpg");
	this->T_Map[6].loadFromFile("Texture/Map/map3.3.jpg");
	this->T_Map[7].loadFromFile("Texture/Map/map3.4.jpg");
	this->T_Map[8].loadFromFile("Texture/Map/map3.5.jpg");
	this->T_Map[9].loadFromFile("Texture/Map/Map&shop-01.jpg");
	this->T_Map[10].loadFromFile("Texture/Map/MapOnly-01.jpg");
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
	this->T_items[10].loadFromFile("Texture/items/IQ.png");

/*
map 5 normal
map 6 paint
map 7 wrench
map 8 teacher
map 9 football
*/

	//NPC
	this->T_NPC[0].loadFromFile("Texture/NPC/NPC01.png");
	this->T_NPC[1].loadFromFile("Texture/NPC/NPC02.png");
	this->T_NPC[2].loadFromFile("Texture/NPC/cat_-01.png");
	this->T_NPC[3].loadFromFile("Texture/NPC/cat_luv-01.png");
	this->T_NPC[4].loadFromFile("Texture/NPC/C1.png");
	this->T_NPC[5].loadFromFile("Texture/NPC/C2.png");
	this->T_NPC[6].loadFromFile("Texture/NPC/C3.png");
	this->T_NPC[7].loadFromFile("Texture/NPC/C4.png");
	this->T_NPC[8].loadFromFile("Texture/NPC/F1.png");
	this->T_NPC[9].loadFromFile("Texture/NPC/F2.png");
	this->T_NPC[10].loadFromFile("Texture/NPC/F3.png");
	this->T_NPC[11].loadFromFile("Texture/NPC/F4.png");
	//normal
	this->T_NPC[12].loadFromFile("Texture/NPC/map3.1.1.png");
	this->T_NPC[13].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[14].loadFromFile("Texture/NPC/map3.1.2.png");
	//paint
	this->T_NPC[15].loadFromFile("Texture/NPC/map3.2.1.png");
	this->T_NPC[16].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[17].loadFromFile("Texture/NPC/map3.2.2.png");
	//Wrench
	this->T_NPC[18].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[19].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[20].loadFromFile("Texture/NPC/Box.png");
	//teacher
	this->T_NPC[21].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[22].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[23].loadFromFile("Texture/NPC/Box.png");
	//football
	this->T_NPC[24].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[25].loadFromFile("Texture/NPC/Box.png");
	this->T_NPC[26].loadFromFile("Texture/NPC/Box.png");
		//Shop Map
	this->T_NPC[27].loadFromFile("Texture/NPC/Flower1.png");
	this->T_NPC[28].loadFromFile("Texture/NPC/Flower2.png");
	this->T_NPC[29].loadFromFile("Texture/NPC/Flower3.png");
	this->T_NPC[30].loadFromFile("Texture/NPC/CarShow1.png");
	this->T_NPC[31].loadFromFile("Texture/NPC/CarShow2.png");
	this->T_NPC[32].loadFromFile("Texture/NPC/CarShow3.png");
	this->T_NPC[33].loadFromFile("Texture/NPC/CarRun1.png");
	this->T_NPC[34].loadFromFile("Texture/NPC/CarRun2.png");
	this->T_NPC[34].loadFromFile("Texture/NPC/CarRun3.png");
	this->T_NPC[35].loadFromFile("Texture/NPC/Bus.png");

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
		this->S_cur_Map.move(-3 * gameSpeed, 0);

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next -1].getSize().x != 0)
		{
			this->S_new_Map.move(-3 * gameSpeed, 0);
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
			this->S_new_Map.setPosition(1800.0f, 0.0f);
			if (this->next != 10) this->S_door.setPosition(1800, 0.0f);
			if (this->useMap != -1)
			{
				cout << "DO1" << endl;
				this->S_new_Map.setTexture(this->T_Map[this->useMap]);
				this->next = 9;
				//this->way = this->useMap;
				this->useMap = -1;
			}
			else if (this->next - 1 >= 4 && this->next - 1 <= 8)
			{
				cout << "DO2" << endl;
				this->next = 9;
				this->S_new_Map.setTexture(this->T_Map[this->next]);
				this->next++;
				//cout << "Do This2" << endl;
			}
			else
			{
				cout << "DO3" << endl;
				this->S_new_Map.setTexture(this->T_Map[this->next]);
				if (this->next == 4)
				{
					this->next = 9;
					this->way = -1;
				}
				else this->next++;
			}
		}
	}
	else
	{
		this->S_new_Map.move(-3 * gameSpeed, 0);
		if (this->S_cur_Map.getPosition().x + this->T_Map[this->next-1].getSize().x != 0)
		{
			this->S_cur_Map.move(-3 * gameSpeed, 0);
		}

		if (int(this->S_new_Map.getPosition().x) ==402)
		{
			if (this->next - 1 == 3) // P T W F
			{
				//cout << "EIEI" << endl;
				if (this->counter[ID_FOOTBALL] >= 6) { this->mutiChoice.Set(3); this->countChoice++;/* cout << "EIEI" << endl;*/ }
				if (this->counter[ID_PAINTER] >= 6) { this->mutiChoice.Set(0); this->countChoice++; /*cout << "EIEI" << endl; */}
				if (this->counter[ID_WRENCH] >= 6) { this->mutiChoice.Set(2); this->countChoice++; /*cout << "EIEI" << endl;*/ }
				if (this->counter[ID_TEACHER] >= 6) { this->mutiChoice.Set(1); this->countChoice++;/* cout << "EIEI" << endl; */}
				if (this->countChoice > 1)
				{
					//cout << "Show" << endl;
					this->pause = true;
				}
			}
			//player.updateRec(this->indexPlayer);
			//indexPlayer++;
			updateChalacter(true);
			updateBar();
			loadItems();	
		}

		if (this->S_new_Map.getPosition().x + this->T_Map[this->next].getSize().x == 1800)
		{
			B_nowusemap = !B_nowusemap;

			//this->S_cur_Map.setTexture(T_Map[this->next]);
			this->S_cur_Map.setPosition(1800.0f, 0.0f);
			if(this->next != 10) this->S_door.setPosition(1800, 0.0f);
			if (this->useMap != -1)
			{
				cout << "DO" << endl;
				this->S_cur_Map.setTexture(this->T_Map[this->useMap]);
				this->next=9;
				this->way = this->useMap;
				cout << " " << this->way << endl;
				this->useMap = -1;
			}
			else if (this->next - 1 >= 4 && this->next -1 <= 8)
			{
				cout << "DO2" << endl;
				this->next = 9;
				this->S_cur_Map.setTexture(this->T_Map[this->next]);
				this->next++;
				//cout << "Do This2" << endl;
			}
			else
			{
				cout << "DO3" << endl;
				this->S_cur_Map.setTexture(this->T_Map[this->next]);

				if (this->next == 4)
				{
					this->next = 9;
					this->way = -1;
				}
				else this->next++;
			}
		}
	}
	if (this->next == 13)
	{
		*this->stateGame = 2;
	}
	if (!pause) this->S_door.move(-3 * gameSpeed, 0);
	//cout << this->next << endl;
}


void InGame::loadItems()
{
	srand(time(NULL));
	int tempPos[5] = { 290,650,300,630,320 };
	int tempID;
	int R = 0;
	int randTemp;
	switch (this->next-1)
	{
	case 0:
		for (int j = 0; j < 12; j++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size()-1]->loadData(this->T_items[idItem1[0] - 1], idItem1[0], this->window, Vector2f(positionItem1[j] + rand() % 200, tempPos[(j + rand() % 5) % 5]));
		}
		for (int j = 0; j < 1; j++) 
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size()-1]->setDATA(T_NPC[idNPC1[j]], positionNPC1[j], &this->yPos, idNPC1[j], this->window, this->event);
		}
		break;
	case 1:
		this->itemList.clear();
		this->npcList.clear();
		for (int j = 0; j < 9; j++)
		{
			//cout << j%3 << endl;
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size()-1]->loadData(this->T_items[idItem2[0] - 1], idItem2[0], this->window, Vector2f(positionItem2[j], tempPos[0]));
		}
		for (int j = 0; j < 9; j++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size()-1]->setDATA(T_NPC[idNPC2[j]], positionNPC2[j], &this->yPos, idNPC2[j], this->window, this->event);
		}
		break;
	case 2:
		this->itemList.clear();
		this->npcList.clear();
		for (int j = 0; j < 32; j++)
		{
			//cout << j%3 << endl;
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem3[j % 4] - 1], idItem3[j % 4], this->window, Vector2f(positionItem3[j] + rand() % 200, tempPos[(j + rand() % 5) % 5]));
		}
	    randTemp = rand() % 3;
		if (randTemp == 0)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_WRENCH], positionNPC3[0], &this->yPos, ID_NPC_WRENCH, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_PAINTER], positionNPC3[1], &this->yPos, ID_NPC_PAINTER, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_FOOTBALL], positionNPC3[2], &this->yPos, ID_NPC_FOOTBALL, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_TEACHER], positionNPC3[3], &this->yPos, ID_NPC_TEACHER, this->window, this->event);
		}
		else if (randTemp == 1)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_TEACHER], positionNPC3[0], &this->yPos, ID_NPC_TEACHER, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_FOOTBALL], positionNPC3[1], &this->yPos, ID_NPC_FOOTBALL, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_WRENCH], positionNPC3[2], &this->yPos, ID_NPC_WRENCH, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_PAINTER], positionNPC3[3], &this->yPos, ID_NPC_PAINTER, this->window, this->event);
		}
		else if (randTemp == 2)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_FOOTBALL], positionNPC3[0], &this->yPos, ID_NPC_FOOTBALL, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_PAINTER], positionNPC3[1], &this->yPos, ID_NPC_PAINTER, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_TEACHER], positionNPC3[2], &this->yPos, ID_NPC_TEACHER, this->window, this->event);
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[ID_NPC_WRENCH], positionNPC3[3], &this->yPos, ID_NPC_WRENCH, this->window, this->event);
		}
		break;
	case 3: // MAP4
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 4; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC4[i]], positionNPC4[i], &this->yPos, idNPC4[i], this->window, this->event);
		}
		break;
	case 4: // MAP5
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 12; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem56789[0] - 1], idItem56789[0], this->window, Vector2f(positionItem56789[i] + rand() % 200, tempPos[i%5]));
		}
		for (int i = 0; i < 7; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567892[0] - 1], idItem567892[0], this->window, Vector2f(positionItem567892[i] + rand() % 200, tempPos[(i+rand()) % 5]));
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567893[i%2] - 1], idItem567893[i%2], this->window, Vector2f(positionItem567893[i] + rand() % 200, tempPos[(i + rand()) % 5]));
		}
		/*if (this->useMap != -1)
		{
			switch (this->useMap)
			{
			case 5: // Painter
				for (int i = 0; i < 3; i++)
				{
					this->npcList.push_back(new NPC());
					this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC6[i]], positionNPC6[i], &this->yPos, idNPC6[i], this->window, this->event);
				}
				break;
			case 6:
				for (int i = 0; i < 3; i++)
				{
					this->npcList.push_back(new NPC());
					this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC7[i]], positionNPC7[i], &this->yPos, idNPC7[i], this->window, this->event);
				}
				break;
			case 7:
				for (int i = 0; i < 3; i++)
				{
					this->npcList.push_back(new NPC());
					this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC8[i]], positionNPC8[i], &this->yPos, idNPC8[i], this->window, this->event);
				}
				break;
			case 8:
				for (int i = 0; i < 3; i++)
				{
					this->npcList.push_back(new NPC());
					this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC9[i]], positionNPC9[i], &this->yPos, idNPC9[i], this->window, this->event);
				}
				break;
			}
		}
		else
		{*/
			//cout << "Debug : " << this->useMap << " --- " << this->next - 1 << endl;
		for (int i = 0; i < 3; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC5[i]], positionNPC5[i], &this->yPos, idNPC5[i], this->window, this->event);
		}
		//}
		break;
	case 5: // MAP6
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 3; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC6[i]], positionNPC6[i], &this->yPos, idNPC6[i], this->window, this->event);
		}
		for (int i = 0; i < 12; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem56789[0] - 1], idItem56789[0], this->window, Vector2f(positionItem56789[i] + rand() % 200, tempPos[i % 5]));
		}
		for (int i = 0; i < 7; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567892[0] - 1], idItem567892[0], this->window, Vector2f(positionItem567892[i] + rand() % 200, tempPos[(i + rand()) % 5]));
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567893[i % 2] - 1], idItem567893[i % 2], this->window, Vector2f(positionItem567893[i] + rand() % 200, tempPos[(i + rand()) % 5]));
		}
		break;
	case 6: // MAP7
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 3; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC7[i]], positionNPC7[i], &this->yPos, idNPC7[i], this->window, this->event);
		}
		for (int i = 0; i < 12; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem56789[0] - 1], idItem56789[0], this->window, Vector2f(positionItem56789[i] + rand() % 200, tempPos[i % 5]));
		}
		for (int i = 0; i < 7; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567892[0] - 1], idItem567892[0], this->window, Vector2f(positionItem567892[i] + rand() % 200, tempPos[(i + rand()) % 5]));
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567893[i % 2] - 1], idItem567893[i % 2], this->window, Vector2f(positionItem567893[i] + rand() % 200, tempPos[(i + rand()) % 5]));
		}
		break;
	case 7: // MAP5
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 3; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC8[i]], positionNPC8[i], &this->yPos, idNPC8[i], this->window, this->event);
		}
		for (int i = 0; i < 12; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem56789[0] - 1], idItem56789[0], this->window, Vector2f(positionItem56789[i] + rand() % 200, tempPos[i % 5]));
		}
		for (int i = 0; i < 7; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567892[0] - 1], idItem567892[0], this->window, Vector2f(positionItem567892[i] + rand() % 200, tempPos[(i + rand()) % 5]));
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567893[i % 2] - 1], idItem567893[i % 2], this->window, Vector2f(positionItem567893[i] + rand() % 200, tempPos[(i + rand()) % 5]));
		}
		break;
	case 8: // MAP5
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 3; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC9[i]], positionNPC9[i], &this->yPos, idNPC9[i], this->window, this->event);
		}
		for (int i = 0; i < 12; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem56789[0] - 1], idItem56789[0], this->window, Vector2f(positionItem56789[i] + rand() % 200, tempPos[i % 5]));
		}
		for (int i = 0; i < 7; i++)
		{
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567892[0] - 1], idItem567892[0], this->window, Vector2f(positionItem567892[i] + rand() % 200, tempPos[(i + rand()) % 5]));
			this->itemList.push_back(new Item());
			this->itemList[this->itemList.size() - 1]->loadData(this->T_items[idItem567893[i % 2] - 1], idItem567893[i % 2], this->window, Vector2f(positionItem567893[i] + rand() % 200, tempPos[(i + rand()) % 5]));
		}
		break;
	case 9://Shop
		this->itemList.clear();
		this->npcList.clear();
		for (int i = 0; i < 6; i++)
		{
			this->npcList.push_back(new NPC());
			this->npcList[this->npcList.size() - 1]->setDATA(T_NPC[idNPC10[i]], positionNPC10[i], &this->yPos, idNPC10[i], this->window, this->event);
		}
		break;
	}
}

int InGame::positionNow()
{
	if (B_nowusemap)
	{
		return int(round(fabs(this->S_cur_Map.getPosition().x)));
	}
	else
	{
		return int(round(fabs(this->S_new_Map.getPosition().x)));
	}
}


void InGame::updateChalacter(bool state)
{
	int temp;
	if (state)
	{
		switch (this->indexPlayer)
		{
		case 0: case 1: this->indexPlayer = 2; // Player in map2
			break;
		case 2: case 3: this->indexPlayer = 4; // set player to Map 3 --> boy in school
			//cout << "Check case" << endl;
			break;
		case 4:
			if(this->next != 4)
			if (this->way != -1)
			{
				switch (this->way)
				{
				case 5: // Paint
					this->indexPlayer = 6;
					//cout << "Painter" << endl;
					break;
				case 6:
					this->indexPlayer = 7;
					cout << "A" << endl;
					break;
				case 7:
					this->indexPlayer = 8;
					cout << "B" << endl;
					break;
				case 8:
					this->indexPlayer = 9;
				//	cout << "C" << endl;
					break;
				}
			//	cout << "ASDAASDAQSDASDASD" <<this->way << endl;
			}
			else
			{
				this->indexPlayer = 5;
			//cout << "Do Normal" << endl;
			}
			
			break;
		}
		this->soundManage->playLvUp();
	}
	else
	{
		switch (this->indexPlayer) // this is a paint Action!!! <<<---
		{
		case 3:
			this->soundManage->playPaint();
			this->pause = true;
			this->counter[ID_PAINTACTION]++;
			//cout << "Pause" << endl;
			break;
		}
	}
	if (this->indexPlayer == 1) this->soundManage->playLvUp();
	player.updateRec(this->indexPlayer);
	//cout << this->indexPlayer << endl;
}

bool InGame::checkColilistion(Item* item)
{
	//cout << "Player : "<< this->player.getPosition().x << " " << this->player.getPosition().y << endl;
	//cout << "Item : " << item->getPosition().x << " " << item->getPosition().y << endl;
	return (abs(this->player.getPosition().x-item->getPosition().x) < this->player.getHalfsize().x*0.8 + item->getHalfsize().x*0.6 &&
			abs(this->player.getPosition().y-item->getPosition().y) < this->player.getHalfsize().y*0.8 + item->getHalfsize().y*0.6);
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
		this->counter[ID_BEAR]++;
		this->bar.hp(-0.5f);
		this->bar.happy(0.3f);
		break;
	case ID_CANDY:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPDOWN]);
		this->faceList.push_back(tempFace);
		this->counter[ID_CANDY]++;
		this->bar.hp(-0.3f);
		this->bar.happy(0.3f);
		break;
	case ID_FOOD:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_MONEYDOWN]);
		this->faceList.push_back(tempFace);
		this->counter[ID_FOOD]++;
		this->bar.hp(2.0f);
		this->bar.happy(2.0f);
		this->money -= 20;
		break;
	case ID_FOOD2:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_MONEYDOWN]);
		this->faceList.push_back(tempFace);
		this->counter[ID_FOOD2]++;
		this->bar.hp(2.0f);
		this->bar.happy(2.0f);
		this->money -= 20;
		break;
	case ID_FOOTBALL:
		this->counter[ID_FOOTBALL]++;
		if (this->mainArchive != ID_FOOTBALL)
		{
			addFace(this->T_face[ID_FACE_SAD]);
			this->faceList.push_back(tempFace);
			this->bar.happy(-0.3f);
		}
		break;
	case ID_MILK:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_HPUP]);
		this->faceList.push_back(tempFace);
		this->counter[ID_MILK]++;
		this->bar.hp(0.3f);
		this->bar.happy(0.3f);
		break;
	case ID_IQ:
		addFace(this->T_face[ID_FACE_HAPPY]);
		this->faceList.push_back(tempFace);
		this->bar.happy(0.5f);
		this->counter[ID_IQ]++;
		break;
	case ID_MONEY:
		this->money += 55;
		addFace(this->T_face[ID_FACE_MONEYUP]);
		this->faceList.push_back(tempFace);
		addFace(this->T_face[ID_FACE_SAD]);
		this->faceList.push_back(tempFace);
		this->bar.happy(-3.0f);
		break;
	case ID_PAINTER:
		this->counter[ID_PAINTER]++;
		if (this->mainArchive != ID_PAINTER)
		{
			addFace(this->T_face[ID_FACE_SAD]);
			this->faceList.push_back(tempFace);
			this->bar.happy(-0.3f);
		}
		break;
	case ID_TEACHER:
		this->counter[ID_TEACHER]++;
		if (this->mainArchive != ID_TEACHER)
		{
			addFace(this->T_face[ID_FACE_SAD]);
			this->faceList.push_back(tempFace);
			this->bar.happy(-0.3f);
		}
		break;
	case ID_WRENCH:
		this->counter[ID_WRENCH]++;
		if (this->mainArchive != ID_WRENCH)
		{
			addFace(this->T_face[ID_FACE_SAD]);
			this->faceList.push_back(tempFace);
			this->bar.happy(-0.3f);
		}
		break;
	}
}

void InGame::addFace(Texture texture)
{
	this->tempFace = new statusFace(texture, this->player.getPosition() + Vector2f(float(this->boxForFace[this->indexFaceX]), float(this->boxForFace[this->indexFaceY])));
	this->indexFaceX = (this->indexFaceX > 4 ? 0 : this->indexFaceX + 1);
	this->indexFaceY = (this->indexFaceY > 4 ? 0 : this->indexFaceY + 1);
}

void InGame::firstArchive(int index)
{

	//cout << "Main Archive : " << index << endl;
	switch (index)
	{
	case ID_NPC_FOOTBALL: this->mainArchive = ID_FOOTBALL; break;
	case ID_NPC_WRENCH:   this->mainArchive = ID_WRENCH;   break;
	case ID_NPC_TEACHER:  this->mainArchive = ID_TEACHER;  break;
	case ID_NPC_PAINTER:  this->mainArchive = ID_PAINTER;  break;
	}

	for (int k = 0; k < 4; k++)
	{
		NPC* p = npcList.at(0);
		delete p;
		this->npcList.erase(this->npcList.begin() + 0);
		//cout << "this is a npcList size : " << this->npcList.size() << endl;
	}
	
	this->Object = index;
	bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5], this->next - 1);
	//cout << this->npcList.size() << endl;
}

void InGame::updateBar()
{
	switch (this->next-1)
	{
	case 0: // MAP 1
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
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5],this->next-1);
		break;
	case 1: // MAP2
		this->Object =0;
		this->Object2[0] = false;
		this->Object2[1] = false;
		for (int i = 0; i < 6; i++)
		{
			this->ID[i] = 0;
			this->Status[i] = 0;
		}
		this->ID[0] = ID_SHOWBAR_IQ;
		this->ID[1] = ID_SHOWBAR_CAT;
		this->ID[2] = ID_SHOWBAR_PAINTACTION;
		//this->ID[1] = ID_SHOWBAR_FOOD1;
		//this->ID[2] = ID_SHOWBAR_FOOD2;
		this->Status[0] = &this->counter[ID_IQ];
		this->Status[1] = &this->counter[ID_CAT];
		this->Status[2] = &this->counter[ID_PAINTACTION];
		//this->Status[1] = &this->counter[ID_FOOD];
		//this->Status[2] = &this->counter[ID_FOOD2];
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5],this->next-1);
		break;
	case 2: // Map 3 
		this->Object = 0;
		this->Object2[0] = true;
		this->Object2[1] = true;
		for (int i = 0; i < 6; i++)
		{
			this->ID[i] = 0;
			this->Status[i] = 0;
		}
		this->ID[0] = ID_SHOWBAR_FOOTBALL;
		this->ID[1] = ID_SHOWBAR_TEACHER;
		this->ID[2] = ID_SHOWBAR_PAINTER;
		this->ID[3] = ID_SHOWBAR_WRENCH;
		this->Status[0] = &this->counter[ID_FOOTBALL];
		this->Status[1] = &this->counter[ID_TEACHER];
		this->Status[2] = &this->counter[ID_PAINTER];
		this->Status[3] = &this->counter[ID_WRENCH];
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5], this->next - 1);
		break;
	case 3: // Map4 
		for (int i = 0; i < 6; i++)
		{
			this->ID[i] = 0;
			this->Status[i] = 0;
		}
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5], this->next - 1);
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		for (int i = 0; i < 6; i++)
		{
			this->ID[i] = 0;
			this->Status[i] = 0;
		}
		this->ID[0] = ID_SHOWBAR_BEER;
		this->Status[0] = &this->counter[ID_BEAR];
		bar.setup(&this->Object, &this->Object2[0], &this->Object2[1], &this->ID[0], this->Status[0], this->Status[1], this->Status[2], this->Status[3], this->Status[4], this->Status[5], this->next - 1);
		break;
	}
}


///----------///
/*
map 5 normal
map 6 paint
map 7 wrench
map 8 teacher
map 9 football
*/
///----------///

int InGame::calc(int idNPC)
{
	srand(time(NULL));
	int ran = rand() % 100 + 1;
	int base = 10;
	switch (idNPC)
	{
	case ID_NPC_FRIEND1:
		base += this->counter[ID_PAINTACTION] * 25;
		break;
	case ID_NPC_FRIEND2:
		base += this->counter[ID_CAT] * 25 - this->counter[ID_FRIEND1] * 10;
		break;
	case ID_NPC_FRIEND3:
		base += this->counter[ID_CAT] * 25 - this->counter[ID_FRIEND1] * 10;
		break;
	case ID_NPC_FRIEND4:
		base += this->counter[ID_CAT] * 25 - this->counter[ID_FRIEND1] * 10;
		break;
		//------//    IQ 9
	case ID_NPC_PAINT_1://		10+24+25+15 = 74
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_PAINTER]) + this->counter[ID_PAINTACTION] * 5;
		break;
	case ID_NPC_PAINT_2:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_PAINTER]) + this->counter[ID_PAINTACTION] * 5;
		break;
	case ID_NPC_PAINT_3:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_PAINTER]) + this->counter[ID_PAINTACTION] * 5;
		break;
		//------//
	case ID_NPC_OFFICE_1: // 10+60+3+3+3 = 79
		base += this->counter[ID_IQ] * 5 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
	case ID_NPC_OFFICE_2:
		base += this->counter[ID_IQ] * 5 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
	case ID_NPC_OFFICE_3:
		base += this->counter[ID_IQ] * 5 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
		//------//
	case ID_NPC_WRENCH_1: // 10+24+25+9+4 = 69
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_WRENCH]) + this->counter[ID_PAINTACTION] * 3 + this->counter[ID_FRIEND1] * 4;
		break;
	case ID_NPC_WRENCH_2:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_WRENCH]) + this->counter[ID_PAINTACTION] * 3 + this->counter[ID_FRIEND1] * 4;
		break;
	case ID_NPC_WRENCH_3:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_WRENCH]) + this->counter[ID_PAINTACTION] * 3 + this->counter[ID_FRIEND1] * 4;
		break;
		//------//
	case ID_NPC_FOOTBALL_1: // 10+24+25+4+9 = 72
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_FOOTBALL]) + this->counter[ID_BABYCAR] * 4 + this->counter[ID_PAINTACTION] * 3;
		break;
	case ID_NPC_FOOTBALL_2:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_FOOTBALL]) + this->counter[ID_BABYCAR] * 4 + this->counter[ID_PAINTACTION] * 3;
		break;
	case ID_NPC_FOOTBALL_3:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_FOOTBALL]) + this->counter[ID_BABYCAR] * 4 + this->counter[ID_PAINTACTION] * 3;
		break;
		//------// 10 + 24 + 25 +9+3+3+3 = 77
	case ID_NPC_TEACHER_1:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_TEACHER]) + this->counter[ID_CAT] * 3 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
	case ID_NPC_TEACHER_2:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_TEACHER]) + this->counter[ID_CAT] * 3 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
	case ID_NPC_TEACHER_3:
		base += this->counter[ID_IQ] * 2 + calBase(this->counter[ID_TEACHER]) + this->counter[ID_CAT] * 3 + this->counter[ID_FRIEND2] * 3 + this->counter[ID_FRIEND3] * 3 + this->counter[ID_FRIEND4] * 3;
		break;
	}
	//cout << "----- :: ID " << idNPC << " : rand : " << ran << " : base : " << base << endl;
	if (ran <= base)
	{
		return 2;
	}
	return 1;
}
