#pragma once

struct bullet* bullet_construct(float x, float y);
void bullet_set(struct bullet* bullet, float shipX, float shipY, ofSoundPlayer pew);
void bullet_move(struct bullet* bullet);
void bullet_draw(struct bullet* bullet);
