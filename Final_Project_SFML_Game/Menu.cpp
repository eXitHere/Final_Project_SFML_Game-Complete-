#include "Menu.h"

Menu::Menu()
{
	loadScore();
	this->T_bg.loadFromFile("Texture/Menu/bg_main-01.jpg");
	this->S_bg.setTexture(this->T_bg);

	this->T_hima.loadFromFile("Texture/Menu/hima.png");
	this->S_hima.setTexture(this->T_hima);
	this->T_hima.setRepeated(true);
	this->R_hima = IntRect(0, 0, 1600, 20000);
	this->S_hima.setPosition(0, -20000);
	this->S_hima.setTextureRect(this->R_hima);

	this->T_btnStart.loadFromFile("Texture/Menu/startBTN-01.png");
	this->S_btnStart.setTexture(this->T_btnStart);
	this->S_btnStart.setOrigin(this->T_btnStart.getSize().x / 2, this->T_btnStart.getSize().y / 2);
	this->S_btnStart.setPosition(800, 750);

	this->T_focus.loadFromFile("Texture/Menu/focus.png");
	this->S_focus.setTexture(this->T_focus);
	this->S_focus.setOrigin(this->T_focus.getSize().x / 2, this->T_focus.getSize().y / 2);
	this->S_focus.setPosition(800, 660);

	this->T_score.loadFromFile("Texture/Menu/bg_score.png");
	this->S_score.setTexture(this->T_score);
	this->S_score.setOrigin(this->T_score.getSize().y / 2, 0);
	this->S_score.setPosition(1200, 0);
	this->R_score = IntRect(0, 0, this->T_score.getSize().x, 0);
	this->S_score.setTextureRect(this->R_score);
	font.loadFromFile("font/Cloud-Bold.otf");
	for (int i = 0; i < 5; i++)
	{
		text_score[i].setFont(font);
		text_score[i].setString("THANA 123456789");
		text_score[i].setCharacterSize(40);
		text_score[i].setFillColor(Color::Magenta);
		text_score[i].setStyle(sf::Text::Bold);
		text_score[i].setPosition(1090, 75*i+150); // name_Show
	}
}

void Menu::DRAW(RenderWindow* window)
{
	this->window = window;
	checkMouse();
	moveHima();
	window->draw(this->S_bg);
	window->draw(this->S_hima);
	window->draw(this->S_btnStart);
	if (this->B_focus)
	{
		window->draw(this->S_focus);
		focused();
	}
	window->draw(this->S_score);
	scoreShow();
}

void Menu::checkMouse()
{
	if (Mouse::getPosition(*window).x >= this->S_btnStart.getPosition().x - this->T_btnStart.getSize().x / 2 +70 &&
		Mouse::getPosition(*window).y >= this->S_btnStart.getPosition().y - this->T_btnStart.getSize().y / 2 +15 &&
		Mouse::getPosition(*window).x <= this->S_btnStart.getPosition().x + this->T_btnStart.getSize().x / 2 -70 &&
		Mouse::getPosition(*window).y <= this->S_btnStart.getPosition().y + this->T_btnStart.getSize().y / 2 -15)
	{
		B_focus = true;
	}
	else
	{
		B_focus = false;
	}
}

void Menu::moveHima()
{
	this->S_hima.move(0, 0.5);
	if (this->S_hima.getPosition().y > 1600)
	{
		this->S_hima.setPosition(0, -20000);
	}
	//cout << this->S_hima.getPosition().y << endl;
}

void Menu::focused()
{
	if (this->B_focus)
	{
		this->totalTime += clock.restart().asSeconds();
		if (this->totalTime >= 0.1)
		{
			if (this->B_swap)
			{
				this->S_focus.move(-2, sin(this->A));
				this->S_btnStart.move(sin(this->A), 0);
			}
			else if (!this->B_swap)
			{
				this->S_focus.move(2, sin(this->A));
				this->S_btnStart.move(sin(this->A), 0);
			}
			if (this->S_focus.getPosition().x > 1000) this->B_swap = true;
			if (this->S_focus.getPosition().x < 600) this->B_swap = false;
			this->A -= 0.1;
		}
	}
}

