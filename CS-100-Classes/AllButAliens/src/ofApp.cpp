

#include "ofApp.h"
#include "ship.h"
#include "star.h"
#include "bullet.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(0, 0, 0);

	thisShip = ship_construct(ofGetWidth() / 2, ofGetHeight() - 100, 50, 50);

	thisBullet = bullet_construct(-50, -50);

	for (int i = 0; i < 50; ++i) {
		stars[i] = star_construct();
	}
	
	shipImage.load("images/Galaga_Fighter.png");
	crosshair.load("images/crosshair.png");
	theme.load("sound/8-punk-8-bit-music.mp3");
	pew.load("sound/10-coin.mp3");
	scoreFont.load("fonts/Xacto Blade.ttf", 40);
	
	ofSoundSetVolume(0.05);
	theme.play();
	
}

//--------------------------------------------------------------
void ofApp::update() {
	ship_move(thisShip);
	ship_bounce(thisShip);

	bullet_move(thisBullet);

	for (int i = 0; i < 50; ++i) {
		star_move(stars[i]);
	}

	frameRate = ofToString(ofGetFrameRate());
	frameCount = ofToString(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
	ship_draw(thisShip, shipImage);
	ship_reticle(thisShip, crosshair);

	bullet_draw(thisBullet);

	for (int i = 0; i < 50; ++i) {
		star_draw(stars[i]);
	}

	ofDrawBitmapString("Frame Rate:" + frameRate, 10, 10);
	ofDrawBitmapString("Total Frames:" + frameCount, 10, 30);
	scoreFont.drawString("Score:", 200, 42);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_LEFT) {
		ship_move_left(thisShip);
	}
	if (key == OF_KEY_RIGHT) {
		ship_move_right(thisShip);
	}
	if (key == OF_KEY_UP) {
		ship_move_up(thisShip);
	}
	if (key == OF_KEY_DOWN) {
		ship_move_down(thisShip);
	}
	if (key == OF_KEY_BACKSPACE) {
		bullet_set(thisBullet, ship_x(thisShip), ship_y(thisShip), pew);
	}

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
