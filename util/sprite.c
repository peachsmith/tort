#include "tort.h"
#include "assets.h"
#include "util/sprite.h"

static const int tile_w = 16;
static const int tile_h = 16;

static void set_tile_rect(cr_rect *r, int x, int y)
{
    r->x = x;
    r->y = y;
    r->w = tile_w;
    r->h = tile_h;
}

//----------------------------------------------------------------------------
// terrain renderers

#define MAX_TILE_RENDERERS 15
static void sprite_draw_nothing(cr_app *app, int x, int y) {}
static void (*tile_renderers[MAX_TILE_RENDERERS])(cr_app *, int, int) = {
    sprite_draw_nothing,   // 0
    sprite_draw_grass_1,   // 1 plain grass
    sprite_draw_dirt,      // 2
    sprite_draw_water,     // 3
    sprite_draw_tree,      // 4
    sprite_draw_grass_2,   // 5 some extra blades of grass
    sprite_draw_roof_1,    // 6  bottom left
    sprite_draw_roof_2,    // 7  top left corner
    sprite_draw_roof_3,    // 8  top right corner
    sprite_draw_roof_4,    // 9  bottom right corner
    sprite_draw_roof_5,    // 10 top middle
    sprite_draw_roof_6,    // 11 bottom middle
    sprite_draw_wall_1,    // 12 brick wall with no features
    sprite_draw_door,      // 13
    sprite_draw_wood_floor // 14
};

void sprite_draw_terrain(cr_app *app, int x, int y, int type)
{
    if (type > MAX_TILE_RENDERERS)
    {
        type = 0;
    }

    tile_renderers[type](app, x, y);
}

void sprite_draw_grass_1(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 5 * tile_w, 2 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_grass_2(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 5 * tile_w, 3 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_water(cr_app *app, int x, int y)
{
    int water_offset = app->extension->counters[TORT_COUNTER_60_FRAMES];
    cr_rect src, dest;
    set_tile_rect(&src, (2 + water_offset) * tile_w, 3 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_dirt(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 3 * tile_w, 2 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_tree(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 4 * tile_w, 2 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_1(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 0 * tile_w, 4 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_2(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 0 * tile_w, 3 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_3(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 1 * tile_w, 3 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_4(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 1 * tile_w, 4 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_5(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 3 * tile_w, 4 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_roof_6(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 2 * tile_w, 4 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_wall_1(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 0 * tile_w, 5 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_door(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 1 * tile_w, 5 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

void sprite_draw_wood_floor(cr_app *app, int x, int y)
{
    cr_rect src, dest;
    set_tile_rect(&src, 2 * tile_w, 5 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}

//----------------------------------------------------------------------------
// entity renderers

void sprite_draw_user(cr_app *app, int x, int y, int mirror, int tile)
{
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

void sprite_draw_sign(cr_app *app, int x, int y)
{
    cr_rect src;
    cr_rect dest;
    set_tile_rect(&src, 0 * tile_w, 2 * tile_h);
    set_tile_rect(&dest, x, y);
    cr_draw_texture(app, app->textures[TORT_TEXTURE_SPRITES], &src, &dest, 0);
}
