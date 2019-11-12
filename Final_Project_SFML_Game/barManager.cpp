#include "barManager.h"

barManager::barManager(RenderWindow* window, Event* event)
{
	//this->ASDControl = ASD;
	this->window = window;
	this->event = event;
	this->loadTextureAll();

	this->S_grid[0].setTexture(this->T_grid[0]);
	this->S_grid[1].setTexture(this->T_grid[1]);
	this->S_hpHappy.setTexture(this->T_hpHappy);
	this->S_value[0].setTexture(this->T_value[0]);
	this->S_value[1].setTexture(this->T_value[0]);
	this->rect[0] = IntRect(0, 0, this->T_value[0].getSize().x, this->T_value[0].getSize().y);
	this->rect[1] = IntRect(0, 0, this->T_value[0].getSize().x, this->T_value[0].getSize().y);
	this->S_value[0].setTextureRect(this->rect[0]);
	this->S_value[1].setTextureRect(this->rect[1]);
	this->S_lop[0].setTexture(this->T_lop);
	this->S_lop[1].setTexture(this->T_lop);
	this->S_grid[0].setPosition(0,0);
	this->S_grid[1].setPosition(0, 750);
	this->S_value[0].setPosition(20, 20);
	this->S_value[1].setPosition(60, 20);
	this->S_lop[0].setPosition(90.0f, 58.5f);
	this->S_lop[1].setPosition(520.0f, 59.0f);
	this->S_value[0].setPosition(90.0f, 58.5f);
	this->S_value[1].setPosition(520.0f, 59.0f);
	this->S_hpHappy.setPosition(10.0f, 15.0f);


	// DOWN
	this->S_bgObject[0].setTexture(this->T_object);
	this->S_bgObject[1].setTexture(this->T_object);
	this->S_bgObject[2].setTexture(this->T_object);
	this->S_bgObject[0].setPosition(100, 765);
	this->S_bgObject[1].setPosition(250, 765);
	this->S_bgObject[2].setPosition(400, 765);

	this->Rec = IntRect(0, 0, this->T_onLoad.getSize().x, this->T_onLoad.getSize().y);
	this->RecHeigh = T_onLoad.getSize().x;

	for (int i = 0; i < 6; i++) this->S_bgItemCount[i].setTexture(this->T_itemCount);
	for (int i = 0; i < 3; i++)
	{
		this->S_Grid[i].setTexture(this->T_Grid[0]);
		this->S_onLoad[i].setTexture(this->T_onLoad);
	}
	this->S_bgItemCount[0].setPosition(600, 760);
	this->S_bgItemCount[1].setPosition(600, 825);
	this->S_bgItemCount[2].setPosition(800, 760);
	this->S_bgItemCount[3].setPosition(800, 825);
	this->S_bgItemCount[4].setPosition(1000, 760);
	this->S_bgItemCount[5].setPosition(1000, 825);
	this->S_onLoad[0].setPosition(103, 765);
	this->S_onLoad[1].setPosition(253, 765);
	this->S_onLoad[2].setPosition(403, 765);
	this->S_Grid[0].setPosition(98, 763);
	this->S_Grid[1].setPosition(248, 763);
	this->S_Grid[2].setPosition(398, 763);
	this->S_archiveInobject.setPosition(118, 783);
	this->S_Family.setPosition(418, 783);
	this->S_Friend.setPosition(268, 783);
	this->font.loadFromFile("Font/impact.ttf");
	this->countItem[0].setFont(font);
	this->countItem[0].setString("0/10");
	this->countItem[0].setCharacterSize(20);
	this->countItem[0].setFillColor(Color::White);
	this->countItem[0].setPosition(680, 780);

	this->countItem[1].setFont(font);
	this->countItem[1].setString("0/10");
	this->countItem[1].setCharacterSize(20);
	this->countItem[1].setFillColor(Color::White);
	this->countItem[1].setPosition(680, 845);

	this->countItem[2].setFont(font);
	this->countItem[2].setString("0/10");
	this->countItem[2].setCharacterSize(20);
	this->countItem[2].setFillColor(Color::White);
	this->countItem[2].setPosition(880, 780);

	this->countItem[3].setFont(font);
	this->countItem[3].setString("0/10");
	this->countItem[3].setCharacterSize(20);
	this->countItem[3].setFillColor(Color::White);
	this->countItem[3].setPosition(880, 845);

	this->countItem[4].setFont(font);
	this->countItem[4].setString("0/10");
	this->countItem[4].setCharacterSize(20);
	this->countItem[4].setFillColor(Color::White);
	this->countItem[4].setPosition(1080, 780);

	this->countItem[5].setFont(font);
	this->countItem[5].setString("0/10");
	this->countItem[5].setCharacterSize(20);
	this->countItem[5].setFillColor(Color::White);
	this->countItem[5].setPosition(1080, 845);

	// For Test Only!
	//this->S_archiveInobject.setTexture(this->T_Archive[0]);
	this->S_Family.setTexture(this->T_Family[1]);
	this->S_Friend.setTexture(this->T_Friend[1]);
}

