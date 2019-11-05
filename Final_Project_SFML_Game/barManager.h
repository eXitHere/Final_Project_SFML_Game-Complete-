#include"initial.h"
#define HP 0
#define HAPPY 1
class barManager
{
public:
	barManager(RenderWindow *window,Event *event);
	void DRAW();

private:
	// Function
	void loadTextureAll();
	void updateHpHappy();

	// Variable
	Texture T_value[7],T_hpHappy,T_grid[2];
	Sprite S_value[2], S_hpHappy, S_grid[2];
	IntRect rect[2];
	int hp_Val = 60;
	int happy_Val = 60;

	//->
	RenderWindow* window;
	Event* event;
};

