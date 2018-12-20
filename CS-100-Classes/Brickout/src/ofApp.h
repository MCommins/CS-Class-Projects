#pragma once

#include "ofMain.h"
#include "brick.h"
#include "ball.h"
#include "paddle.h"

class ofApp : public ofBaseApp{

	public:

		ofBuffer buffer;
		int gamestate;
		int level;
		int livesLeft;
		int currentScore;
		int bricksLeft;
		bool gameIsWon;
		bool powerUpOn;

		ofImage title;
		ofImage gameOver;
		ofImage youWin;
		ofImage powerUpImage;
		ofSoundPlayer music;
		ofSoundPlayer hit;
		ofTrueTypeFont mono;
		ofTrueTypeFont monoSmall;

		void prepareLevel();
		void updateBall();
		void drawBorder();
		void updateTitleRectangle(ofRectangle *rect);
		void updatePowerUp();

		Ball *ball;
		Paddle *paddle;
		Brick *powerUp;
		ofRectangle leftRect;
		ofRectangle rightRect;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
