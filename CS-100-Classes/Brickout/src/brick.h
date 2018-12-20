#pragma once

#include "ofMain.h"

class Brick {
public:
	int x;
	int y;
	int w;
	int h;
	ofColor color;
	int points;
	int type;
	float speedModifier;
	char kind;
	bool destroyed;
	Brick();
	Brick(int x, int y, int w, int h, char kind);
	void draw();
	
};