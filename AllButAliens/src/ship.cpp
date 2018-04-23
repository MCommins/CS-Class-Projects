#include "ship.h"
#include "ofMain.h"

struct ship {
	float x;
	float y;
	float w;
	float h;
	float velocity;
	float theta;
	float projectileY;
	bool finishPath;
	ofColor color;
};

struct ship* ship_construct(float x, float y, float w, float h) {
	struct ship* thisShip = (struct ship*)malloc(sizeof(struct ship));
	thisShip->x = x;
	thisShip->y = y;
	thisShip->w = w;
	thisShip->h = h;
	thisShip->velocity = 0;
	thisShip->theta = 0;
	thisShip->projectileY = 0;
	thisShip->finishPath = TRUE;
	return thisShip;
}

void ship_move(struct ship* ship) {
	ship->x += ship->velocity;
	if (ship->x < 0 || ship->x > ofGetWidth() - ship->w) {
		ship->velocity += ship->velocity * -2;
		ship->x += ship->velocity;
	}
}

void ship_move_right(struct ship* ship) {
	if (ship->velocity < 0.6) {
		ship->velocity += 0.2;
	}
}

void ship_move_left(struct ship* ship) {
	if (ship->velocity > -0.6) {
		ship->velocity -= 0.2;
	}
}

void ship_move_up(struct ship* ship) {
	if (ship->y > 0) {
		ship->y -= 2;
	}
}

void ship_move_down(struct ship* ship) {
	if (ship->y < ofGetHeight()) {
		ship->y += 2;
	}
}

void ship_bounce(struct ship* ship) {
	ship->y += (cos(ship->theta) * sin(ship->theta)) / 20;
	ship->theta += 0.01;
}

void ship_draw(struct ship* ship, ofImage sprite) {
	sprite.draw(ship->x, ship->y, ship->w, ship->h);
}

void ship_reticle(struct ship* ship, ofImage crosshair) {
	crosshair.draw(ship->x + ship->w / 2 - 20, ship->y - 200, 40, 40);
}

float ship_x(struct ship* ship) {
	float x = ship->x;
	return x;
}

float ship_y(struct ship* ship) {
	float y = ship->y;
	return y;
}