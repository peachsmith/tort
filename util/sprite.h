#ifndef TORT_SPRITE_H
#define TORT_SPRITE_H

#include "tort.h"

//----------------------------------------------------------------------------
// terrain renderers
void sprite_draw_terrain(cr_app *app, int x, int y, int type);
void sprite_draw_grass_1(cr_app *app, int x, int y);
void sprite_draw_grass_2(cr_app *app, int x, int y);
void sprite_draw_water(cr_app *app, int x, int y);
void sprite_draw_dirt(cr_app *app, int x, int y);
void sprite_draw_tree(cr_app *app, int x, int y);

void sprite_draw_roof_1(cr_app *app, int x, int y);
void sprite_draw_roof_2(cr_app *app, int x, int y);
void sprite_draw_roof_3(cr_app *app, int x, int y);
void sprite_draw_roof_4(cr_app *app, int x, int y);
void sprite_draw_roof_5(cr_app *app, int x, int y);
void sprite_draw_roof_6(cr_app *app, int x, int y);

void sprite_draw_wall_1(cr_app *app, int x, int y);
void sprite_draw_door(cr_app *app, int x, int y);

//----------------------------------------------------------------------------
// entity renderers
void sprite_draw_user(cr_app *app, int x, int y, int mirror, int tile);
void sprite_draw_sign(cr_app *app, int x, int y);

#endif