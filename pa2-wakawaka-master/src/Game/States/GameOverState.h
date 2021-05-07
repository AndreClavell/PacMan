#pragma once
#include "State.h"
#include "Button.h"
#include "Player.h"
#include "MapBuilder.h"


class GameOverState : public State
{
private:
    ofImage img1;
    ofImage restartW;
    ofImage restartY;
    Button *restartButton;
    Map *map;
    Map* getMap(){return map;};
    string Name;
	ofTrueTypeFont font;
    
public:
    
    GameOverState(Map* m);
    void tick();
    void render();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void reset();
    void setName(string n){Name=n ;};
};