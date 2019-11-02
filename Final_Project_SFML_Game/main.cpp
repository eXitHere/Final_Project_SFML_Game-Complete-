#include "initial.h"
#include "Menu.h"

void setupWindow(RenderWindow* window);

int main()
{
	RenderWindow window(VideoMode(SIZE_WIDTH, SIZE_HEIGHT), NAME_GAME);
	Event event;
	setupWindow(&window);
	Menu menu(&window, &event);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();
		if(!menu.isStart()) menu.DRAW();
		window.display();
	}
	return 0;
}

void setupWindow(RenderWindow *window)
{
	window->setFramerateLimit(60);
}