#include "tort.h"
#include "input/input.h"
#include "scenes/scenes.h"
#include "entities/transition.h"
#include "entities/user.h"

#include "common/util.h"
#include "common/collision.h"

void tort_main_input(cr_app *app)
{
    if (cr_consume_input(app, CR_KEYCODE_ESCAPE))
    {
        app->done = 1;
    }

    // Locate the player entity.
    cr_entity *target = app->extension->entity_handles[TORT_HANDLE_USER];
    if (target == NULL)
    {
        return;
    }

    int max_walk = 6;
    int min_walk = 1;
    int walk_acc = 1;

    target->cursor_x = 0;

    // left movement
    if (cr_peek_input(app, CR_KEYCODE_LEFT))
    {
        target->cursor_x = 3;
        target->cursor_y = TORT_DIR_LEFT;

        if (!app->actuation_counters[CR_KEYCODE_LEFT])
        {
            target->animation_ticks = 0;
        }

        if (app->actuation_counters[CR_KEYCODE_LEFT] < 10)
        {
            app->actuation_counters[CR_KEYCODE_LEFT]++;
        }

        if (target->x_acc > -min_walk)
        {
            if (target->x_acc < min_walk)
            {
                target->x_acc = -min_walk;
            }
        }
        else
        {
            target->x_acc -= walk_acc;
        }

        if (target->x_acc < -max_walk)
        {
            target->x_acc = -max_walk;
        }
    }
    else
    {
        app->actuation_counters[CR_KEYCODE_LEFT] = 0;
    }

    // right movement
    if (cr_peek_input(app, CR_KEYCODE_RIGHT))
    {
        target->cursor_x = 4;
        target->cursor_y = TORT_DIR_RIGHT;

        if (!app->actuation_counters[CR_KEYCODE_RIGHT])
        {
            target->animation_ticks = 0;
        }

        if (app->actuation_counters[CR_KEYCODE_RIGHT] < 10)
        {
            app->actuation_counters[CR_KEYCODE_RIGHT]++;
        }

        if (target->x_acc < min_walk)
        {
            if (target->x_acc > -min_walk)
            {
                target->x_acc = min_walk;
            }
        }
        else
        {
            target->x_acc += walk_acc;
        }

        if (target->x_acc > max_walk)
        {
            target->x_acc = max_walk;
        }
    }
    else
    {
        app->actuation_counters[CR_KEYCODE_RIGHT] = 0;
    }

    // up movement
    if (cr_peek_input(app, CR_KEYCODE_UP))
    {
        target->cursor_x = 2;
        target->cursor_y = TORT_DIR_UP;

        if (!app->actuation_counters[CR_KEYCODE_UP])
        {
            target->animation_ticks = 0;
        }

        if (app->actuation_counters[CR_KEYCODE_UP] < 10)
        {
            app->actuation_counters[CR_KEYCODE_UP]++;
        }

        if (target->y_acc > -min_walk)
        {
            if (target->y_acc < min_walk)
            {
                target->y_acc = -min_walk;
            }
        }
        else
        {
            target->y_acc -= walk_acc;
        }

        if (target->y_acc < -max_walk)
        {
            target->y_acc = -max_walk;
        }
    }
    else
    {
        app->actuation_counters[CR_KEYCODE_UP] = 0;
    }

    // down movement
    if (cr_peek_input(app, CR_KEYCODE_DOWN))
    {
        target->cursor_x = 1;
        target->cursor_y = TORT_DIR_DOWN;

        if (!app->actuation_counters[CR_KEYCODE_DOWN])
        {
            target->animation_ticks = 0;
        }

        if (app->actuation_counters[CR_KEYCODE_DOWN] < 10)
        {
            app->actuation_counters[CR_KEYCODE_DOWN]++;
        }

        if (target->y_acc < min_walk)
        {
            if (target->y_acc > -min_walk)
            {
                target->y_acc = min_walk;
            }
        }
        else
        {
            target->y_acc += walk_acc;
        }

        if (target->y_acc > max_walk)
        {
            target->y_acc = max_walk;
        }
    }
    else
    {
        app->actuation_counters[CR_KEYCODE_DOWN] = 0;
    }

    if (cr_consume_input(app, CR_KEYCODE_Z))
    {
        int int_dir = 0;

        // Scan for interactable entities.
        cr_entity *interactable = NULL;
        for (int i = 0; i < app->entity_cap && interactable == NULL; i++)
        {
            if (app->entity_types[app->entities[i].type].interactable && app->entities[i].present)
            {
                // Check for overlap with the interactable entity.
                cr_rect a = {.x = target->x_pos,
                             .y = target->y_pos,
                             .w = app->entity_types[target->type].width,
                             .h = app->entity_types[target->type].height};

                cr_rect b = {.x = app->entities[i].x_pos + app->cam.x,
                             .y = app->entities[i].y_pos + app->cam.y,
                             .w = app->entity_types[app->entities[i].type].width,
                             .h = app->entity_types[app->entities[i].type].height};
                cr_overlap o;

                if (common_is_overlapped(&a, &b, &o))
                {
                    interactable = &(app->entities[i]);

                    // Determine if the user is facing the correct direction for interaction.
                    int int_dir_x = o.dx0 < o.dx1 ? TORT_DIR_LEFT : TORT_DIR_RIGHT;
                    int int_dir_y = o.dy0 < o.dy1 ? TORT_DIR_UP : TORT_DIR_DOWN;
                    int min_ox = o.dx0 < o.dx1 ? o.dx0 : o.dx1;
                    int min_oy = o.dy0 < o.dy1 ? o.dy0 : o.dy1;
                    int_dir = min_ox < min_oy ? int_dir_x : int_dir_y;
                }
            }
        }

        if (interactable != NULL)
        {
            if (
                int_dir == TORT_DIR_LEFT && target->cursor_y == TORT_DIR_RIGHT ||
                int_dir == TORT_DIR_RIGHT && target->cursor_y == TORT_DIR_LEFT ||
                int_dir == TORT_DIR_DOWN && target->cursor_y == TORT_DIR_UP ||
                int_dir == TORT_DIR_UP && target->cursor_y == TORT_DIR_DOWN)
            {
                app->entity_types[interactable->type].interact(app, interactable, target);
            }
        }
    }

    //-------------------------------------------------
    // BEGIN debug controls

    if (cr_consume_input(app, CR_KEYCODE_LEFTBRACKET))
    {
        app->debug.hitboxes = app->debug.hitboxes ? 0 : 1;
    }

    if (cr_consume_input(app, CR_KEYCODE_RIGHTBRACKET))
    {
        app->debug.camera = app->debug.camera ? 0 : 1;
    }

    // END debug controls
    //-------------------------------------------------
}