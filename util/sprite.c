#include "tort.h"
#include "assets.h"
#include "util/sprite.h"

void sprite_draw_user(cr_app *app, int x, int y, int mirror, int tile)
{
    // tile dimensions
    int tile_w = 16;
    int tile_h = 16;

    // tile coordinates
    int tile_x = tile;
    int tile_y = 1;

    cr_rect src = {
        .x = tile_x * tile_w,
        .y = tile_y * tile_h,
        .w = tile_w,
        .h = tile_h};

    cr_rect dest = {
        .x = x,
        .y = y,
        .w = tile_w,
        .h = tile_h};

    cr_draw_texture(
        app,
        app->textures[TORT_TEXTURE_SPRITES],
        &src,
        &dest,
        mirror);
}

void sprite_draw_terrain(cr_app *app, int x, int y, int type)
{
    cr_rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 16;
    rect.h = 16;

    cr_color c = 0xff56bf4b; // green grass
    if (type == 2)
    {
        c = 0xfffce797; // tan dirt
    }
    if (type == 3)
    {
        c = 0xff0054f0; // blue water
    }

    cr_set_color(app, c);
    cr_draw_rect(app, &rect, 1);
}

void sprite_draw_sign(cr_app *app, int x, int y)
{
    // tile dimensions
    int tile_w = 16;
    int tile_h = 16;

    cr_rect src = {
        .x = 0 * tile_w,
        .y = 2 * tile_h,
        .w = tile_w,
        .h = tile_h};

    cr_rect dest = {
        .x = x,
        .y = y,
        .w = tile_w,
        .h = tile_h};

    cr_draw_texture(
        app,
        app->textures[TORT_TEXTURE_SPRITES],
        &src,
        &dest,
        0);
}
