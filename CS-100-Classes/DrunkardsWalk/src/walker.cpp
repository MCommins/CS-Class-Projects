#include "walker.h"

Walker::Walker() {
	this->x = 500;
	this->y = 500;
	this->size = 20;
	this->color = ofColor(255);
}

Walker::Walker(int x, int y, int size, ofColor color) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
}

void Walker::moveLeft() {
	x -= 3;
}

void Walker::moveRight() {
	x +=3;
}

void Walker::moveUp() {
	y -=3;
}

void Walker::moveDown() {
	y +=3;
}

void Walker::move() {
	int direction = ofRandom(4);
	if (direction == 0) {
		moveUp();
	}
	else if (direction == 1) {
		moveDown();
	}
	else if (direction == 2) {
		moveLeft();
	}
	else if (direction == 3) {
		moveRight();
	}
}

void Walker::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, size);
}