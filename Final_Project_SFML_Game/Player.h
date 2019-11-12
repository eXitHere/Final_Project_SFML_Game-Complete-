#ifndef HEADER_H_
#define HEADER_H_
#include "soundPlayBack.h"
#include "actionASD.h"
#endif

#include"initial.h"
#define P_COUNT 5
class Player
{
public:
	Player(RenderWindow* window, Event* event, bool* pause, soundPlayBack* soundManage);
	void updateRec(int newRec);
	void DRAW();
	void setPointerToY(float* Y);
	Vector2f getHalfsize();
	Vector2f getPosition();
private:
	soundPlayBack* soundManage;
	bool* pause;
	float *pointerToY;
	void controls();
	void update();
	void jump();
	bool canJump();
	int stateJump = 0;
	float jumpPower = 20;
	int action_now=0;

	Texture T_texture[P_COUNT];
	Sprite body;

	IntRect rec;
	double totalTime = 0;
	Clock clock;
	int X_now = 0;
	int countPic[P_COUNT] = { 4,4,6,4,6 };
	float baseHeight[2] = { 600,500 };


	//->
	RenderWindow* window;
	Event* event;
};

