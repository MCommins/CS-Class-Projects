#pragma once
#include "ofMain.h"

class Walker {

public:
	int x;
	int y;
	int size;
	ofColor color;
	Walker();
	Walker(int x, int y, int size, ofColor color);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void move();
	void draw();
};

