#include"initial.h"
#include<fstream>
#include<stdlib.h>
#include<time.h>

class Menu
{
public:
	Menu(RenderWindow* window, Event* event,int *state);
	void DRAW();
private:
	void checkMouse();
	void moveHima();
	void focused();
	void scoreShow();
	void loadScore();
	void loadSetting();
	void moveBTNsoundBar(int index);
	void moveMyname();
	void enterName();
	fstream myFile;
	bool B_focus = false, B_swap = false, B_mouse = false, B_Holdon[2] = { false,false }, B_enterStart = false, B_enterName = false;
	char last_Char = ' ';
	Clock clock,clock_score,clock_myname,clock_EnterName;
	float totalTime = 0, totalTimeScore = 0, A = 100000, B = 0, totalTimeMyName = 0, C = 0, totalTimeEnterName = 0;
	Text text_score[5],text_valMusic,text_ValEffect,text_GetName, text_showTitle;
	RectangleShape rectangle_GetName,rectangle_focus;
	string string_score[5] = {"                    ","                    " ,"                    " ,"                    " ,"                    "}, string_Score_slid[5] = { "                    ","                    " ,"                    " ,"                    " ,"                    " };
	string string_GetName;
	int stateScore = 1, indexSlid = 0, stateSetting = 0, valMusic = 50, valEffect = 50, stateMyName = 0,stateEnterName =0,indexGetName=0;
	Font font;
	Texture T_bg,T_hima,T_btnStart,T_focus,T_score,T_setting[2],T_boardSetting,T_soundBar[2],T_soundBtn,T_myName;
	Sprite S_bg,S_hima,S_btnStart,S_focus,S_score,S_setting,S_boardSetting,S_soundBar[4],S_soundBtn[2],S_myName;
	IntRect R_hima,R_score,R_soundBar[2];
	RenderWindow* window;
	Event* event;
	int* stateGame;
};