void barManager::DRAW()
{

	//Top
	updateHpHappy();
	this->window->draw(this->S_grid[0]);
	this->window->draw(this->S_grid[1]);
	this->window->draw(this->S_value[0]);
	this->window->draw(this->S_value[1]);
	this->window->draw(this->S_lop[0]);
	this->window->draw(this->S_lop[1]);
	this->window->draw(this->S_hpHappy);

	// Down
	press();
	updateCounter();
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(this->S_bgObject[i]);
	}
	this->window->draw(this->S_archiveInobject);
	this->window->draw(this->S_Family);
	this->window->draw(this->S_Friend);
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(this->S_onLoad[i]);
		this->window->draw(this->S_Grid[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		if (IHide[i])
		{
			window->draw(this->S_bgItemCount[i]);
			window->draw(this->countItem[i]);
		}
	}
	if (this->B_onLoad) onLoad();
	else Active();
	this->ASD.draw(this->window);
}

void barManager::setup(int* O1, bool* O2, bool* O3, int* D, int* I1, int* I2, int* I3, int* I4, int* I5, int* I6,int map)
{
	//setPointer!
	if (this->map == 1 && !this->setFirst)
	{
		setFirst = true;
		this->B_onLoad = false;
		this->Rec.height = 0;
		for (int i = 0; i < 3; i++)
		{
		
			this->S_onLoad[i].setTextureRect(this->Rec);
		}
	}
	this->map = map;
	this->pointerCount[0] = I1;
	this->pointerCount[1] = I2;
	this->pointerCount[2] = I3;
	this->pointerCount[3] = I4;
	this->pointerCount[4] = I5;
	this->pointerCount[5] = I6;
	// set Active
	if (*O1) this->active[0] = true;
	else this->active[0] = false;
	if (*O3) { this->active[2] = true; this->S_Family.setTexture(this->T_Family[1]); }
	else { this->active[2] = false; this->S_Family.setTexture(this->T_Family[0]); }
	if (*O2) { this->active[1] = true; this->S_Friend.setTexture(this->T_Friend[1]); }
	else { this->active[1] = false; this->S_Friend.setTexture(this->T_Friend[0]); }
	//for object 1
	switch (*O1)
	{ // f p t w // listItem
	case 0: this->S_archiveInobject.setTexture(this->T_Q); break;
	case ID_NPC_FOOTBALL: this->S_archiveInobject.setTexture(this->T_Archive[0]); break;
	case ID_NPC_PAINTER : this->S_archiveInobject.setTexture(this->T_Archive[1]); break;
	case ID_NPC_TEACHER : this->S_archiveInobject.setTexture(this->T_Archive[2]); break;
	case ID_NPC_WRENCH  : this->S_archiveInobject.setTexture(this->T_Archive[3]); break;
	}
	for (int i = 0; i < 6; i++)
	{
		this->countItem[i].setFillColor(Color::White); // reset color
		if (*(D + i) != 0)
		{
			switch (*(D + i))
			{
			case 1: this->S_bgItemCount[i].setTexture(this->T_I[0]); break;
			case 2: this->S_bgItemCount[i].setTexture(this->T_I[1]); break;
			case 3: this->S_bgItemCount[i].setTexture(this->T_I[2]); break;
			case 4: this->S_bgItemCount[i].setTexture(this->T_I[3]); break;
			case 5: this->S_bgItemCount[i].setTexture(this->T_I[4]); break;
			case 6: this->S_bgItemCount[i].setTexture(this->T_I[5]); break;
			case 7: this->S_bgItemCount[i].setTexture(this->T_I[6]); break;
			case 8: this->S_bgItemCount[i].setTexture(this->T_I[7]); break;
			case 9: this->S_bgItemCount[i].setTexture(this->T_I[8]); break;
			case 10:this->S_bgItemCount[i].setTexture(this->T_I[9]); break;
			}
			IHide[i] = true;
		}
		else
		{
			IHide[i] = false;
		}
	}
}

