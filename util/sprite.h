#ifndef TORT_SPRITE_H
#define TORT_SPRITE_H

#include "tort.h"

void sprite_draw_user(cr_app *app, int x, int y, int mirror, int tile);

void sprite_draw_terrain(cr_app *app, int x, int y, int type);

void sprite_draw_sign(cr_app *app, int x, int y);

#endif