#include"initial.h"
#include<fstream>

class Menu
{
public:
	Menu();
	void DRAW(RenderWindow* window);
private:
	void checkMouse();
	void moveHima();
	void focused();
	void scoreShow();
	void loadScore();
	void loadSetting();
	fstream myFile;
	bool B_focus = false, B_swap = false,B_mouse=false;
	Clock clock,clock_score;
	float totalTime = 0, totalTimeScore = 0 , A = 100000,B=0;
	Text text_score[5];
	string string_score[5] = {"                    ","                    " ,"                    " ,"                    " ,"                    "}, string_Score_slid[5] = { "                    ","                    " ,"                    " ,"                    " ,"                    " };
	int stateScore = 1, indexSlid = 0,stateSetting=0;
	Font font;
	Texture T_bg,T_hima,T_btnStart,T_focus,T_score,T_setting[2],T_boardSetting;
	Sprite S_bg,S_hima,S_btnStart,S_focus,S_score,S_setting,S_boardSetting;
	IntRect R_hima,R_score;
	RenderWindow* window;
};