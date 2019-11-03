#include"initial.h"

class EndGame
{
public:
	EndGame(RenderWindow* window, Event* event, int* state);
	void DRAW();
private:
	int* stateGame;
};

