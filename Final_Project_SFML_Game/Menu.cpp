#include "Menu.h"

Menu::Menu(RenderWindow* window, Event* event)
{
	this->window = window;
	this->event = event;
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
		this->text_score[i].setFont(font);
		this->text_score[i].setString("THANA 123456789");
		this->text_score[i].setCharacterSize(40);
		this->text_score[i].setFillColor(Color::Blue);
		this->text_score[i].setStyle(sf::Text::Bold);
		this->text_score[i].setPosition(1090, 75*i+150); // name_Show
	}

	this->T_setting[0].loadFromFile("Texture/Menu/setting.png");
	this->T_setting[1].loadFromFile("Texture/Menu/setting_hold.png");
	this->S_setting.setTexture(this->T_setting[0]);
	this->S_setting.setOrigin(this->T_setting[0].getSize().x / 2, this->T_setting[0].getSize().y / 2);
	this->S_setting.setPosition(1560, 860);

	this->T_boardSetting.loadFromFile("Texture/Menu/boardSetting.png");
	this->S_boardSetting.setTexture(this->T_boardSetting);
	this->S_boardSetting.setOrigin(this->T_boardSetting.getSize().x / 2, 0);
	//this->S_boardSetting.setPosition(1320, 700);
	this->S_boardSetting.setPosition(1320, 900);

	this->T_soundBar[0].loadFromFile("Texture/Menu/soundBar.png");
	this->T_soundBar[1].loadFromFile("Texture/Menu/soundBarHold.png");
	this->T_soundBtn.loadFromFile("Texture/Menu/btnBar.png");
	this->S_soundBar[0].setTexture(this->T_soundBar[0]);
	this->S_soundBar[1].setTexture(this->T_soundBar[1]);
	this->S_soundBar[2].setTexture(this->T_soundBar[0]);
	this->S_soundBar[3].setTexture(this->T_soundBar[1]);
	this->S_soundBtn[0].setTexture(this->T_soundBtn);
	this->S_soundBtn[1].setTexture(this->T_soundBtn);
	/*this->S_soundBar[0].setPosition(1100, 765);
	this->S_soundBar[1].setPosition(1100, 765);
	this->S_soundBar[2].setPosition(1100, 835);
	this->S_soundBar[3].setPosition(1100, 835);*/
	this->S_soundBar[0].setPosition(1100, 965);
	this->S_soundBar[1].setPosition(1100, 965);
	this->S_soundBar[2].setPosition(1100, 1035);
	this->S_soundBar[3].setPosition(1100, 1035);
	this->S_soundBtn[0].setOrigin(this->T_soundBtn.getSize().x / 2, this->T_soundBtn.getSize().y / 2);
	this->S_soundBtn[0].setPosition(float(this->valMusic * this->T_soundBar[0].getSize().x /100) + 1100, 979);
	this->S_soundBtn[1].setOrigin(this->T_soundBtn.getSize().x / 2, this->T_soundBtn.getSize().y / 2);
	this->S_soundBtn[1].setPosition(float(this->valEffect * this->T_soundBar[0].getSize().x / 100)  + 1100, 1049);
	this->R_soundBar[0] = IntRect(0, 0, float(this->valMusic * this->T_soundBar[0].getSize().x / 100) ,this->T_soundBar[0].getSize().y);
	this->R_soundBar[1] = IntRect(0, 0, float(this->valEffect * this->T_soundBar[0].getSize().x / 100), this->T_soundBar[0].getSize().y);
	this->S_soundBar[1].setTextureRect(this->R_soundBar[0]);
	this->S_soundBar[3].setTextureRect(this->R_soundBar[1]);
	this->text_valMusic.setFont(font);
	this->text_valMusic.setString(to_string(this->valMusic));
	this->text_valMusic.setCharacterSize(21);
	this->text_valMusic.setFillColor(Color::Blue);
	this->text_valMusic.setStyle(sf::Text::Bold);
	this->text_valMusic.setPosition(1462, 963);
	this->text_ValEffect.setFont(font);
	this->text_ValEffect.setString(to_string(this->valEffect));
	this->text_ValEffect.setCharacterSize(21);
	this->text_ValEffect.setFillColor(Color::Blue);
	this->text_ValEffect.setStyle(sf::Text::Bold);
	this->text_ValEffect.setPosition(1462, 1033);

	this->T_myName.loadFromFile("Texture/Menu/myname.png");
	this->S_myName.setTexture(this->T_myName);

	this->text_showTitle.setFont(font);
	this->text_showTitle.setCharacterSize(25);
	this->text_showTitle.setFillColor(Color::Blue);
	//this->text_GetName.setStyle(sf::Text::Bold);
	this->text_showTitle.setPosition(580, 680);
	this->text_showTitle.setString("Enter your name | Press enter to start");

	this->text_GetName.setFont(font);
	this->text_GetName.setCharacterSize(40);
	this->text_GetName.setFillColor(Color::Black);
	//this->text_GetName.setStyle(sf::Text::Bold);
	this->text_GetName.setPosition(690, 725);
	this->text_GetName.setString("");

	this->rectangle_GetName.setSize(Vector2f(300.0f, 60.0f));
	this->rectangle_GetName.setPosition(800, 750);
	this->rectangle_GetName.setFillColor(Color::White);
	this->rectangle_GetName.setOutlineThickness(3);
	this->rectangle_GetName.setOutlineColor(Color::Red);
	this->rectangle_GetName.setOrigin(Vector2f(150.0f, 30.0f));
	this->rectangle_focus.setSize(Vector2f(3.0f, 44.0f));
	this->rectangle_focus.setPosition(695, 750);
	this->rectangle_focus.setFillColor(Color::Black);
	this->rectangle_focus.setOrigin(Vector2f(1.5f, 22.0f));
}

