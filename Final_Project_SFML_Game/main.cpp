#include "initial.h"
#include "Menu.h"

void setupWindow(RenderWindow* window);

int main()
{
	RenderWindow window(VideoMode(SIZE_WIDTH, SIZE_HEIGHT), NAME_GAME);
	setupWindow(&window);
	Menu menu;
	Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();
		menu.DRAW(&window);
		window.display();
	}
	return 0;
}

void setupWindow(RenderWindow *window)
{
	window->setFramerateLimit(60);
}