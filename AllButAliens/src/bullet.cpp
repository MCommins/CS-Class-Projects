#include "ofMain.h"
#include "bullet.h"

struct bullet {
	float x;
	float shipX;
	float y;
	float shipY;
	ofColor c;
};

struct bullet* bullet_construct(float x, float y) {
	struct bullet* thisBullet = (struct bullet*)malloc(sizeof(struct bullet));
	thisBullet->x = x;
	thisBullet->shipX = 0;
	thisBullet->y = y;
	thisBullet->shipY = 0;
	thisBullet->c = ofColor(50, 255, 0);
	return thisBullet;
}

void bullet_set(struct bullet* bullet, float shipX, float shipY, ofSoundPlayer pew) {
	if (bullet->y < 0) {
		bullet->x = shipX;
		bullet->y = shipY;
		pew.play();
	}
}

void bullet_move(struct bullet* bullet) {
	if (bullet->y > -20) {
		bullet->y -= 10;
	}
}

void bullet_draw(struct bullet* bullet) {
	ofSetColor(bullet->c);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofDrawRectangle(bullet->x, bullet->y, 7, 7);
}