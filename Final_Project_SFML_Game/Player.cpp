#include "Player.h"

Player::Player(RenderWindow* window, Event* event,bool *pause)
{
	//cout << "Load Player" << endl;
	//LoadTexture
	this->pause = pause;
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
	return Vector2f(this->T_texture[this->action_now].getSize().x/this->countPic[this->action_now]/2*0.8,this->T_texture[this->action_now].getSize().y/2*0.8);
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
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->canJump() && this->action_now != 3)
	{
		this->stateJump = 1;
	//	cout << "JUMP!" << endl;
	}
}

void Player::update()
{
	double time = 0.09;
	switch (this->action_now)
	{
	case 3: time = 0.3;
		break;
	}
	
	this->totalTime += clock.restart().asSeconds();

	if (this->totalTime >= time)
	{
		this->totalTime = 0;
		this->X_now++;
		if (this->X_now > this->countPic[this->action_now]-1)
		{
			this->X_now = 0;
			if (this->action_now == 3)
			{
				*this->pause = false;
				updateRec(2);
			}
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
		this->jumpPower -= 0.3;
		if (this->action_now == 0 && this->body.getPosition().y < this->baseHeight[0])
		{
			this->stateJump = 2;
			this->jumpPower = 5;
		}
		//if (this->action_now == 1 && this->body.getPosition().y < this->baseHeight[1])
		else if (this->body.getPosition().y < this->baseHeight[1])
		{
			this->stateJump = 2;
			this->jumpPower = 15;
		}
		break;
	case 2:
		this->body.move(0, this->jumpPower);
		this->jumpPower += 0.3;
		if (this->body.getPosition().y >= 750)
		{
			this->body.setPosition(400, 750);
			this->stateJump = 0;
			this->jumpPower = 15;
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
	this->body.setTexture(this->T_texture[this->action_now]);
	this->body.setPosition(400.0f, 750.0f);
	this->body.setOrigin(this->T_texture[this->action_now].getSize().x / this->countPic[this->action_now] / 2, this->T_texture[this->action_now].getSize().y);
	this->X_now = 0;
	this->rec = IntRect(0, 0, this->T_texture[this->action_now].getSize().x / this->countPic[this->action_now], this->T_texture[this->action_now].getSize().y);
	this->body.setTextureRect(this->rec);
	this->stateJump = 0;
	this->jumpPower = 15;
	if (this->action_now > 1)
	{
		this->body.setScale(0.8, 0.8);
	}
	switch (newRec) // set origin
	{
	case 3:
		//this->body.setOrigin(this->T_texture[this->action_now].getSize().x / this->countPic[this->action_now] / 3, this->T_texture[this->action_now].getSize().y);
		this->body.setPosition(470.0f, 750.0f);
		break;
	}
	
}
