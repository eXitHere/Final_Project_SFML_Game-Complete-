#include"initial.h"
#define HP 0
#define HAPPY 1
class barManager
{
public:
	barManager(RenderWindow *window,Event *event);
	void DRAW();
	void setup(int* O1, bool* O2, bool* O3, int* D, int* I1, int* I2, int* I3, int* I4, int* I5, int* I6,int map);

private:
	// Function
	void loadTextureAll();
	void updateHpHappy();
	void updateArchive();
	void updateCounter();
	// Variable

	//-> Bar Top
	Texture T_value[7],T_hpHappy,T_grid[2],T_lop;
	Sprite S_value[2], S_hpHappy, S_grid[2],S_lop[2];
	IntRect rect[2];
	int hp_Val = 20;
	int happy_Val = 20;


	//-> Bar Down
	Texture T_object,T_itemCount,T_onLoad,T_Grid[2],T_Archive[4],T_Friend[2],T_Family[2],T_I[9];
	Sprite S_bgObject[3],S_bgItemCount[6],S_onLoad[3],S_Grid[3],S_archiveInobject,S_Friend,S_Family;
	int I_indexArchive = 0;
	bool B_archive[2] = { false,false }, IHide[6], active[3];
	int* pointerCount[6];
	int map;
	Font font;
	Text countItem[6];
	//->
	RenderWindow* window;
	Event* event;
};

