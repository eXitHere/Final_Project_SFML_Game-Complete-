#include "Player.h"

Player::Player(RenderWindow* window, Event* event)
{
	//cout << "Load Player" << endl;
	//LoadTexture
	this->window = window;
	this->event = event;
	this->T_texture[0].loadFromFile("Texture/Player/p1.png");
	this->T_texture[1].loadFromFile("Texture/Player/p2.png");
	this->T_texture[2].loadFromFile("Texture/Player/p3.0.png");
	this->T_texture[3].loadFromFile("Texture/Player/p3.1.png");
	this->T_texture[4].loadFromFile("Texture/Player/p4.png");
}

void Player::DRAW()
{
	//cout << this->body.getPosition().x << endl;
	controls();
	jump();
	update();
	*this->pointerToY = this->body.getPosition().y;
	this->window->draw(this->body);
	//cout << this->body.getPosition().y << endl;
}

void Player::setPointerToY(float* Y)
{
	this->pointerToY = Y;
}

Vector2f Player::getHalfsize()
{
	//cout << "eieieie" << endl;
	return Vector2f(this->T_texture[this->action_now].getSize().x/this->countPic[this->action_now]/2,this->T_texture[this->action_now].getSize().y/2);
}

Vector2f Player::getPosition()
{
	//cout << this->body.getPosition().x << " " << this->body.getPosition().y << endl;
	//cout << getHalfsize().x << " " << this->getHalfsize().y << endl;
	return (this->body.getPosition() - Vector2f(0,this->T_texture[this->action_now].getSize().y/2));
}

void Player::controls()
{
	//cout << "Press" << endl; 
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->canJump())
	{
		this->stateJump = 1;
	//	cout << "JUMP!" << endl;
	}
}

void Player::update()
{
	this->totalTime += clock.restart().asSeconds();

	if (this->totalTime >= 0.2)
	{
		this->totalTime = 0;
		this->X_now++;
		if (this->X_now > this->countPic[this->action_now]-1)
		{
			this->X_now = 0;
		}
	}
	this->rec.left = this->rec.width * this->X_now;
	this->body.setTextureRect(this->rec);
}

void Player::jump()
{
	switch (this->stateJump)
	{
	case 1:
		this->body.move(0, -this->jumpPower);
		this->jumpPower -= 0.1;
		if (this->action_now == 0 && this->body.getPosition().y < this->baseHeight[0])
		{
			this->stateJump = 2;
			this->jumpPower = 12;
		}
		else if (this->action_now == 1 && this->body.getPosition().y < this->baseHeight[1])
		{
			this->stateJump = 2;
			this->jumpPower = 20;
		}
		break;
	case 2:
		this->body.move(0, this->jumpPower);
		this->jumpPower += 0.1;
		if (this->body.getPosition().y >= 750)
		{
			this->body.setPosition(400, 750);
			this->stateJump = 0;
			this->jumpPower = 20;
		}
	}
}

bool Player::canJump()
{
	return !(this->stateJump);
}

void Player::updateRec(int newRec)
{
	this->action_now = newRec;
	this->X_now = 0;
	this->rec = IntRect(0, 0, this->T_texture[this->action_now].getSize().x / this->countPic[this->action_now], this->T_texture[this->action_now].getSize().y);
	this->body.setTexture(this->T_texture[this->action_now]);
	this->body.setOrigin(this->T_texture[this->action_now].getSize().x / this->countPic[this->action_now] /2, this->T_texture[this->action_now].getSize().y);
	this->body.setTextureRect(this->rec);
	this->body.setPosition(400.0f, 750.0f);
	if (this->stateJump != 2)
	{
		this->jumpPower = 20;
		this->stateJump = 2;
	}
}
