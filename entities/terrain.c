#include "tort.h"
#include "entities/entity_types.h"
#include "entities/terrain.h"
#include "util/sprite.h"

#include "common/util.h"

#define TERRAIN_ROWS 10
#define TERRAIN_COLS 15
#define TERRAIN_SIZE (TERRAIN_ROWS * TERRAIN_COLS)

static int terrain_map[TERRAIN_SIZE] = {
    1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1, 3, 1, 2, 2, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

static void render_terrain(cr_app *app, cr_entity *terrain)
{
    for (int i = 0; i < TERRAIN_SIZE; i++)
    {
        int x = terrain->x_pos + (i % TERRAIN_COLS) * 16 + app->cam.x;
        int y = terrain->y_pos + (i / TERRAIN_COLS) * 16 + app->cam.y;
        cr_rect rect = {.x = x, .y = y, .w = 16, .h = 16};

        if (util_is_rect_on_screen(app, &rect))
        {
            sprite_draw_terrain(
                app,
                x,
                y,
                terrain_map[i]);
        }
    }
}

void tort_register_terrain(cr_entity_type *t)
{
    t->render = render_terrain;
}

cr_entity *tort_create_terrain(cr_app *app, int x, int y)
{
    cr_entity *terrain = NULL;

    terrain = cr_create_entity(app);
    if (terrain == NULL)
    {
        return NULL;
    }

    terrain->type = ENTITY_TYPE_TERRAIN;
    terrain->x_pos = x;
    terrain->y_pos = y;

    return terrain;
}