void barManager::press()
{
	if (!this->B_onLoad)
	{
		//cout << "Can press!" << endl;
		if (Keyboard::isKeyPressed(Keyboard::A) && this->active[0])
		{
			cout << "barManager :: Press A" << endl;
			this->ASD.setAction(0);
			this->B_onLoad = true;
			this->S_Grid[0].setTexture(this->T_Grid[0]);
			this->S_Grid[1].setTexture(this->T_Grid[0]);
			this->S_Grid[2].setTexture(this->T_Grid[0]);
		}	
	}
}

void barManager::hp(float val)
{
	this->hp_Val += val;
	if (this->hp_Val > 60) this->hp_Val = 60;
	if (this->hp_Val < 0) this->hp_Val = 0;
}

void barManager::happy(float val)
{
	this->happy_Val += val;
	if (this->happy_Val > 60) this->happy_Val = 60;
	if (this->happy_Val < 0 ) this->happy_Val = 0;
}

void barManager::Active()
{
	this->totalTime += this->clock.restart().asSeconds();
	if (this->totalTime >= 0.2)
	{
		this->totalTime = 0;
		for (int i = 0; i < 3; i++)
		{
			if (this->active[i])
			{
				//cout << "Active!" << endl;
				if(this->active[i])this->S_Grid[i].setTexture(this->T_Grid[this->B_Switch]);
			}
		}
		this->B_Switch = !this->B_Switch;
	}
}

void barManager::loadTextureAll()
{
	// Top
	this->T_value[0].loadFromFile("Texture/barmanage/G1.png");
	this->T_value[1].loadFromFile("Texture/barmanage/G2.png");
	this->T_value[2].loadFromFile("Texture/barmanage/G3.png");
	this->T_value[3].loadFromFile("Texture/barmanage/G4.png");
	this->T_value[4].loadFromFile("Texture/barmanage/G5.png");
	this->T_value[5].loadFromFile("Texture/barmanage/G6.png");
	this->T_value[6].loadFromFile("Texture/barmanage/G7.png");
	this->T_hpHappy.loadFromFile("Texture/barmanage/hp_happy_bar.png");
	this->T_grid[0].loadFromFile("Texture/barmanage/gridTOP.png");
	this->T_grid[1].loadFromFile("Texture/barmanage/gridDOWN.png");
	this->T_lop.loadFromFile("Texture/barmanage/E.png");

	// Down
	this->T_object.loadFromFile("Texture/barmanage/Active1.png");
	this->T_itemCount.loadFromFile("Texture/barmanage/itemCount.png");
	this->T_onLoad.loadFromFile("Texture/barmanage/onload.png");
	this->T_Grid[0].loadFromFile("Texture/barmanage/Grid.png");
	this->T_Grid[1].loadFromFile("Texture/barmanage/GridActive.png");
	this->T_Archive[0].loadFromFile("Texture/barmanage/f.png");
	this->T_Archive[1].loadFromFile("Texture/barmanage/p.png");
	this->T_Archive[2].loadFromFile("Texture/barmanage/t.png");
	this->T_Archive[3].loadFromFile("Texture/barmanage/w.png");
	this->T_Family[0].loadFromFile("Texture/barmanage/family_black.png");
	this->T_Family[1].loadFromFile("Texture/barmanage/family.png");
	this->T_Friend[0].loadFromFile("Texture/barmanage/friend_black.png");
	this->T_Friend[1].loadFromFile("Texture/barmanage/friend.png");
	this->T_I[0].loadFromFile("Texture/barmanage/i1.png");
	this->T_I[1].loadFromFile("Texture/barmanage/i2.png");
	this->T_I[2].loadFromFile("Texture/barmanage/i3.png");
	this->T_I[3].loadFromFile("Texture/barmanage/i4.png");
	this->T_I[4].loadFromFile("Texture/barmanage/i5.png");
	this->T_I[5].loadFromFile("Texture/barmanage/i6.png");
	this->T_I[6].loadFromFile("Texture/barmanage/i7.png");
	this->T_I[7].loadFromFile("Texture/barmanage/i8.png");
	this->T_I[8].loadFromFile("Texture/barmanage/i9.png");
	this->T_I[9].loadFromFile("Texture/barmanage/i10.png");
	this->T_Q.loadFromFile("Texture/barmanage/Q.png");
}

