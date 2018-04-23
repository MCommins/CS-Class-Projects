#include "Paddle.h"

Paddle::Paddle() {
}

Paddle::Paddle(float w) {
	this->x = ofGetWidth() / 2;
	this->y = ofGetHeight() - 30;
	this->w = w;
	this->h = 30;
	this->color = ofColor(200, 0, 0);
}
void Paddle::draw() {
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}