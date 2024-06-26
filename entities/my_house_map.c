#include "tort.h"
#include "assets.h"
#include "entities/entity_types.h"
#include "entities/my_house_map.h"
#include "util/sprite.h"

#include "common/util.h"

static int map_rows = 0;
static int map_cols = 0;
static int map_size = 0;
static int *map_data = NULL;

static void render_my_house_map(cr_app *app, cr_entity *map_entity)
{
    for (int i = 0; i < map_size; i++)
    {
        int x = map_entity->x_pos + (i % map_cols) * 16 + app->cam.x;
        int y = map_entity->y_pos + (i / map_cols) * 16 + app->cam.y;
        cr_rect rect = {.x = x, .y = y, .w = 16, .h = 16};

        if (util_is_rect_on_screen(app, &rect))
        {
            sprite_draw_terrain(
                app,
                x,
                y,
                map_data[i]);
        }
    }
}

void tort_register_my_house_map(cr_entity_type *t)
{
    t->render = render_my_house_map;
}

cr_entity *tort_create_my_house_map(cr_app *app, int x, int y)
{
    cr_entity *my_house_map = NULL;

    my_house_map = cr_create_entity(app);
    if (my_house_map == NULL)
    {
        return NULL;
    }

    my_house_map->type = ENTITY_TYPE_MY_HOUSE_MAP;
    my_house_map->x_pos = x;
    my_house_map->y_pos = y;

    if (map_data == NULL)
    {
        map_data = load_map("my_house.map", &map_rows, &map_cols);
        map_size = map_rows * map_cols;
    }

    return my_house_map;
}