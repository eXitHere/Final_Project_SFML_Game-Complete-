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
	Menu* menu = nullptr; // new Menu(&window, &event, &stateGame);
	InGame* ingame = nullptr;
	EndGame* endgame = new EndGame(&window, &event, &stateGame);
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
			if (menu == nullptr)
			{
				menu = new Menu(&window, &event, &stateGame);
				delete endgame;
			}
			menu->DRAW();
			break;

		case 1: // --> In game
			//cout << "Load In Game " << endl;
			if (ingame == nullptr)
			{
				delete menu;
				ingame = new InGame(&window, &event, &stateGame);
			}
			ingame->DRAW();
			break;

		case 2: // --> End game
			if (endgame == nullptr)
			{
				delete ingame;
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