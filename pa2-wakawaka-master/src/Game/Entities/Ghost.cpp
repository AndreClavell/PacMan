#include "Ghost.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"

Ghost::Ghost(int x, int y, int width, int height, EntityManager *em, int color) : Entity(x, y, width, height)
{
    sprite.load("images/Background.png");
    //red ghost
    right.cropFrom(sprite, 456, 64, 16, 16);
    left.cropFrom(sprite, 488, 64, 16, 16);
    up.cropFrom(sprite, 520, 64, 16, 16);
    down.cropFrom(sprite, 552, 64, 16, 16);
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    vector<ofImage> deathAnimframes;
    ofImage temp;
    for (int i = 0; i < 4; i++)
    {
        temp.cropFrom(sprite, 584 + i * 16, 64, 16, 16);
        deathAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(sprite, 456 + i * 16, 64 + color * 16, 16, 16);
        rightAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(sprite, 488 + i * 16, 64 + color * 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(sprite, 520 + i * 16, 64 + color * 16, 16, 16);
        upAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(sprite, 552 + i * 16, 64 + color * 16, 16, 16);
        downAnimframes.push_back(temp);
    }
    walkDown = new Animation(1, downAnimframes);
    walkUp = new Animation(1, upAnimframes);
    walkLeft = new Animation(1, leftAnimframes);
    walkRight = new Animation(1, rightAnimframes);
    die = new Animation(2, deathAnimframes);

    this->em = em;
    started = false;
}

void Ghost::tick()
{
    if (canDie && timer > 0)
    {
        timer--;
    }
    else if (canDie && timer <= 0)
    {
        timer = 60;
        canDie = false;
    }

    if (counter <= 0)
    {
        started = true;
    }
    else
    {
        counter--;
    }
    canMove = true;
    checkCollisions();

    if (!canMove)
    {
        if (change <= 0)
        {
            direction = round(ofRandom(0, 3));
            change = 1;
        }
        else
        {
            change--;
        }

        switch (direction)
        {
        case 0:
            setFacing(UP);
            break;
        case 1:
            if (started)
            {
                setFacing(DOWN);
            }
            break;
        case 2:
            setFacing(LEFT);
            break;
        case 3:
            setFacing(RIGHT);
            break;
        }
    }

    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
            walkUp->tick();
            if(canDie){
                die->tick();
            }
        }
        else if (facing == DOWN)
        {
            y += speed;
            walkDown->tick();
            if(canDie){
                die->tick();
            }
        }
        else if (facing == LEFT)
        {
            x -= speed;
            walkLeft->tick();
            if(canDie){
                die->tick();
            }
        }
        else if (facing == RIGHT)
        {
            x += speed;
            walkRight->tick();
            if(canDie){
                die->tick();
            }
        }
    }
}

void Ghost::render()
{
    ofSetColor(256, 256, 256);
    // ofDrawRectangle(getBounds());
    if (facing == UP)
    {
        if (!canDie)
        {
            walkUp->getCurrentFrame().draw(x, y, width, height);
        }
        else
        {
            die->getCurrentFrame().draw(x, y, width, height);
        }
    }
    else if (facing == DOWN)
    {
        if (!canDie)
        {
            walkDown->getCurrentFrame().draw(x, y, width, height);
        }
        else
        {
            die->getCurrentFrame().draw(x, y, width, height);
        }
    }
    else if (facing == LEFT)
    {
        if (!canDie)
        {
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        }
        else
        {
            die->getCurrentFrame().draw(x, y, width, height);
        }
    }
    else if (facing == RIGHT)
    {
        if (!canDie)
        {
            walkRight->getCurrentFrame().draw(x, y, width, height);
        }
        else
        {
            die->getCurrentFrame().draw(x, y, width, height);
        }
    }
}

void Ghost::setFacing(FACING facing)
{
    this->facing = facing;
}

void Ghost::checkCollisions()
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
}

void Ghost::resetTimer()
{
    timer = 120;
}

void Ghost::setCanDie(bool a)
{
    canDie = a;
}