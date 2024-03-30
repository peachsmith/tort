#include "tort.h"
#include "assets.h"
#include "util/ui.h"

void ui_draw_panel(cr_app *app, int x, int y, int w, int h)
{
    cr_rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    cr_set_color(app, CR_COLOR_VINIK_BLACK);
    cr_draw_rect(app, &rect, 1);

    cr_set_color(app, CR_COLOR_VINIK_LIGHT_GRAY);
    cr_draw_rect(app, &rect, 0);
}

void ui_draw_text(cr_app *app)
{
}

void ui_draw_cursor(cr_app *app, int x, int y)
{
    cr_rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 16;
    rect.h = 16;

    cr_set_color(app, CR_COLOR_VINIK_LIGHT_GRAY);
    cr_draw_rect(app, &rect, 1);
}

void ui_draw_indicator(cr_app *app, int x, int y, int type)
{
    // tile dimensions
    int tile_w = 16;
    int tile_h = 16;

    cr_rect src = {
        .x = 1 * tile_w,
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
