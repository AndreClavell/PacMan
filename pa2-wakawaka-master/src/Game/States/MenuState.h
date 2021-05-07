#pragma once

#include "State.h"
#include "Button.h"

class MenuState : public State {
private:
	ofImage img1;
	ofImage startW;
	ofImage startY;
	Button *startButton;
	ofSoundPlayer Spice;
	bool Accept= true;
	char txt;
	ofTrueTypeFont font;
	string pName;
	string n;
	
	

public:
	MenuState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	string getName(){return n;};
};
