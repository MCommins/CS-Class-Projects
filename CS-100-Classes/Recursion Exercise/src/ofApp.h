#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		int x;
		int y;
		int radius;
		int drawConcentricCircle(int x, int y, int radius);

		ofImage toad;
};
