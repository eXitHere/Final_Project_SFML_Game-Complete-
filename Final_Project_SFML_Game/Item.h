#include"initial.h"

class Item
{
public:
	Item();
	void loadData(Texture texture, RenderWindow* window,Vector2f position);
	void DRAW();
	bool deleteMe();
private:
	// function
	void update();
	void move();

	float A = 2000;
	int X = 0;
	Texture texture;
	Sprite body;
	IntRect rect;
	Clock clock;
	float totalTime = 0.0f;
	
	RenderWindow* window;
};

