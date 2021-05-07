#include "MapBuilder.h"
#include "Map.h"
#include "GhostSpawner.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager *em, int color) : Entity(x, y, width, height)
{
    this->em = em;
    for (int i = 0; i < 4; i++)
    {
        ghost = new Ghost(x, y, width, height, em, i);
        em->entities.push_back(ghost);
    }
}

void GhostSpawner::keyPressed(int key)
{
    if (key == 'g' || key == 'G')
    {
        ghost1 = new Ghost(x, y, width, height, em, round(ofRandom(0, 3)));
        em->entities.push_back(ghost1);
    }
}
void GhostSpawner::tick()
{
    if (cooldown <= 0)
    {
        for (Entity *en : em->entities)
        {
            if (dynamic_cast<Ghost *>(en))
            {
                amount++;
            }
        }
        if (amount < 4)
        {
            ghost1 = new Ghost(x, y, width, height, em, round(ofRandom(0, 3)));
            em->entities.push_back(ghost1);
        }
        amount = 0;
        cooldown = 120;
    }
    else
    {
        cooldown--;
    }
}
void GhostSpawner::render()
{
}