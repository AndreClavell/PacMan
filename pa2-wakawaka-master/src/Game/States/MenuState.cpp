#include "MenuState.h"

MenuState::MenuState()
{
	img1.load("images/Pac-Man-Start.png");
	startW.load("images/start-hover.png");
	startY.load("images/start-hover1.png");
	startButton = new Button(ofGetWidth() / 2 - 75, ofGetHeight() / 2, 128, 50, "");
	font.load("fonts/Pixeboy-z8XGD.ttf",36);
	
}
void MenuState::tick()
{
	startButton->tick();
	if (startButton->wasPressed()&& !Accept)
	{
		setNextState("Game");
		setFinished(true);
	}
}
void MenuState::render()
{
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(255);
	img1.draw(0, 0, ofGetWidth(), ofGetHeight());
	startButton->render();
	if ((ofGetMouseX() >= startButton->getX() && ofGetMouseY() >= startButton->getY()) && (ofGetMouseX() <= startButton->getX() + startButton->getWidth() && ofGetMouseY() <= startButton->getY() + startButton->getHeight())&& !Accept)
	{
		startY.draw(startButton->getX(), startButton->getY(), startButton->getWidth(), startButton->getHeight());
	}
	else
	{
		startW.draw(startButton->getX(), startButton->getY(), startButton->getWidth(), startButton->getHeight());
	}
	ofSetColor(255);
	ofDrawBitmapString("x: " + to_string(ofGetMouseX()) + "\ny: " + to_string(ofGetMouseY()), 10, 10);
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(startButton->getX(), startButton->getY(), startButton->getWidth(), startButton->getHeight());
	
	if (Accept)
	{
		if (pName.size()==4)
		{
			font.drawString("Enter to Accept", (ofGetWidth() / 2) - 160, ofGetHeight() - 300);
		}else{
			font.drawString("Enter Name", (ofGetWidth() / 2) - 110, ofGetHeight() - 300);
		}
		ofSetColor(0, 255, 0);
		font.drawString(pName, (ofGetWidth() / 2) - 50, ofGetHeight() - 260);
		ofDrawLine((ofGetWidth() / 2) - 80, ofGetHeight() - 250, (ofGetWidth() / 2) + 70, ofGetHeight() - 250);
	}
}

void MenuState::keyPressed(int key)
{
	if (Accept)
	{
		if (pName.size() < 4)
		{
			if (key != OF_KEY_RETURN && key != OF_KEY_RIGHT_SHIFT)
			{
				txt = key;
				pName.push_back(toupper(txt));
			}
		}
		if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL)
		{
			pName.clear();
		}
	}
	if (key == OF_KEY_RETURN && pName.size() == 4)
	{
		Accept = false;
		n= pName;
	}
}

void MenuState::mousePressed(int x, int y, int button)
{
	startButton->mousePressed(x, y);
}

void MenuState::reset()
{
	setFinished(false);
	setNextState("");
	startButton->reset();
}