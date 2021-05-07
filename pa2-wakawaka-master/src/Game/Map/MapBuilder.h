#pragma once
#include "ofMain.h"
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"


class MapBuilder
{
public:
        MapBuilder();
        Map *createMap(ofImage);


private:
        int health;
        vector<ofImage> bound;
        int pixelMultiplier;
        int color;
        ofColor boundBlock;
        ofColor pacman;
        ofColor ghostC;
        ofColor dotC;
        ofColor bigDotC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager *entityManager;
};