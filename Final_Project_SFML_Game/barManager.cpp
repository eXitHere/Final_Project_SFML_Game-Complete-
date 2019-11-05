#include "barManager.h"

barManager::barManager(RenderWindow* window, Event* event)
{
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
	this->S_grid[0].setPosition(0,0);
	this->S_grid[1].setPosition(750, 0);
	this->S_value[0].setPosition(20, 20);
	this->S_value[1].setPosition(60, 20);
}

void barManager::DRAW()
{
	this->window->draw(this->S_grid[0]);
	this->window->draw(this->S_grid[1]);
	this->window->draw(this->S_hpHappy);
	this->window->draw(this->S_value[0]);
	this->window->draw(this->S_value[1]);
}

void barManager::loadTextureAll()
{
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

}

void barManager::updateHpHappy()
{
	this->rect[0].width = (this->hp_Val * 330) / 70;
	this->rect[1].width = (this->happy_Val * 330) / 70;
	this->S_value[0].setTextureRect(this->rect[0]);
	this->S_value[1].setTextureRect(this->rect[1]);
	this->S_value[0].setTexture(this->T_value[int(6 - round(this->hp_Val/10))]);
	this->S_value[1].setTexture(this->T_value[int(6 - round(this->happy_Val / 10))]);
	this->S_value[0].setTextureRect(this->rect[0]);
	this->S_value[1].setTextureRect(this->rect[1]);
}
