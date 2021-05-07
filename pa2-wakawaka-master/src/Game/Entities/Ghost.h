#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityManager.h"
#include "Player.h"


class Ghost : public Entity
{

private:
    int direct;
    int counter = 30;
    int change = 0;
    int timer = 120;
    int direction;
    bool canMove;
    bool canDie = false;
    bool started;
    bool dead = false;
    int speed = 4;
    int xpos;
    int ypos;
    bool walking = false;
    FACING facing = UP;
    ofImage up, down, left, right;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *die;
    EntityManager *em;

public:
    Ghost(int, int, int, int, EntityManager *,int);
    void tick();
    void render();
    void damage(Entity *damageSource);
    void reset();
    void setFacing(FACING facing);
    void checkCollisions();
    void setCanDie(bool a);
    void resetTimer();
};
