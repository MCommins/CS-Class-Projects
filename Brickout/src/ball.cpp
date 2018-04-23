#include "ball.h"

const int HIT_CLEARANCE = 5;
const int ROTATION = 5;

Ball::Ball() {
	this->radius = 10;
}

void Ball::draw() {
	ofSetColor(255);
	ofDrawCircle(position.x, position.y, radius);
}

void Ball::move() {
	position += velocity;
	if (position.x < 0 + radius){
		bounceFromLeft(0);
	}
	else if (position.x > ofGetWidth() - radius) {
		bounceFromRight(0);
	}
	else if (position.y < 0) {
		bounceFromTop(0);
	}
}

void Ball::bounceFromLeft(float modifier) {
	position.x += HIT_CLEARANCE;
	velocity.x *= -(1 + modifier);
	velocity.rotate(ofRandom(-1 * ROTATION, ROTATION));
}
void Ball::bounceFromRight(float modifier) {
	position.x -= HIT_CLEARANCE;
	velocity.x *= -(1 + modifier);
	velocity.rotate(ofRandom(-1 * ROTATION, ROTATION));
}
void Ball::bounceFromTop(float modifier) {
	position.y += HIT_CLEARANCE;
	velocity.y *= -(1 + modifier);
	velocity.rotate(ofRandom(-1 * ROTATION, ROTATION));
}
void Ball::bounceFromBottom(float modifier) {
	position.y -= HIT_CLEARANCE;
	velocity.y *= -(1 + modifier);
	velocity.rotate(ofRandom(-1 * ROTATION, ROTATION));
}

bool Ball::hits(Brick *brick) {
	if (!brick->destroyed) {
		//hits bottom side of brick
		if (position.y - radius < brick->y + brick->h && position.x - radius > brick->x && position.x + radius < brick->x + brick->w && position.y - radius > brick->y + brick->h - HIT_CLEARANCE) {
			bounceFromTop(brick->speedModifier);
			return true;
		}
		//hits left side
		else if (position.x + radius > brick->x && position.y - radius < brick->y + brick->h && position.y + radius > brick->y && position.x + radius < brick->x + HIT_CLEARANCE) {
			bounceFromRight(brick->speedModifier);
			return true;
		}
		//hits right side
		else if (position.x - radius < brick->x + brick->w && position.y - radius < brick->y + brick->h && position.y + radius > brick->y && position.x - radius > brick->x + brick->w - HIT_CLEARANCE) {
			bounceFromLeft(brick->speedModifier);
			return true;
		}
		//hits top side
		else if (position.y + radius > brick->y && position.x - radius > brick->x && position.x + radius < brick->x + brick->w && position.y + radius < brick->y + HIT_CLEARANCE) {
			bounceFromBottom(brick->speedModifier);
			return true;
		}
		else return false;
	}
}

void Ball::initiate() {
	position = ofVec2f(ofRandom(ofGetWidth() / 2 - 100, ofGetWidth() / 2 + 100), ofGetHeight() / 2 + 200);
	velocity = ofVec2f(ofRandom(-0.3, 0.3), -0.6);
	if (radius != 10) radius = 10;
}