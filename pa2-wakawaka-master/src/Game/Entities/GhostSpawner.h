#pragma once
#include "EntityManager.h"
#include "Ghost.h"

class GhostSpawner : public Entity{

private:
EntityManager *em;
Ghost* ghost;
Ghost* ghost1;
int amount = 0;
int cooldown = 120;
public:
GhostSpawner(int x, int y, int width, int height, EntityManager *em, int color);
void keyPressed(int key);
void tick();
void render();
};