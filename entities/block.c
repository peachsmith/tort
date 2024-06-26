#include "tort.h"
#include "input/input.h"
#include "scenes/scenes.h"
#include "entities/entity_types.h"
#include "entities/block.h"
#include "util/sprite.h"

#include "common/util.h"
#include "common/collision.h"

static void begin_transition(cr_app *app, cr_func loader, cr_func input)
{
    app->transition_loader = loader;
    app->transition_input = input;

    // Start the screen transition by marking the data field as 1 for any
    // entity that has an entity type of ENTITY_TYPE_TRANSITION.
    for (int i = 0; i < app->entity_cap; i++)
    {
        if (app->entities[i].type == ENTITY_TYPE_TRANSITION && app->entities[i].present)
        {
            app->entities[i].data = 1 | TX_RESUME;
            app->overlays[app->overlay_count++] = &(app->entities[i]);
        }
    }
}

static void collide_block(
    cr_app *app,
    cr_entity *block,
    cr_entity *other,
    cr_collision *t_res)
{
    // The collision resolution correction factor formula is pulled from
    // the video at https://www.youtube.com/watch?v=8JJ-4JgR7Dg.

    // Clear the jump flag and set the ground flag.
    // Only do this if the entity collided with the block from above.
    // if (t_res->cn.y < 0 && !t_res->cn.x)
    // {
    //     cr_clear_flag(other, ENTITY_FLAG_JUMP);
    //     cr_set_flag(other, ENTITY_FLAG_GROUND);
    // }

    // Correction factor.
    float t1 = 1 - t_res->t;

    if (t_res->cn.x)
    {
        int avx = app->entity_types[other->type].get_x_vel(other);
        int absx = avx > 0 ? avx : -(avx);
        float correction = t_res->cn.x * absx * t1;

        // Account for rounding.
        if (correction < 0)
        {
            correction -= 0.5f;
        }
        else if (correction > 0)
        {
            correction += 0.5f;
        }

        other->x_t += (int)correction;
    }

    if (t_res->cn.y)
    {
        // Correction factor for landing on top of the block.
        int avy = app->entity_types[other->type].get_y_vel(other);
        int absy = avy > 0 ? avy : -(avy);
        float correction = t_res->cn.y * absy * t1;

        // Account for rounding.
        if (correction < 0)
        {
            correction -= 0.5f;
        }
        else if (correction > 0)
        {
            correction += 0.5f;
        }

        other->y_t += (int)correction;
    }

    if (block->type == ENTITY_TYPE_TRANSITION_BLOCK)
    {
        app->pause = 1;
        cr_pop_input_handler(app);
        begin_transition(app, tort_load_my_house_scene, tort_main_input);
        printf("collided with transition block\n");
    }
}

static void render_block(cr_app *app, cr_entity *block)
{
    if (!util_is_on_screen(app, block))
    {
        return;
    }

    // hit box
    if (app->debug.hitboxes)
    {
        cr_rect hit_box;
        hit_box.x = block->x_pos + app->cam.x;
        hit_box.y = block->y_pos + app->cam.y;
        hit_box.w = app->entity_types[block->type].width;
        hit_box.h = app->entity_types[block->type].height;

        cr_set_color(app, CR_COLOR_VINIK_LIGHT_BLUE);
        cr_draw_rect(app, &hit_box, 0);
    }
}

static void render_transition_block(cr_app *app, cr_entity *block)
{
    if (!util_is_on_screen(app, block))
    {
        return;
    }

    // hit box
    if (app->debug.hitboxes)
    {
        cr_rect hit_box;
        hit_box.x = block->x_pos + app->cam.x;
        hit_box.y = block->y_pos + app->cam.y;
        hit_box.w = app->entity_types[block->type].width;
        hit_box.h = app->entity_types[block->type].height;

        cr_set_color(app, CR_COLOR_VINIK_ORANGE);
        cr_draw_rect(app, &hit_box, 0);
    }
}

void tort_register_tile_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_TILE_BLOCK;
    t->width = 16;
    t->height = 16;
    t->render = render_block;
    t->collide = collide_block;
}

cr_entity *tort_create_tile_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_TILE_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}

void tort_register_narrow_tile_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_NARROW_BLOCK;
    t->width = 15;
    t->height = 16;
    t->render = render_block;
    t->collide = collide_block;
}

cr_entity *tort_create_narrow_tile_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_NARROW_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}

void tort_register_transition_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_TRANSITION_BLOCK;
    t->width = 18;
    t->height = 10;
    t->render = render_transition_block;
    t->collide = collide_block;
}

cr_entity *tort_create_transition_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_TRANSITION_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}

void tort_register_small_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_SMALL_BLOCK;
    t->width = 14;
    t->height = 14;
    t->render = render_block;
    t->collide = collide_block;
}

cr_entity *tort_create_small_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_SMALL_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}

void tort_register_horizontal_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_HORIZONTAL_BLOCK;
    t->width = 64;
    t->height = 16;
    t->render = render_block;
    t->collide = collide_block;
}

cr_entity *tort_create_horizontal_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_HORIZONTAL_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}

void tort_register_vertical_block(cr_entity_type *t)
{
    t->id = ENTITY_TYPE_VERTICAL_BLOCK;
    t->width = 16;
    t->height = 64;
    t->render = render_block;
    t->collide = collide_block;
}

cr_entity *tort_create_vertical_block(cr_app *app, int x, int y)
{
    cr_entity *block = NULL;

    block = cr_create_entity(app);
    if (block == NULL)
    {
        return NULL;
    }

    block->type = ENTITY_TYPE_VERTICAL_BLOCK;
    block->x_pos = x;
    block->y_pos = y;

    return block;
}