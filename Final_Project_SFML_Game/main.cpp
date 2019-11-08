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

	int stateGame = 0;
	Menu* menu = NULL; // new Menu(&window, &event, &stateGame);
	InGame* ingame = NULL;
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
				//cout << "Create Menu !" << endl;
				menu = new Menu(&window, &event, &stateGame);
				delete endgame;
				endgame = nullptr;
			}
			menu->DRAW();
			break;
			
		case 1: // --> In game
			//cout << "Load In Game " << endl;
			if (!ingame)
			{
				delete menu;
				menu = nullptr;
				ingame = new InGame(&window, &event, &stateGame);
			}
			ingame->DRAW();
			break;

		case 2: // --> End game
			if (!endgame)
			{
				delete ingame;
				ingame = nullptr;
				endgame = new EndGame(&window, &event, &stateGame);
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
	window->setFramerateLimit(60);
}