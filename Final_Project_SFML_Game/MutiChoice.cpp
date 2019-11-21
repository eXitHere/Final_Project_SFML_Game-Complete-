#include "MutiChoice.h"

MutiChoice::MutiChoice(RenderWindow* window, Event* event)
{
	this->window = window;
	this->event = event;
	this->texture[0].loadFromFile("Texture/MutiChoice/Grid.png");
	this->texture[1].loadFromFile("Texture/MutiChoice/p.png");
	this->texture[2].loadFromFile("Texture/MutiChoice/t.png");
	this->texture[3].loadFromFile("Texture/MutiChoice/w.png");
	this->texture[4].loadFromFile("Texture/MutiChoice/f.png");
	this->Grid.setTexture(this->texture[0]);
	this->Grid.setOrigin(this->texture[0].getSize().x / 2, this->texture[0].getSize().y / 2);
	this->body.setOrigin(this->texture[0].getSize().x / 2, this->texture[1].getSize().y / 2);
	this->body.setTexture(this->texture[1]);
	//

	this->Grid.setPosition(450, 400);
	this->body.setPosition(this->Grid.getPosition().x + 60, this->Grid.getPosition().y - 15);

	//cout << "Address : " << this->window << endl;
}

void MutiChoice::DRAW()
{
	if (this->event->type == Event::EventType::TextEntered)
	{
		//cout << this->event->text.unicode << endl;

		if (((this->event->text.unicode == 13 || this->event->text.unicode == 102) && !this->keyReleased) || this->textProcess.size() == 1) // F OR Enter
		{
			this->keyReleased = true;
			//this->forReturn = this->index + 1;
			this->forReturn = this->compare[this->index];
			//cout << "Set" << endl;
		}
	}
	else if (this->event->type == Event::EventType::KeyPressed)
	{
		//cout << "EIEIE" << endl;

		if (this->event->text.unicode == 71 && this->index >= 1 && !this->keyReleased) // Left
		{
			this->keyReleased = true;
			this->index--;
			this->body.setTexture(this->textProcess[this->index]);
		}
		else if (this->event->text.unicode == 72 && this->index < this->textProcess.size() - 1 && !this->keyReleased) // Right
		{
			this->keyReleased = true;
			this->index++;
			this->body.setTexture(this->textProcess[this->index]);
		}

	}
	else if (this->event->type == Event::EventType::KeyReleased && this->keyReleased)
	{
		this->keyReleased = false;
		//cout << "reset" << endl;
	}
	//cout << this->index << endl;
	this->window->draw(this->Grid);
	this->window->draw(this->body);
	//cout << "Draw" << endl;
}

void MutiChoice::Set(int number)
{
	if (number == 0)
	{
		this->textProcess.push_back(this->texture[1]);
		this->compare.push_back(1);
	}
	if (number == 1)
	{
		this->textProcess.push_back(this->texture[2]);
		this->compare.push_back(2);
	}
	if (number == 2)
	{
		this->textProcess.push_back(this->texture[3]);
		this->compare.push_back(3);
	}
	if (number == 3)
	{
		this->textProcess.push_back(this->texture[4]);
		this->compare.push_back(4);
	}
	if (this->textProcess.size() > 0)
	{
		this->body.setTexture(this->textProcess[0]);
	}
	//cout << this->textProcess.size() << endl;
}

int MutiChoice::getChoice()
{
	if (this->forReturn == 0)
	{
		
		this->DRAW();
		return 0;
	}
	else
	{
		return this->forReturn;
	}
}
