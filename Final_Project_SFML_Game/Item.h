#include"initial.h"

class Item
{
public:
	Item();
	~Item() { cout << "delete ‘item' complete" << endl; };
	void loadData(Texture texture,int ID, RenderWindow* window,Vector2f position);
	void DRAW();
	bool deleteMe();
	Vector2f getHalfsize();
	Vector2f getPosition();
	int getID();

private:
	// function
	void update();
	void move();

	int ID;
	float A = 2000;
	int X = 0;
	Texture texture;
	Sprite body;
	IntRect rect;
	Clock clock;
	float totalTime = 0.0f;
	
	RenderWindow* window;
};

