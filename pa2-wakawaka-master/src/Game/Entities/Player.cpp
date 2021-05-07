#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"

Player::Player(int x, int y, int width, int height, int health, EntityManager *em) : Entity(x, y, width, height)
{
    xPos = x;
    yPos = y;
    eating.load("sounds/waka.mp3");
    sprite.load("images/pacman.png");
    font.load("fonts/Pixeboy-z8XGD.ttf",24);
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);

    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1, downAnimframes);
    walkUp = new Animation(1, upAnimframes);
    walkLeft = new Animation(1, leftAnimframes);
    walkRight = new Animation(1, rightAnimframes);

    this->em = em;
    this->health=3;
}

void Player::tick()
{
    canMove = true;
    checkCollisions();
    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
            walkUp->tick();
        }
        else if (facing == DOWN)
        {
            y += speed;
            walkDown->tick();
        }
        else if (facing == LEFT)
        {
            x -= speed;
            walkLeft->tick();
        }
        else if (facing == RIGHT)
        {
            x += speed;
            walkRight->tick();
        }
    }
    if (timer <= 0)
    {
        canK = false;
        timer = 120;
    }
    else
    {
        timer--;
        if (resetTimer)
        {
            timer = 120;
            resetTimer = false;
        }
    }
    if (eat && eatCooldown <= 0)
    {
        eating.play();
        eat = false;
        eatCooldown = 10;
    }
    else if (eat && eatCooldown > 0)
    {
        eatCooldown--;
    }
}

void Player::render()
{
    ofSetColor(256, 256, 256);

    // ofDrawRectangle(getBounds());
    if (facing == UP)
    {
        walkUp->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == DOWN)
    {
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == LEFT)
    {
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == RIGHT)
    {
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    //Draws Scores
    font.drawString("HIGH SCORE\n",0,30);
    ofSetColor(255,255,0);
    font.drawString(to_string(getHScore()),0,50);
    ofSetColor(255);
    font.drawString("SCORE\n",0, 70);
    ofSetColor(255,255,0);
    font.drawString(to_string(getScore()), 0, 90);

    for (int i = 0; i < health; i++)
    {
        lifes.cropFrom(sprite, 16, 16, 16, 16);
        lifes.draw(200 + (i * 20), ofGetHeight() - 60);
    }
}

void Player::keyPressed(int key)
{
    switch (key)
    {
    case 'w':
        setFacing(UP);
        break;
    case 's':
        setFacing(DOWN);
        break;
    case 'a':
        setFacing(LEFT);
        break;
    case 'd':
        setFacing(RIGHT);
        break;
    case 'p':
        setScore(0);
        break;
    case 'n':
        health -= 1;
        break;
    case 'm':
        health += 1;
        break;
    case 'W':
        setFacing(UP);
        break;
    case 'S':
        setFacing(DOWN);
        break;
    case 'A':
        setFacing(LEFT);
        break;
    case 'D':
        setFacing(RIGHT);
        break;
    case 'P':
        setScore(0);
        break;
    case 'N':
        health -= 1;
        break;
    case 'M':
        health += 1;
        break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}

void Player::mousePressed(int x, int y, int button)
{
}

void Player::setFacing(FACING facing)
{
    this->facing = facing;
}

void Player::checkCollisions()
{
    for (Block *block : em->blocks)
    {
        switch (facing)
        {
        case UP:
            if (this->getBounds(x, y - speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case DOWN:
            if (this->getBounds(x, y + speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case LEFT:
            if (this->getBounds(x - speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case RIGHT:
            if (this->getBounds(x + speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        }
    }
    for (Entity *entity : em->entities)
    {
        if (collides(entity))
        {
            if (dynamic_cast<Dot *>(entity))
            { 
                
                entity->remove = true;
                addScore(10);
                setHScore();
                eat = true;
            }
            else if (dynamic_cast<BigDot *>(entity))
            {
                if(canK){
                    resetTimer = true;
                   
                }
                entity->remove = true;
                addScore(50);
                setHScore();
                canK = true;
                eat = true;
                for(Entity *en : em->entities){
                    Ghost* g = dynamic_cast<Ghost*>(en);
                    if(dynamic_cast<Ghost *>(en)){
                        g->setCanDie(true);
                        g->resetTimer();
                    }
                    
                }
                
            }
            else if (dynamic_cast<Ghost*>(entity))
            {
                if (canK)
                {       
                    entity->remove = true;
                    addScore(100);
                    eat = true;
                    
                }
                else
                {
                    die();
                }
            }
        }
    }
}

void Player::die(){
    health--;
    x = xPos;
    y = yPos;
    
}
bool Player::dead(){
    
    if(this->health<=0){
        return true;
    }
    else{
        return false;
    }
}



