#pragma once

#include "ofMain.h"
#include "brick.h"

class Ball {
public:
	ofVec2f position;
	ofVec2f velocity;
	int radius;
	Ball();
	void initiate();
	void draw();
	void move();
	bool hits(Brick *brick);
	void bounceFromLeft(float modifier);
	void bounceFromRight(float modifier);
	void bounceFromTop(float modifier);
	void bounceFromBottom(float modifier);
};