#include "ofApp.h"


const int TITLE_SCREEN = 0;
const int GAME_SCREEN = 1;
const int GAME_OVER_SCREEN = 2;

const int BRICK_GAP = 1;
const int HEADER = 100;

vector<Brick*> bricks;
vector<string> lines;


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	gamestate = TITLE_SCREEN;
	ball = new Ball();
	paddle = new Paddle(200);
	currentScore = 0;
	title.load("images/title.png");
	gameOver.load("images/GameOver.png");
	youWin.load("images/YouWin.png");
	powerUpImage.load("images/powerUp.png");
	mono.load("mono.ttf", 20);
	monoSmall.load("mono.ttf", 8);
	music.load("sound/music.mp3");
	hit.load("sound/hit.wav");
	music.setVolume(0.5);
	music.setLoop(true);
	music.play();
	hit.setVolume(0.7);
	ofHideCursor();

	leftRect.set(200, 0, 100, 50);
	rightRect.set(ofGetWidth() - 200, -ofGetHeight() / 2 - 100, 100, 50);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (gamestate == TITLE_SCREEN) {
		updateTitleRectangle(&leftRect);
		updateTitleRectangle(&rightRect);
	}
	if (gamestate == GAME_SCREEN) {
		updateBall();
		if (level == 4) {
			if (powerUp->destroyed && !powerUpOn) {
				updatePowerUp();
			}
		}
		for (int i = 0; i < bricks.size(); ++i) {
			if (ball->hits(bricks[i])) {
				if (!bricks.at(i)->destroyed) {
					bricks[i]->destroyed = true;
					currentScore += bricks[i]->points;
					hit.setSpeed(bricks.at(i)->type);
					hit.play();
					bricksLeft--;
				}
			}
		}
		if (bricksLeft == 0) {
			if (level == 4) {
				gamestate = GAME_OVER_SCREEN;
				gameIsWon = true;
			}
			else {
				level++;
				prepareLevel();
			}
		}
	}
	if (gamestate == GAME_OVER_SCREEN) {
		music.stop();
		music.play();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (gamestate == TITLE_SCREEN) {
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(255);
		title.draw(ofGetWidth() / 2, ofGetHeight() / 2);
		
		ofSetColor(0, 255, 0);
		ofDrawRectangle(leftRect);
		ofDrawRectangle(rightRect);
	}
	if (gamestate == GAME_SCREEN){
		if (level == 4) {
			if (powerUp->destroyed && !powerUpOn) {
				ofSetRectMode(OF_RECTMODE_CENTER);
				powerUpImage.draw(powerUp->x, powerUp->y);
			}
		}
		paddle->draw();
		ball->draw();
		drawBorder();
		for (int i = 0; i < bricks.size(); ++i) {
			if (!bricks.at(i)->destroyed) {
				bricks[i]->draw();
			}
		}
		ofSetColor(255);
		monoSmall.drawString("Score: " + ofToString(currentScore), 50, ofGetHeight() - 20);
		monoSmall.drawString("Balls Remaining: " + ofToString(livesLeft), 150, ofGetHeight() - 20);
	}
	if (gamestate == GAME_OVER_SCREEN) {
		if (gameIsWon == true) {
			youWin.draw(ofGetWidth() / 2, ofGetHeight() / 2 - 200);
		}
		else {
			gameOver.draw(ofGetWidth() / 2, ofGetHeight() / 2 - 200);
		}
		ofSetColor(255);
		mono.drawString("Your Score: " + ofToString(currentScore), 100, ofGetHeight() / 2);
		mono.drawString("Press SPACEBAR to return to level select!", 100, ofGetHeight() / 2 + 200);
		
	}
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (gamestate == TITLE_SCREEN) {
		if (key == '1') {
			level = 1;
			gamestate++;
			prepareLevel();
			livesLeft = 3;
		}
		if (key == '2') {
			level = 2;
			gamestate++;
			prepareLevel();
			livesLeft = 3;
		}
		if (key == '3') {
			level = 3;
			gamestate++;
			prepareLevel();
			livesLeft = 3;
		}
		if (key == '4') {
			level = 4;
			gamestate++;
			prepareLevel();
			livesLeft = 3;
		}
	}
	if (gamestate == GAME_OVER_SCREEN) {
		if (key == ' ') {
			gamestate = TITLE_SCREEN;
			currentScore = 0;
			gameIsWon = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	paddle->x = x;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//Function Definitions

void ofApp::prepareLevel() {
	music.stop();
	music.setSpeed(1 + 0.2 * (level - 1));
	music.play();
	lines.clear();
	bricks.clear();
	delete powerUp;
	powerUpOn = false;
	livesLeft = 3;
	paddle->w = 200 / level;
	buffer = ofBufferFromFile(ofToString(level) + ".txt");
	for (auto line : buffer.getLines()) {
		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); ++i) {
		string row = lines[i];
		for (int j = 0; j < row.size(); ++j) {
			char code = row[j];
			if (code == ' ') continue;
			Brick *b = new Brick(j * ofGetWidth() / row.size(), HEADER + i * ofGetHeight() / 16, ofGetWidth() / row.size() - BRICK_GAP, ofGetHeight() / 16 - BRICK_GAP, code);
			bricks.push_back(b);
		}
	}
	if (level == 4) {
		powerUp = new Brick();
		bricks.push_back(powerUp);
	}
	bricksLeft = bricks.size();
	ball->initiate();
}

void ofApp::updateBall() {
	ball->move();
	if (ball->position.x > paddle->x - paddle->w / 2 && ball->position.x < paddle->x + paddle->w / 2 && ball->position.y + ball->radius > paddle->y - paddle->h / 2 && ball->position.y + ball->radius < paddle->y) {
		ball->bounceFromBottom(0);
		hit.setSpeed(1);
		hit.play();
	}
	if (ball->position.y - ball->radius > ofGetHeight()) {
		ball->initiate();
		livesLeft--;
	}
}

void ofApp::drawBorder() {
	ofSetColor(255, 255, 0);
	ofDrawLine(0, 0, 0, ofGetHeight());
	ofDrawLine(0, 0, ofGetWidth(), 0);
	ofDrawLine(ofGetWidth(), 0, ofGetWidth(), ofGetHeight());
}

void ofApp::updateTitleRectangle(ofRectangle *rect) {
	rect->y++;
	if (rect->y > ofGetHeight() + rect->width) {
		rect->y = -200;
	}
}

void ofApp::updatePowerUp() {
	powerUp->y++;
	if (powerUp->x > paddle->x - paddle->w / 2 && powerUp->x < paddle->x + paddle->w / 2 && powerUp->y > paddle->y - paddle->h / 2 && powerUp->y < ofGetHeight()) {
		powerUpOn = true;
		ball->radius *= 2;
		ball->velocity / 4;
	}
}