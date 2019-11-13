#include "actionASD.h"

actionASD::actionASD()
{
	reset();
	this->T_texture[0].loadFromFile("Texture/Action/a0.png");
	this->T_texture[1].loadFromFile("Texture/Action/a1.png");

	this->body.setPosition(1400,760);
}

void actionASD::setAction(int index)
{
	reset();
	this->indexAction = index;
	this->body.setTexture(this->T_texture[this->indexAction]);
	this->rect = IntRect(0, 0, this->T_texture[this->indexAction].getSize().x / 4, this->T_texture[this->indexAction].getSize().y);
	this->body.setTextureRect(this->rect);
	this->B_stop = false;
	this->X = 0;
	this->deltaTime = 0;
//	cout << "Debug in Action ASD" << endl;
//	cout << this->rect.left << " -- " << this->rect.top << endl;
}

void actionASD::draw(RenderWindow* window)
{
	if (!this->B_stop)
	{
		window->draw(this->body);
		update();
		//cout << "Action : " << this->indexAction << endl;
	}
}

void actionASD::reset()
{
	this->deltaTime = 0;
	this->X = 0;
}

void actionASD::update()
{
	this->deltaTime += this->clock.restart().asSeconds();
	if (this->deltaTime > 0.5)
	{
		this->deltaTime = 0;
		this->X++;
		if (this->X == 4)
		{
			this->X = 0;
			this->B_stop = true;
		}
		this->rect.left = this->X * this->rect.width;
		this->body.setTextureRect(this->rect);
	}
}