void Menu::DRAW()
{
	checkMouse();
	moveHima();
	window->draw(this->S_bg);
	moveMyname();
	window->draw(this->S_score);
	scoreShow();
	window->draw(this->S_hima);
	if(!this->B_enterStart) window->draw(this->S_btnStart);
	else enterName();
	if (this->B_focus)
	{
		window->draw(this->S_focus);
		focused();
	}
	loadSetting();
	window->draw(this->S_setting);	
}

bool Menu::isStart()
{
	return this->stateEnterName == 2;
}

void Menu::checkMouse()
{
	// btn start
	if (Mouse::getPosition(*window).x >= this->S_btnStart.getPosition().x - this->T_btnStart.getSize().x / 2 + 70 &&
		Mouse::getPosition(*window).y >= this->S_btnStart.getPosition().y - this->T_btnStart.getSize().y / 2 + 15 &&
		Mouse::getPosition(*window).x <= this->S_btnStart.getPosition().x + this->T_btnStart.getSize().x / 2 - 70 &&
		Mouse::getPosition(*window).y <= this->S_btnStart.getPosition().y + this->T_btnStart.getSize().y / 2 - 15)
	{
		this->B_focus = true;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!this->B_enterStart)
			{
				this->B_enterStart = true;
				this->stateEnterName = 1;
			}
		}
	}
	else
	{
		this->B_focus = false;
	}

	// btn setting
	if (Mouse::getPosition(*window).x >= this->S_setting.getPosition().x - this->T_setting[0].getSize().x / 2 &&
		Mouse::getPosition(*window).y >= this->S_setting.getPosition().y - this->T_setting[0].getSize().y / 2 &&
		Mouse::getPosition(*window).x <= this->S_setting.getPosition().x + this->T_setting[0].getSize().x / 2 &&
		Mouse::getPosition(*window).y <= this->S_setting.getPosition().y + this->T_setting[0].getSize().y / 2)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->B_mouse == false)
			{
				//	cout << "Click!" << endl;	
				this->B_mouse = true;
				if (this->stateSetting == 0 || this->stateSetting == 3)
				{
					this->stateSetting = 1;
					this->B = 0;
				}
				else if (this->stateSetting == 1 || this->stateSetting == 2)
				{
					this->stateSetting = 3;
					this->B = 0;
				}
				//	cout << this->stateSetting << endl;
			}
		}
		else
		{
			this->B_mouse = false;
		}
		//this->B_setting = true;
		//cout << this->B << endl;
	}
	else
	{
		//this->B_setting = false;
		this->S_setting.setTexture(this->T_setting[0]);
		//this->B = 0;
	}

	// btn soundbar
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (Mouse::getPosition(*window).x >= this->S_soundBtn[0].getPosition().x - this->T_soundBtn.getSize().x / 2 &&
			Mouse::getPosition(*window).y >= this->S_soundBtn[0].getPosition().y - this->T_soundBtn.getSize().y / 2 &&
			Mouse::getPosition(*window).x <= this->S_soundBtn[0].getPosition().x + this->T_soundBtn.getSize().x / 2 &&
			Mouse::getPosition(*window).y <= this->S_soundBtn[0].getPosition().y + this->T_soundBtn.getSize().y / 2)
		{
			if (this->B_mouse == false)
			{
				//	cout << "Click!" << endl;
				this->B_Holdon[0] = true;
				this->B_mouse = true;
				//cout << "Click!!!!!" << endl;
			}
		}
		if (this->B_Holdon[0])
		{
		//	cout << "HOLD!!" << endl;
			moveBTNsoundBar(0);
		}
	}
	else
	{
		this->B_mouse = false;
		this->B_Holdon[0] = false;
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (Mouse::getPosition(*window).x >= this->S_soundBtn[1].getPosition().x - this->T_soundBtn.getSize().x / 2 &&
			Mouse::getPosition(*window).y >= this->S_soundBtn[1].getPosition().y - this->T_soundBtn.getSize().y / 2 &&
			Mouse::getPosition(*window).x <= this->S_soundBtn[1].getPosition().x + this->T_soundBtn.getSize().x / 2 &&
			Mouse::getPosition(*window).y <= this->S_soundBtn[1].getPosition().y + this->T_soundBtn.getSize().y / 2)
		{

			if (this->B_mouse == false)
			{
					//	cout << "Click!" << endl;	
				this->B_mouse = true;
				this->B_Holdon[1] = true;

			}
		}
		if (this->B_Holdon[1])
		{
			moveBTNsoundBar(1);
		}
	}
	else
	{
		this->B_mouse = false;
		this->B_Holdon[1] = false;
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
			if (this->indexSlid < this->string_score[i].length())  this->string_Score_slid[i][this->indexSlid] = '_';
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
			this->indexSlid -= 2;
			//cout << this->indexSlid << endl;
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
				this->string_Score_slid[i][this->indexSlid] = '_';
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

void Menu::loadSetting()
{
	switch (this->stateSetting)
	{
	case 0:
		break;
	case 1:
		this->S_setting.setTexture(this->T_setting[1]);
		this->S_setting.rotate(-this->B);
		this->B += 0.01;
		this->S_boardSetting.move(0, -this->B);
		for (int i = 0; i < 4; i++) this->S_soundBar[i].move(0, -this->B);
		this->S_soundBtn[0].move(0, -this->B);
		this->S_soundBtn[1].move(0, -this->B);
		this->text_valMusic.move(0, -this->B);
		this->text_ValEffect.move(0, -this->B);
		this->S_soundBar[1].setTextureRect(this->R_soundBar[0]);
		this->S_soundBar[3].setTextureRect(this->R_soundBar[1]);
		window->draw(this->S_boardSetting);
		window->draw(this->S_soundBar[0]);
		window->draw(this->S_soundBar[1]);
		window->draw(this->S_soundBar[2]);
		window->draw(this->S_soundBar[3]);
		window->draw(this->S_soundBtn[0]);
		window->draw(this->S_soundBtn[1]);
		window->draw(this->text_valMusic);
		window->draw(this->text_ValEffect);
		if (this->S_boardSetting.getPosition().y <= 700)
		{
			this->stateSetting = 2;
		}
		break;
	case 2:
		this->S_soundBar[1].setTextureRect(this->R_soundBar[0]);
		this->S_soundBar[3].setTextureRect(this->R_soundBar[1]);
		window->draw(this->S_boardSetting);
		window->draw(this->S_soundBar[0]);
		window->draw(this->S_soundBar[1]);
		window->draw(this->S_soundBar[2]);
		window->draw(this->S_soundBar[3]);
		window->draw(this->S_soundBtn[0]);
		window->draw(this->S_soundBtn[1]);
		window->draw(this->text_valMusic);
		window->draw(this->text_ValEffect);
		break;
	case 3:
		this->S_setting.setTexture(this->T_setting[1]);
		this->S_setting.rotate(this->B);
		this->B += 0.01;
		this->S_boardSetting.move(0, this->B);
		for (int i = 0; i < 4; i++) this->S_soundBar[i].move(0, this->B);
		this->S_soundBtn[0].move(0, this->B);
		this->S_soundBtn[1].move(0, this->B);
		this->text_ValEffect.move(0, this->B);
		this->text_valMusic.move(0, this->B);
		this->S_soundBar[1].setTextureRect(this->R_soundBar[0]);
		this->S_soundBar[3].setTextureRect(this->R_soundBar[1]);
		window->draw(this->S_boardSetting);
		window->draw(this->S_soundBar[0]);
		window->draw(this->S_soundBar[1]);
		window->draw(this->S_soundBar[2]);
		window->draw(this->S_soundBar[3]);
		window->draw(this->S_soundBtn[0]);
		window->draw(this->S_soundBtn[1]);
		window->draw(this->text_valMusic);
		window->draw(this->text_ValEffect);
		if (this->S_boardSetting.getPosition().y >= 900)
		{
			this->stateSetting = 0;
		}
		break;
	}
}

void Menu::moveBTNsoundBar(int index)
{
	if (index ==0 && this->S_soundBtn[0].getPosition().x >= 1100 && this->S_soundBtn[0].getPosition().x <= this->T_soundBar[0].getSize().x + 1100)
	{
		this->valMusic = float((this->S_soundBtn[0].getPosition().x - 1100.0f) / this->T_soundBar[0].getSize().x)*100;
		this->R_soundBar[0].width = float(this->valMusic)/ 100 * this->T_soundBar[0].getSize().x;
		this->S_soundBar[1].setTextureRect(this->R_soundBar[0]);
		this->text_valMusic.setString(to_string(this->valMusic));
		//cout << (this->S_soundBtn[0].getPosition().x - 1100) << " -- " << this->T_soundBtn.getSize().x << endl;
		//cout << this->valMusic << endl;
		this->S_soundBtn[0].setPosition(Mouse::getPosition(*window).x, this->S_soundBtn[0].getPosition().y);
		if (this->S_soundBtn[0].getPosition().x < 1100) this->S_soundBtn[0].setPosition(1100, this->S_soundBtn[0].getPosition().y);
		if (this->S_soundBtn[0].getPosition().x > this->T_soundBar[0].getSize().x + 1100) this->S_soundBtn[0].setPosition(this->T_soundBar[0].getSize().x + 1100, this->S_soundBtn[0].getPosition().y);
	}
	else if (index == 1 && this->S_soundBtn[1].getPosition().x >= 1100 && this->S_soundBtn[1].getPosition().x <= this->T_soundBar[0].getSize().x + 1100)
	{
		this->valEffect = float((this->S_soundBtn[1].getPosition().x - 1100.0f) / this->T_soundBar[0].getSize().x) * 100;
		this->text_ValEffect.setString(to_string(this->valEffect));
		this->R_soundBar[1].width = float(this->valEffect) / 100 * this->T_soundBar[0].getSize().x;
		this->S_soundBar[3].setTextureRect(this->R_soundBar[1]);
		this->S_soundBtn[1].setPosition(Mouse::getPosition(*window).x, this->S_soundBtn[1].getPosition().y);
		if (this->S_soundBtn[1].getPosition().x < 1100) this->S_soundBtn[1].setPosition(1100, this->S_soundBtn[1].getPosition().y);
		if (this->S_soundBtn[1].getPosition().x > this->T_soundBar[0].getSize().x + 1100) this->S_soundBtn[1].setPosition(this->T_soundBar[0].getSize().x + 1100, this->S_soundBtn[1].getPosition().y);
	}
}

void Menu::moveMyname()
{
	switch (this->stateMyName)
	{
	case 0:
		this->totalTimeMyName += this->clock_myname.restart().asSeconds();
		//cout << this->totalTimeMyName << endl;
		if (this->totalTimeMyName >=15)
		{
			this->totalTimeMyName = 0;
			srand(time(NULL));
			this->stateMyName = rand()%2+1; // 1 LEFT ---- 2 RIGHT
			if (this->stateMyName == 1)
			{
				//cout << "Set 1" << endl;
				this->S_myName.setPosition(-100, rand() % 100 + 30);
				this->S_myName.setScale(-1.0f, 1.0f);
			}
			else if(this->stateMyName == 2)
			{
				//cout << "Set 2" << endl;
				this->S_myName.setPosition(1700, rand() % 100 + 30);
				this->S_myName.setScale(1.0f, 1.0f);
			}
			this->C = rand()%10;
		}
		break;

	case 1: 
		//cout << "Do case 1" << endl;
		this->S_myName.move(this->C, sin(this->C));
		this->C += 0.01;
		window->draw(this->S_myName);
		if (this->S_myName.getPosition().x > this->T_myName.getSize().x + 1600)
		{
			//cout << "Reset" << endl;
			this->stateMyName = 0;
			this->totalTimeMyName = 0;
		}
		break;
	case 2:
		//cout << "Do case 2" << endl;
		this->S_myName.move(-this->C, sin(this->C));
		this->C += 0.01;
		window->draw(this->S_myName);
		if (this->S_myName.getPosition().x < (-((float)this->T_myName.getSize().x)))
		{
			//cout << "Reset" << endl;
			this->stateMyName = 0;
			this->totalTimeMyName = 0;
		}
		break;
	}
}

void Menu::enterName()
{
	switch (this->stateEnterName)
	{
	case 0:// unload
		break;
	case 1:
			//cout << "Press!" << endl;
		if (this->event->type == Event::EventType::KeyReleased && this->last_Char != ' ')
		{
			this->last_Char = ' ';
			//cout << "Clear" << endl;
		}
		if (this->event->type == Event::TextEntered && this->last_Char != this->event->text.unicode)
		{
			//cout << event->text.unicode << endl;
			//cout << this->event->text.unicode << endl;
			if (this->event->text.unicode == 13 && this->indexGetName !=0) // enter
			{
				this->stateEnterName = 2;
			}
			else if (this->event->text.unicode == 27)
			{
				this->stateEnterName = 0;
				this->B_enterStart = false;
				this->string_GetName.clear();
				this->text_GetName.setString(this->string_GetName);
				this->rectangle_focus.setPosition(690 + this->text_GetName.getGlobalBounds().width + 5, 750);
				this->indexGetName = 0;
				this->last_Char = ' ';
			}
			else if (this->event->text.unicode == 8) // delete
			{
				this->last_Char = this->event->text.unicode;
				this->string_GetName.erase(this->indexGetName);
				this->text_GetName.setString(this->string_GetName);
				//cout << this->string_GetName << endl;
				this->rectangle_focus.setPosition(690 + this->text_GetName.getGlobalBounds().width+5, 750);
				if (this->indexGetName > 0) this->indexGetName--;
			}
			else if (this->indexGetName < 10 && this->event->text.unicode != 8 &&(
					(this->event->text.unicode >= 'a' && this->event->text.unicode <='z') ||
					(this->event->text.unicode >= 'A' && this->event->text.unicode <='Z') ||
					(this->event->text.unicode >= '0' && this->event->text.unicode <= '9'))
				)
			{
				this->last_Char = this->event->text.unicode;
				this->string_GetName+= this->last_Char;
				this->text_GetName.setString(this->string_GetName);
				this->indexGetName++;
				this->rectangle_focus.setPosition(690+this->text_GetName.getGlobalBounds().width+5, 750);
				//this->rectangle_focus.setPosition(695 + this->indexGetName * 21, 750);
			}
			//cout << string_GetName << endl;
		}
		
		this->totalTimeEnterName += this->clock_EnterName.restart().asSeconds();
		window->draw(this->rectangle_GetName);
		if (this->totalTimeEnterName > 0.5)
		{
			this->B_enterName = !this->B_enterName;
			this->totalTimeEnterName = 0;
		}
		if (this->B_enterName) window->draw(this->rectangle_focus);
		window->draw(this->text_showTitle);
		if (this->indexGetName >= 0)
		{
			window->draw(this->text_GetName);
		}
		break;
	}
}
