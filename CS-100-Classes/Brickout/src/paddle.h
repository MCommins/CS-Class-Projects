#pragma once

#include "ofMain.h"

class Paddle {

public:
	float x;
	int y;
	float w;
	float h;
	ofColor color;
	Paddle();
	Paddle(float w);
	void draw();
}; 