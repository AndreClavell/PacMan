#include "GameState.h"
#include "Entity.h"



GameState::GameState() {
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
	player= map->getPlayer();
	Spice.load("sounds/SPICY.mp3");
	Spice.setVolume(0.30);
	Spice.setLoop(true);
	Spice.play();
}


void GameState::tick() {
	map->tick();	
	
	
	if(player->dead()){

		setNextState("GameOver");
		setFinished(true);
		Spice.stop();
	}
}

void GameState::render() {
	map->render();



}

void GameState::keyPressed(int key){
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}