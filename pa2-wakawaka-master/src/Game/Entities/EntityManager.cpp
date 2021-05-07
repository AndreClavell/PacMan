#include "EntityManager.h"
#include "Ghost.h"

void EntityManager::tick(){
    std::vector<int> toRemove;
    for(unsigned int i=0;i<entities.size();i++){
        if(!entities[i]->remove){
            entities[i]->tick();
        }else{
            toRemove.push_back(i);
        }
    }
    for(Block* block: blocks){
        block->tick();
    }
    for(unsigned int removable: toRemove){
        entities.erase(entities.begin() + removable);
    }
}

void EntityManager::render(){

    vector<Entity*> ghosts;
    for(Block* block: blocks){
        block->render();
    }
   
    for(Entity* entity: entities){
        
        
        if (dynamic_cast<Ghost*>(entity)!=NULL)
        {
            ghosts.push_back(entity);
        }
    
         entity->render();
        
    }
    for(Entity* ghost: ghosts){
        ghost->render();
    }
}

