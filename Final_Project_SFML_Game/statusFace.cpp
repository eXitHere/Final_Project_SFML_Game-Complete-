#include "statusFace.h"

statusFace::statusFace(Texture texture, Vector2f pos)
{
	//cout << pos.x << endl;
	this->texture = texture;
	this->texture.setSmooth(true);
	this->body.setTexture(this->texture);
	this->body.setPosition(pos.x, pos.y); // center X and rand Y
	this->body.setScale(1.2, 1.2);
	//cout << "Load Items" << endl;
}

void statusFace::DRAW(RenderWindow* window)
{
	this->move();
	window->draw(this->body);
}

bool statusFace::getDelete()
{
	return this->Del;
}

void statusFace::move()
{
	totalTime += clock.restart().asSeconds();
	if (totalTime >= 1.5 || this->body.getPosition().y <= 130) this->Del = true;
	this->body.move(0, -A);
	A += 0.05;
}
