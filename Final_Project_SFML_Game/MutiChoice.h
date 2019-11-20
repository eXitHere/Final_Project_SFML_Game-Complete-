#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
using namespace std;
using namespace sf;

class MutiChoice
{
public:
	MutiChoice(RenderWindow* window, Event* event);
	int getChoice();
	void Set(int number);

private:
	void DRAW();
	vector<Texture> textProcess;
	bool keyReleased = false;
	int index = 0, forReturn = 0;
	Event* event;
	RenderWindow* window;
	Texture texture[5];
	Sprite body, Grid;
};

