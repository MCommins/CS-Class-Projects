//Michael Commins
//Exercise 7: Concentric Circles


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(32);
	ofSetBackgroundColor(255);
	x = ofGetWidth() / 2;
	y = ofGetHeight() / 2;
	radius = 21;
	toad.load("images/hypnotoad.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	toad.draw(x, y, 300, 300);
	drawConcentricCircle(x + 80, y + 83, radius);
	drawConcentricCircle(x + 130, y + 83, radius);
}

int ofApp::drawConcentricCircle(int x, int y, int radius) {
	
	//Make it Rave!
	ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));

	ofDrawCircle(x, y, radius);
	if (radius == 1) {
		return 1;
	}
	else if (radius > 0) {
		return drawConcentricCircle(x, y, radius - 1);
	}
}