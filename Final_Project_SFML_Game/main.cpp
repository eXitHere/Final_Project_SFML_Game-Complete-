#ifndef HEADER_H_
#define HEADER_H_
#include "soundPlayBack.h"
#endif

#include "initial.h"
#include "Menu.h"
#include "InGame.h"
#include "EndGame.h"



void setupWindow(RenderWindow* window);
	
int main()
{
	RenderWindow window(VideoMode(SIZE_WIDTH, SIZE_HEIGHT), NAME_GAME);
	Event event;
	setupWindow(&window);
	soundPlayBack soundManage;

	string playerName;
	float scoreMain;
	int stateGame = 0;
	Menu* menu = nullptr; // new Menu(&window, &event, &stateGame);
	InGame* ingame = nullptr;
	EndGame* endgame = new EndGame(&window, &event, &stateGame);
	delete menu;
	delete ingame;
	
	bool B_deleteLastState = false;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();
		switch (stateGame)
		{		
		case 0:  // --> Menu
			//cout << "Load Menu" << endl;
			if (!menu)
			{		
				soundManage.restartMusicBackground();
				//cout << "Create Menu !" << endl;
				menu = new Menu(&window, &event, &stateGame,&soundManage);
				menu->setPointerName(&playerName);
				delete endgame;
				endgame = nullptr;
			}
			menu->DRAW();
			break;
			
		case 1: // --> In game
			//cout << "Load In Game " << endl;
			if (!ingame)
			{
				soundManage.restartMusicBackground();
				delete menu;
				menu = nullptr;
				ingame = new InGame(&window, &event, &stateGame, &soundManage);
				ingame->setPointScore(&scoreMain);
			}
			ingame->DRAW();
			break;

		case 2: // --> End game
			if (!endgame)
			{
				delete ingame;
				ingame = nullptr;
				endgame = new EndGame(&window, &event, &stateGame);
				endgame->setPointer(&playerName, &scoreMain);
			}
			endgame->DRAW();
			break;
		}
		window.display();
	}
	return 0;
}

void setupWindow(RenderWindow *window)
{
	window->setFramerateLimit(120);
}