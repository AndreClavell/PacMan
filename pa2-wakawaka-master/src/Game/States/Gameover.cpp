
#include "GameOverState.h"
#include "Entity.h"

GameOverState::GameOverState(Map* m)
{
	
	this->map=m;
	img1.load("images/GlitchOver.png");
	restartW.load("images/Replaybutton.png");
	restartY.load("images/Replaybutton(1).png");
	restartButton = new Button(ofGetWidth() / 2 - 75, ofGetHeight() / 2,128, 50, "");
	font.load("fonts/Pixeboy-z8XGD.ttf",36);

	
}

void GameOverState::tick()
{
	restartButton->tick();
	if (restartButton->wasPressed())
	{
		setNextState("Game");
		setFinished(true);
		
	}
 
}
void GameOverState::render()
{
	ofSetBackgroundColor(0,0,0);
	ofSetColor(255);
	img1.draw(ofGetWidth()/4,30, ofGetWidth()/2, ofGetHeight()/2);
	restartButton->render();
	if((ofGetMouseX()>= restartButton->getX() && ofGetMouseY()>= restartButton->getY())&&(ofGetMouseX()<= restartButton->getX()+restartButton->getWidth()&&ofGetMouseY()<= restartButton->getY()+restartButton->getHeight())){
	restartY.draw(restartButton->getX(),restartButton->getY(),restartButton->getWidth(),restartButton->getHeight());
	}else{
	restartW.draw(restartButton->getX(),restartButton->getY(),restartButton->getWidth(),restartButton->getHeight());
	}
	ofSetColor(255);
	ofDrawBitmapString("x: " + to_string(ofGetMouseX()) + "\ny: " + to_string(ofGetMouseY()), 10, 10);
	
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(restartButton->getX(),restartButton->getY(),restartButton->getWidth(),restartButton->getHeight());
	ofSetColor(255,255,0);
	font.drawString("High Score: " + to_string(map->getPlayer()->getHScore()), (ofGetWidth()/2)-130, ofGetHeight()-230);

	ofSetColor(0, 255, 0);
	font.drawString(Name, (ofGetWidth() / 2) - 142, ofGetHeight() - 200);
	ofSetColor(255, 255, 0);
	font.drawString("\t\t\tscored: " + to_string(map->getPlayer()->getScore()), (ofGetWidth() / 2) - 140, ofGetHeight() - 200);
}

void GameOverState::keyPressed(int key)
{
}

void GameOverState::mousePressed(int x, int y, int button)
{
	restartButton->mousePressed(x, y);
}

void GameOverState::reset()
{
	setFinished(false);
	setNextState("");
	restartButton->reset();
}