void barManager::updateHpHappy()
{
	this->rect[0].width = (this->hp_Val * 330) / 60;
	this->rect[1].width = (this->happy_Val * 330) / 60;
	this->S_value[0].setTextureRect(this->rect[0]);
	this->S_value[1].setTextureRect(this->rect[1]);
	this->S_value[0].setTexture(this->T_value[int(6 - round(this->hp_Val/10))]);
	this->S_value[1].setTexture(this->T_value[int(6 - round(this->happy_Val / 10))]);
	this->S_value[0].setTextureRect(this->rect[0]);
	this->S_value[1].setTextureRect(this->rect[1]);
	if (this->S_lop[1].getPosition().x + 14 > this->S_value[1].getPosition().x + (happy_Val * 330) / 60)
	{
		this->S_lop[1].setPosition(520.0f, 58.5f);
	}

	if (this->S_lop[0].getPosition().x + 14 > this->S_value[0].getPosition().x + (hp_Val * 330) / 60)
	{
		this->S_lop[0].setPosition(90.0f, 58.5f);
	}
	this->S_lop[0].move(2, 0);
	this->S_lop[1].move(2, 0);
}

void barManager::updateArchive()
{
	if (this->I_indexArchive)
	{
		switch (this->I_indexArchive)
		{
		case 1: this->S_archiveInobject.setTexture(this->T_Archive[0]);
			break;
		case 2: this->S_archiveInobject.setTexture(this->T_Archive[1]);
			break;
		case 3: this->S_archiveInobject.setTexture(this->T_Archive[2]);
			break;
		case 4: this->S_archiveInobject.setTexture(this->T_Archive[3]);
			break;
		}
	}
}

void barManager::updateCounter()
{
	switch (this->map)
	{
	case 0:
		for (int i = 0; i < 6; i++)
		{
			if (this->pointerCount[i] != nullptr)
			{
				if (*this->pointerCount[i] != 0) this->countItem[i].setFillColor(Color::Green);
				this->countItem[i].setString(to_string(*this->pointerCount[i]) + "/12");
			}
		}
		break;
	case 1:
		for (int i = 0; i < 6; i++)
		{
			if (this->pointerCount[i] != nullptr)
			{
				if (*this->pointerCount[i] != 0) this->countItem[i].setFillColor(Color::Green);
				this->countItem[i].setString(to_string(*this->pointerCount[i]) + "/9");
			}
		}
		break;
	}
}

void barManager::onLoad()
{
	this->totalTimeLoad += this->clock.restart().asSeconds();
	if (this->totalTimeLoad > 0.2)
	{
		//cout << "barmanager :: "<<this->timeLoad << endl;
		this->Rec.height = float(this->timeLoad / delay * this->RecHeigh);
		this->timeLoad-=0.2;
		this->totalTimeLoad = 0;
		if (this->timeLoad < 0)
		{
			this->B_onLoad = false;
			this->timeLoad = delay;
		}
		//cout << Rec.height << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		if(this->active[i]) this->S_onLoad[i].setTextureRect(this->Rec);
	}
}
