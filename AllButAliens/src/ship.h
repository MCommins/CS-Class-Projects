#pragma once
#include "ofApp.h"

struct ship *ship_construct(float x, float y, float w, float h);
void ship_move(struct ship*);
void ship_move_right(struct ship*);
void ship_move_left(struct ship*);
void ship_move_up(struct ship*);
void ship_move_down(struct ship*);
void ship_bounce(struct ship*);
void ship_draw(struct ship*, ofImage sprite);
void ship_reticle(struct ship*, ofImage crosshair);
float ship_x(struct ship* ship);
float ship_y(struct ship* ship);