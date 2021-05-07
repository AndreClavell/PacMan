#pragma once
#include "Animation.h"
#include "EntityManager.h"


class Player : public Entity
{
private:
    int health;
    int score = 0;
    int hScore = 0;
    int timer = 120;
    bool resetTimer;
    bool canMove;
    bool canK = false;
    bool died = false;
    bool inmune= true;
    int speed = 4;
    int xPos;
    int yPos;
    bool walking = false;
    bool eat = true;
    int eatCooldown = 0;
    FACING facing = DOWN;
    ofImage up, down, left, right, lifes;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    EntityManager *em;
    ofSoundPlayer eating;
    ofTrueTypeFont font;

public:
    Player( int, int, int, int, int, EntityManager *);
    virtual int getHealth() { return health; };
    void setHealth(int s){health= s; };
    int getScore() { return score; };
    void addScore(int s) { score += s; };
    void setScore(int s) { score = s; };
    void setHScore() {((hScore<score)?hScore=score:hScore=hScore);};
    void setPrevHScore(int h){hScore = h; };
    int getHScore() {return hScore;};
    void tick();
    void render();
    void keyPressed(int);
    void keyReleased(int);
    void damage(Entity *damageSource);
    void mousePressed(int, int, int);
    void reset();
    void setFacing(FACING facing);
    void checkCollisions();
    void die();
    bool dead();
    
};


