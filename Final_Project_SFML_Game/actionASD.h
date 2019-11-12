#pragma once
#include"initial.h"

class actionASD
{
public:
	actionASD();
	void setAction(int index);
	void draw(RenderWindow *window);

private:
	void reset();
	void update();

	bool B_stop = true;
	int indexAction = 0;
	Texture T_texture[6];
	Sprite body;
	double deltaTime = 0;
	Clock clock;
	int X = 0;
	IntRect rect;
};

