#include "brick.h"
#include "ofMain.h"

const char RED = 'r';
const char GREEN = 'g';
const char BLUE = 'b';
const char YELLOW = 'y';
const char PURPLE = 'p';
const char TURQOISE = 't';

Brick::Brick() {
	this->x = ofGetWidth() * 5/11;
	this->w = ofGetWidth() / 11 - 1;
	this->h = ofGetHeight() / 16 - 1;
	this->y = 52;
	this->color = ofColor(255);
	this->destroyed = false;
	this->points = 10;
	this->speedModifier = 0;
	this->type = 1;
}

Brick::Brick(int x, int y, int w, int h, char kind) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->destroyed = false;
	if (kind == RED) {
		this->points = 10;
		this->speedModifier = 0;
		this->type = 1;
		this->color = ofColor(255, 0, 0);
	}
	else if (kind == GREEN) {
		this->points = 20;
		this->speedModifier = 0.05;
		this->type = 2;
		this->color = ofColor(0, 255, 0);
		}
	else if (kind == BLUE) {
		this->points = 50;
		this->speedModifier = 0.1;
		this->type = 3;
		this->color = ofColor(0, 0, 255);
	}
	else if (kind == YELLOW) {
		this->points = 100;
		this->speedModifier = 0.15;
		this->type = 4;
		this->color = ofColor(255, 255, 0);
	}
	else if (kind == PURPLE) {
		this->points = 200;
		this->speedModifier = 0.2;
		this->type = 5;
		this->color = ofColor(100, 0, 100);
	}
	else if (kind == TURQOISE) {
		this->points = 500;
		this->speedModifier = 0.3;
		this->type = 6;
		this->color = ofColor(0, 255, 255);
	}
}

void Brick::draw() {
	ofSetColor(color);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofDrawRectangle(x, y, w, h);
}
