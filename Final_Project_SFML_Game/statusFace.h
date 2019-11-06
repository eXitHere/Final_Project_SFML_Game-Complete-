#include"initial.h"

#define path_happyp "texture\\items\\happy.png"
#define path_happyd "texture\\items\\sad.png"
#define path_hpup "texture\\items\\hpUp.png"
#define path_hpdown "texture\\items\\hpDown.png"
#define path_moneyp "texture\\items\\moneyP.png"
#define path_moneyd "texture\\items\\moneyD.png"

class statusFace
{
public:
	statusFace(Texture texture, Vector2f pos);
	void DRAW(RenderWindow* window);
	bool getDelete();
private:
	bool Del = false;
	Sprite body;
	Texture texture;
	float totalTime = 0;
	Clock clock;
	float A = 0;
	void move();
};

