#include "EndGame.h"

EndGame::EndGame(RenderWindow* window, Event* event, int* state)
{
	font.loadFromFile("font/Cloud-Bold.otf");
	this->event = event;
	this->window = window;
	this->stateGame = state;
	this->T_bg.loadFromFile("Texture/Endgame/bg.jpg");
	this->T_logo.loadFromFile("Texture/Endgame/logo.png");
	this->T_BlockLogo.loadFromFile("Texture/Endgame/blockLogo.png");
	this->T_status[0].loadFromFile("Texture/Endgame/pass.png");
	this->T_status[1].loadFromFile("Texture/Endgame/fail.png");
	this->T_exit[0].loadFromFile("Texture/Endgame/exit1.png");
	this->T_exit[1].loadFromFile("Texture/Endgame/exit2.png");
	this->T_score.loadFromFile("Texture/Endgame/score.png");
	this->S_bg.setTexture(this->T_bg);
	this->S_logo.setTexture(this->T_logo);
	this->S_blockLogo.setTexture(this->T_BlockLogo);
	this->S_status.setTexture(this->T_status[0]);
	this->S_score.setTexture(this->T_score);
	this->S_exit.setTexture(this->T_exit[0]);
	this->S_blockLogo.setPosition(15, 170);
	this->S_status.setPosition(245, 470);
	this->S_score.setPosition(90, 610);
	this->S_logo.setPosition(90, 180);
	this->S_exit.setPosition(315,790);

	this->Text_score.setFont(this->font);
	
	this->Text_score.setCharacterSize(40);
	this->Text_score.setFillColor(Color::Blue);
	this->Text_score.setStyle(sf::Text::Bold);
	this->Text_score.setPosition(120, 660);
}

void EndGame::DRAW()
{
	mouseCheck();
	if (this->hold) this->S_exit.setTexture(this->T_exit[1]);
	else this->S_exit.setTexture(this->T_exit[0]);
	this->window->draw(this->S_bg);
	this->window->draw(this->S_blockLogo);
	this->window->draw(this->S_logo);
	this->window->draw(this->S_score);
	this->window->draw(this->S_status);
	this->window->draw(this->S_exit);
	this->window->draw(this->Text_score);
}

void EndGame::setPointer(string* P, float* F)
{
	this->PName = P;
	this->PScore = F;
	if (*this->PScore == -1)
	{
		this->S_status.setTexture(this->T_status[1]);
		this->Text_score.setString("There is no reward for loser.");
		this->Text_score.setCharacterSize(40);
		this->Text_score.setPosition(120, 660);
	}
	else
	{
		this->Text_score.setString(to_string(int(*this->PScore)));
		this->Text_score.setCharacterSize(60);
		this->Text_score.setPosition(320, 640);
	}
}

void EndGame::mouseCheck()
{
	if (Mouse::getPosition(*this->window).x >= this->S_exit.getPosition().x &&
		Mouse::getPosition(*this->window).x <= this->S_exit.getPosition().x + this->T_exit[0].getSize().x &&
		Mouse::getPosition(*this->window).y >= this->S_exit.getPosition().y &&
		Mouse::getPosition(*this->window).y <= this->S_exit.getPosition().y + this->T_exit[0].getSize().y)
	{
		this->hold = true;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			*this->stateGame = 0;
		}
	}
	else
	{
		this->hold = false;
	}
}
