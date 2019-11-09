#include"initial.h"

class NPC
{
public:
	NPC();
	void setDATA(Texture texture,int positionX,float *yPos, int ID, RenderWindow* window, Event* event);
	void DRAW();
	void Move();
	int getID();
	int checkState();
	bool isSpacial();
	Vector2f getPostiosion();
	void setPosition(Vector2f pos);

private:
	bool spacial = false;
	void move();
	void update();
	void checkOnHold();
	void updatePress();

	int ID;
	int delme = 0;

	Sprite press;
	Texture Tpess;
	float totalTimePress = 0;
	int XNOW = 0;
	IntRect RECT;
	Clock clockPress;

	Sprite body;
	Texture texture;
	IntRect rect;
	float totalTime = 0;
	Clock clock;
	int xNow = 0;
	float* yPosPlayer;
	//->
	RenderWindow* window;
	Event* event;
};

