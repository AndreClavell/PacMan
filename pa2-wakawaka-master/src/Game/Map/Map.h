#pragma once
#include "Player.h"
#include "EntityManager.h"
#include "GhostSpawner.h"

class Map
{

public:
  Map(EntityManager *);
  void addBlock(Block *);
  void addEntity(Entity *);
  void setGhost(GhostSpawner *);
  void setPlayer(Player *);
  void tick();
  void render();
  void keyPressed(int key);
  void mousePressed(int x, int y, int button);
  void keyReleased(int key);
  Player* getPlayer(){return player;};
  GhostSpawner* getGhost(){return ghost;};

private:
  EntityManager *entityManager;
  Player *player;
  GhostSpawner *ghost;
};