void Menu::scoreShow()
{
	switch (this->stateScore)
	{
		//show board only
	case 1: 
		this->R_score.height += 2;
		this->S_score.setTextureRect(this->R_score);
		if (this->R_score.height > this->T_score.getSize().y)
		{
			this->stateScore = 2;
			cout << "Load board complete!" << endl;
		}
		break;
		//slid text
	case 2:
		//if() cout << 'A' + rand() % ('Z' - 'A') << endl;
		for (int i = 0; i < 5; i++)
		{
			if (this->indexSlid < this->string_score[i].length())  this->string_Score_slid[i][this->indexSlid] = '#';
		}
		
		this->totalTimeScore += clock_score.restart().asSeconds();
		if (this->totalTimeScore >=0.1)
		{
			this->totalTimeScore = 0;
			for (int i = 0; i < 5; i++)
			{
				if(this->indexSlid<this->string_score[i].length()) this->string_Score_slid[i][this->indexSlid] = this->string_score[i][this->indexSlid];
			}
			this->indexSlid++;
			
		}
		if(this->indexSlid>this->string_score[0].length()&&
			this->indexSlid>this->string_score[1].length()&&
			this->indexSlid>this->string_score[2].length()&&
			this->indexSlid>this->string_score[3].length()&&
			this->indexSlid>this->string_score[4].length())
			{
			this->stateScore = 3;
			}
		//if (temp1) cout << "BREAK!!!!!!!" << endl;
		for (int i = 0; i < 5; i++) // show!!
		{
			this->text_score[i].setString(this->string_Score_slid[i]);
			window->draw(this->text_score[i]);
			//cout << "draw!!" << endl;
		}
		break;
		//complete!!
	case 3:
		for (int i = 0; i < 5; i++) // show!!
		{
			window->draw(this->text_score[i]);
			//cout << "draw!!" << endl;
		}
		this->totalTimeScore += clock_score.restart().asSeconds();
		if (this->totalTimeScore > 3)
		{
			this->totalTimeScore = 0;
			this->stateScore = 4;
			cout << this->indexSlid << endl;
		}
		break;
		//hide name
	case 4:
		this->totalTimeScore += clock_score.restart().asSeconds();
		if (this->totalTimeScore > 0.1)
		{
			this->totalTimeScore = 0;
			for (int i = 0; i < 5; i++)
			{
				this->string_Score_slid[i][this->indexSlid + 1] = ' ';
				this->string_Score_slid[i][this->indexSlid] = '#';
				this->text_score[i].setString(this->string_Score_slid[i]);
			}
			this->indexSlid--;
		}
		for (int i = 0; i < 5; i++)
		{
			window->draw(this->text_score[i]);
		}
		if (this->indexSlid == -1)
		{
			this->indexSlid = 0;
			this->stateScore = 5;
		}
		//hide scoreboard
	case 5:
		this->totalTimeScore += this->clock_score.restart().asSeconds();
		if (this->totalTimeScore > 0.5)
		{
			this->R_score.height -= 2;
			this->S_score.setTextureRect(this->R_score);
			if (this->R_score.height < 0)
			{
				this->totalTimeScore = 0;
				this->stateScore = 0;
				cout << "unload board complete!" << endl;
			}
		}
		break;
		// Hide!
	case 0:
		this->totalTimeScore += this->clock_score.restart().asSeconds();
		if (this->totalTimeScore > 3)
		{
			this->totalTimeScore = 0;
			this->stateScore = 1;
		}
		break;
	}
}

void Menu::loadScore()
{
	this->myFile.open("database/score.txt");
	string temp;
	int tempIndex = 0;
	while (!this->myFile.eof())
	{
		getline(this->myFile, temp);
		this->string_score[tempIndex++] = temp;
	}
	this->myFile.close();
}


