#include "Item.h"
#include <time.h>
#include <stdlib.h>
 Item::Item()
{
	//cout << "Load Item complete!" << endl;
}

void Item::loadData(Texture texture, int ID, RenderWindow* window,Vector2f position)
{
	srand(time(NULL));
	this->A = rand() % 20000;
	this->window = window;
	this->texture = texture;
	this->ID = ID;
	this->body.setTexture(this->texture);
	this->rect = IntRect(0, 0, int(this->texture.getSize().x / 4), int(this->texture.getSize().y));
	this->body.setPosition(position);
	//cout << "LoadData Complete" << endl;
}

void Item::DRAW()
{
	update();
	move();
	window->draw(this->body);
}

bool Item::deleteMe()
{
	return (this->body.getPosition().x < -200);
}

Vector2f Item::getHalfsize()
{
	return Vector2f(this->texture.getSize().x / 4 /2, this->texture.getSize().y / 2);
}

Vector2f Item::getPosition()
{
	//cout << getHalfsize().x << " " << this->getHalfsize().y << endl;
	return this->body.getPosition() + this->getHalfsize();;
}

int Item::getID()
{
	return this->ID;
}

void Item::update()
{
	this->totalTime += this->clock.restart().asSeconds();
	if (this->totalTime >= 0.3)
	{
		this->totalTime = 0;
		this->X++;
		if (this->X > 3)
		{
			this->X = 0;
		}
	}
	this->rect.left = this->X * this->rect.width;
	this->body.setTextureRect(this->rect);
}

void Item::move()
{
	//cout << this->body.getPosition().x << " " << this->body.getPosition().y << endl;
	this->body.move(-7 * gameSpeed, sin(this->A));
	this->A -= 0.1;
}
