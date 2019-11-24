#include "NPC.h"

NPC::NPC()
{
	//cout << "Hello Wolrd";
}

void NPC::setDATA(Texture texture,int positionX, float* yPos, int ID,RenderWindow* window, Event* event)
{
	if (positionX == -500) spacial = true;
	this->ID = ID;
	this->yPosPlayer = yPos;
	this->window = window;
	this->event = event;
	this->texture = texture;
	this->body.setTexture(this->texture);
	this->body.setPosition(positionX, 740);
	this->rect = IntRect(0, 0, this->texture.getSize().x / 4, this->texture.getSize().y);	
	this->xNow = 0;
	this->Tpess.loadFromFile("Texture/NPC/pressF.png");
	this->press.setTexture(this->Tpess);
	this->RECT = IntRect(0, 0, this->Tpess.getSize().x / 4, this->Tpess.getSize().y);
	if (check())
	{
		this->press.setTextureRect(this->RECT);
		this->body.setOrigin(this->texture.getSize().x / 4 / 2, this->texture.getSize().y);
		this->body.setTextureRect(this->rect);
	}
	else
	{
		this->body.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y);
	}

	if (this->ID == ID_NPC_CAT || this->ID == ID_NPC_CATLUV || this->ID == ID_NPC_PAINT)
	{
		this->body.setScale(0.8, 0.8);
	}
	
	this->T_yesno[0].loadFromFile("Texture/NPC/yes.png");
	this->T_yesno[1].loadFromFile("Texture/NPC/no.png");
//	this->body_yesno.setOrigin(this->T_yesno[0].getSize().x / 2, this->T_yesno[0].getSize().y / 2);
//	this->body_yesno.setPosition(this->body.getPosition().x, this->body.getPosition().y - this->T_yesno[0].getSize().y - 50);
}

void NPC::DRAW()
{
	if(!this->spacial) checkOnHold();
	if(check())
		this->update();
	if(checkDRAW()) this->window->draw(this->body);
	if (this->yesno == 1)
	{
		if (!this->setTexture)
		{
			this->body_yesno.setTexture(this->T_yesno[1]);
			this->setTexture = true;
		}
		this->body_yesno.setPosition(this->body.getPosition().x, this->body.getPosition().y - this->texture.getSize().y - 100);
		this->window->draw(this->body_yesno);
		//cout << this->body_yesno.getPosition().x << endl;
		//cout << "AA" << endl;
	}
	else if (this->yesno == 2)
	{
		if (!this->setTexture)
		{
			this->body_yesno.setTexture(this->T_yesno[0]);
			this->setTexture = true;
		}
		this->body_yesno.setPosition(this->body.getPosition().x, this->body.getPosition().y - this->texture.getSize().y - 100);
		this->window->draw(this->body_yesno);
	}
}

void NPC::Move()
{
	move();
}

int NPC::getID()
{
	return this->ID;
}

int NPC::checkState()
{
	return this->delme;
}

bool NPC::isSpacial()
{
	return spacial;
}

Vector2f NPC::getPostiosion()
{
	return this->body.getPosition();
}

void NPC::setPosition(Vector2f pos)
{
	this->body.setPosition(pos);
}

void NPC::setYesNo(int state)
{
	this->yesno = state;
	//cout << "Set :: " << this->yesno << endl;
}

int NPC::getYesNo()
{
	return this->yesno;
}

bool NPC::checkDRAW() // LIST
{
	return this->ID != ID_NPC_PAINT_2  && this->ID != ID_NPC_OFFICE_2
		&& this->ID != ID_NPC_WRENCH_1 && this->ID != ID_NPC_WRENCH_2 && this->ID != ID_NPC_WRENCH_3 && this->ID != ID_NPC_FOOTBALL_1 && this->ID != ID_NPC_FOOTBALL_2 && this->ID != ID_NPC_FOOTBALL_3
		&& this->ID != ID_NPC_TEACHER_1 && this->ID != ID_NPC_TEACHER_2 && this->ID != ID_NPC_TEACHER_3;
}

bool NPC::check()
{
	return this->ID != ID_NPC_FRIEND1   && this->ID != ID_NPC_FRIEND2   && this->ID != ID_NPC_FRIEND3  && this->ID != ID_NPC_FRIEND4
		&& this->ID != ID_NPC_PAINT_1   && this->ID != ID_NPC_PAINT_2   && this->ID != ID_NPC_PAINT_3  && this->ID != ID_NPC_OFFICE_1   && this->ID != ID_NPC_OFFICE_2   && this->ID != ID_NPC_OFFICE_3
		&& this->ID != ID_NPC_WRENCH_1  && this->ID != ID_NPC_WRENCH_2  && this->ID != ID_NPC_WRENCH_3 && this->ID != ID_NPC_FOOTBALL_1 && this->ID != ID_NPC_FOOTBALL_2 && this->ID != ID_NPC_FOOTBALL_3
		&& this->ID != ID_NPC_TEACHER_1 && this->ID != ID_NPC_TEACHER_2 && this->ID != ID_NPC_TEACHER_3;
}

void NPC::move()
{
	//cout << this->body.getPosition().x << endl; <-- dubug and now complete!!!!!
	this->body.move(-3, 0);
	if (this->body.getPosition().x < -200)
	{
		this->delme = 2;
	}
}

void NPC::update()
{
	this->totalTime += this->clock.restart().asSeconds();
	if (this->totalTime > 0.2)
	{
		this->totalTime = 0;
		this->xNow++;
		if (this->xNow == 4)
		{
			this->xNow = 0;
		}
	}
	this->rect.left = this->rect.width * this->xNow;
	this->body.setTextureRect(this->rect);
}

void NPC::checkOnHold()
{
	//cout << *this->yPosPlayer << endl;
	/*if (abs(this->body.getPosition().x+20 - 350) < this->texture.getSize().x / 4 / 2 +40 &&
		abs(this->body.getPosition().y-this->texture.getSize().y/2 - *this->yPosPlayer) < this->texture.getSize().y/2 + 100)*/
	if (abs(this->body.getPosition().x + 20 - 350) < this->texture.getSize().x / 4 / 2 + 40 &&
		abs(this->body.getPosition().y - this->texture.getSize().y / 2 - *this->yPosPlayer) < this->texture.getSize().y / 2 + 100)
	{
		if (Keyboard::isKeyPressed(Keyboard::F) && !isSpacial())
		{
			if (check())
			{
				this->delme = 1;
			}
			else
			{
				this->delme = 3;
			}
			//cout << "Press !" << endl;
		}
	}
	if(this->body.getPosition().x >= 0 && this->body.getPosition().x <= 1600 && this->delme != 3)
	{
		updatePress();
		this->press.setPosition(this->body.getPosition().x, this->body.getPosition().y - this->texture.getSize().y-50);
		this->window->draw(this->press);
		//cout << "Chon!" << endl;
	}
}

void NPC::updatePress()
{
	this->totalTimePress += this->clockPress.restart().asSeconds();
	if (this->totalTimePress > 0.25)
	{
		this->totalTimePress = 0;
		this->XNOW++;
		if (this->XNOW == 4)
		{
			this->XNOW = 0;
		}
	}
	this->RECT.left = this->RECT.width * this->XNOW;
	this->press.setTextureRect(this->RECT);
}
