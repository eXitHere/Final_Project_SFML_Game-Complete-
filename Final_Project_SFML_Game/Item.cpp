#include "Item.h"

Item::Item()
{
	//cout << "Load Item complete!" << endl;
}

void Item::loadData(Texture texture, RenderWindow* window,Vector2f position)
{
	this->window = window;
	this->texture = texture;
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
	return (this->body.getPosition().x < 0);
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
	this->body.move(-6, sin(this->A));
	this->A -= 0.1;
}
