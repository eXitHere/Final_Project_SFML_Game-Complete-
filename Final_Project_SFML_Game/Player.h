#include"initial.h"
#define P_COUNT 5
class Player
{
public:
	Player(RenderWindow *window,Event *event);
	void updateRec(int newRec);
	void DRAW();
	void setPointerToY(float* Y);
	Vector2f getHalfsize();
	Vector2f getPosition();
private:
	float *pointerToY;
	void controls();
	void update();
	void jump();
	bool canJump();
	int stateJump = 0;
	float jumpPower = 15;
	int action_now=0;

	Texture T_texture[P_COUNT];
	Sprite body;

	IntRect rec;
	double totalTime = 0;
	Clock clock;
	int X_now = 0;
	int countPic[P_COUNT] = { 4,4,6,4,6 };
	float baseHeight[2] = { 600,450 };


	//->
	RenderWindow* window;
	Event* event;
};

