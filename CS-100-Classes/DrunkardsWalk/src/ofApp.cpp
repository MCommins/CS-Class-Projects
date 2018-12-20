//Michael Commins
//Project 2: Drunkard's Walk

#include "ofApp.h"
#include "walker.h"
#include "stdlib.h"

const int NUMBER_OF_WALKERS = 1000;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(55);
	ofSetCircleResolution(20);
	for (int i = 0; i < NUMBER_OF_WALKERS; ++i) {
		walkers.push_back(new Walker(ofGetWidth() / 2, ofGetHeight() / 2, 10, ofColor(ofRandom(255), ofRandom(255), ofRandom(255))));
	}
}
//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < walkers.size(); ++i) {
		walkers[i]->move();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < walkers.size(); ++i) {
		walkers[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		walkers.push_back(new Walker(ofGetWidth() / 2, ofGetHeight() / 2, 10, ofColor(ofRandom(255), ofRandom(255), ofRandom(255))));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
