#include "NPC.h"

NPC::NPC()
{

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
	this->body.setTextureRect(this->rect);
	this->xNow = 0;
	this->body.setOrigin(this->texture.getSize().x / 4 / 2, this->texture.getSize().y);
	
	this->Tpess.loadFromFile("Texture/NPC/pressF.png");
	this->press.setTexture(this->Tpess);
	this->RECT = IntRect(0, 0, this->Tpess.getSize().x / 4, this->Tpess.getSize().y);
	this->press.setTextureRect(this->RECT);
	if (this->ID == ID_NPC_CAT || this->ID == ID_NPC_CATLUV)
	{
		this->body.setScale(0.8, 0.8);
	}
}

void NPC::DRAW()
{
	if(!this->spacial) checkOnHold();
	this->update();
	this->window->draw(this->body);
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

void NPC::move()
{
	//cout << this->body.getPosition().x << endl; <-- dubug and now complete!!!!!
	this->body.move(-6, 0);
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
			this->delme = 1;
			//cout << "Press !" << endl;
		}
	}
	if(this->body.getPosition().x >= 0 && this->body.getPosition().x <= 1600)
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
