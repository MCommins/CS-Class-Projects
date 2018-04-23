#include "star.h"
#include "ofMain.h"

struct star {
	float x;
	float y;
	float v;
	ofColor c;
};

struct star* star_construct() {
	struct star* temp = (struct star*)malloc(sizeof(struct star));
	temp->x = ofRandom(0, ofGetWidth());
	temp->y = 0;
	temp->v = ofRandom(0, 15);
	temp->c = ofColor(255, 255, 255);
	return temp;
}

void star_move(struct star* star) {
	star->y += star->v;
	if (star->y > ofGetHeight()) {
		star->y = 0;
		star->x = ofRandomWidth();
	}
}

void star_draw(struct star* star) {
	ofSetColor(star->c);
	ofDrawLine(star->x, star->y, star->x, star->y + 10);
}