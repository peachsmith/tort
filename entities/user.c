#include "tort.h"
#include "entities/entity_types.h"
#include "entities/user.h"
#include "util/sprite.h"

#include "common/util.h"

#define USER_X_ACC_LIMIT 24
#define USER_Y_ACC_LIMIT 24

static int get_user_x_vel(cr_entity *user)
{
    // acceleration to velocity conversion table
    int a_to_v[USER_X_ACC_LIMIT] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1};

    // limit acceleration
    int acc = user->x_acc;
    if (acc >= USER_X_ACC_LIMIT)
    {
        acc = USER_X_ACC_LIMIT - 1;
    }
    if (acc <= -USER_X_ACC_LIMIT)
    {
        acc = -USER_X_ACC_LIMIT + 1;
    }

    int x_vel = 0;
    if (acc > 0)
    {
        x_vel = a_to_v[acc];
    }
    else if (acc < 0)
    {
        x_vel = -(a_to_v[-acc]);
    }

    if (user->x_t)
    {
        x_vel += user->x_t;
    }

    return x_vel;
}

static int get_user_y_vel(cr_entity *user)
{
    // acceleration to velocity conversion table
    int a_to_v[USER_X_ACC_LIMIT] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1};

    // limit acceleration
    int acc = user->y_acc;
    if (acc >= USER_Y_ACC_LIMIT)
    {
        acc = USER_Y_ACC_LIMIT - 1;
    }
    if (acc <= -USER_Y_ACC_LIMIT)
    {
        acc = -USER_Y_ACC_LIMIT + 1;
    }

    int y_vel = 0;
    if (acc > 0)
    {
        y_vel = a_to_v[acc];
    }
    else if (acc < 0)
    {
        y_vel = -(a_to_v[-acc]);
    }

    if (user->y_t)
    {
        y_vel += user->y_t;
    }

    return y_vel;
}

static void render_user(cr_app *app, cr_entity *user)
{
    int tile = 0;
    int mirror = 0;

    int left_pressed = cr_peek_input(app, CR_KEYCODE_LEFT) && app->input_count == 2;
    int right_pressed = cr_peek_input(app, CR_KEYCODE_RIGHT) && app->input_count == 2;
    int up_pressed = cr_peek_input(app, CR_KEYCODE_UP) && app->input_count == 2;
    int down_pressed = cr_peek_input(app, CR_KEYCODE_DOWN) && app->input_count == 2;

    switch (user->cursor_y)
    {
    case 1:
        tile = 0;
        break;
    case 2:
        tile = 2;
        break;
    case 3:
        tile = 4;
        break;
    case 4:
        tile = 4;
        mirror = 1;
        break;
    default:
        tile = 0;
        break;
    }

    // animation logic
    if (down_pressed || up_pressed)
    {
        if (user->animation_ticks > 30)
        {
            tile = 0 + (2 * up_pressed);
            mirror = 0;
        }
        else if (user->animation_ticks > 20)
        {
            tile = 1 + (2 * up_pressed);
            mirror = 1;
        }
        else if (user->animation_ticks > 10)
        {
            tile = 0 + (2 * up_pressed);
            mirror = 0;
        }
        else
        {
            tile = 1 + (2 * up_pressed);
            mirror = 0;
        }
    }
    else if (left_pressed || right_pressed)
    {
        if (user->animation_ticks > 10)
        {
            tile = 4;
            mirror = right_pressed;
        }
        else
        {
            tile = 5;
            mirror = right_pressed;
        }
    }

    sprite_draw_user(
        app,
        user->x_pos,
        user->y_pos,
        mirror,
        tile);

    // hit box
    if (app->debug.hitboxes)
    {
        cr_rect hit_box;
        hit_box.x = user->x_pos;
        hit_box.y = user->y_pos;
        hit_box.w = app->entity_types[user->type].width;
        hit_box.h = app->entity_types[user->type].height;

        // Render the user hit box.
        cr_set_color(app, CR_COLOR_VINIK_PURPLE);
        cr_draw_rect(app, &hit_box, 0);
    }
}

static void update_user(cr_app *app, cr_entity *user)
{
    // Get the width and height of the user.
    int w = app->entity_types[user->type].width;
    int h = app->entity_types[user->type].height;

    // input checks
    // When the user has control over this entity, there should be two
    // input handlers.
    int has_control = app->input_count == 2;
    int left_pressed = cr_peek_input(app, CR_KEYCODE_LEFT) && has_control;
    int right_pressed = cr_peek_input(app, CR_KEYCODE_RIGHT) && has_control;
    int up_pressed = cr_peek_input(app, CR_KEYCODE_UP) && has_control;
    int down_pressed = cr_peek_input(app, CR_KEYCODE_DOWN) && has_control;

    int avx = get_user_x_vel(user);
    int avy = get_user_y_vel(user);

    //--------------------------------------------------------------------
    // Horizontal Movement

    // horizontal correction factor applied by collision with a solid object
    if (user->x_t)
    {
        user->x_acc = 0;
        user->x_t = 0;
    }

    // Update horizontal position.
    // user->x_pos += avx;
    if (app->cam.config == CR_CAMERA_ALL &&
        user->x_pos + w >= app->cam.cr &&
        avx > 0 && !(app->ticks % 2))
    {
        int dcam = (user->x_pos + w) - app->cam.cr;
        user->x_pos = app->cam.cr - w;
        app->cam.x -= avx;
        app->cam.x -= dcam;
    }
    else if (app->cam.config == CR_CAMERA_ALL &&
             user->x_pos <= app->cam.cl + 1 &&
             avx < 0 && !(app->ticks % 2))
    {
        int dcam = user->x_pos - (app->cam.cl + 1);
        user->x_pos = app->cam.cl + 1;
        app->cam.x -= avx;
        app->cam.x -= dcam;
    }
    else if (!(app->ticks % 2))
    {
        user->x_pos += avx;
    }

    // Perform horizontal inertia.
    if (user->x_acc > 0 && (!right_pressed))
    {
        user->x_acc--;
    }

    if (user->x_acc < 0 && (!left_pressed))
    {
        user->x_acc++;
    }

    //--------------------------------------------------------------------
    // Vertical Movement

    // vertical correction factor applied by collision with a solid object
    if (user->y_t)
    {
        user->y_acc = 0;
        user->y_t = 0;
    }

    // user->y_pos += avy;
    if (app->cam.config == CR_CAMERA_ALL &&
        user->y_pos + h >= app->cam.cb &&
        avy > 0 && !(app->ticks % 2))
    {
        int dcam = (user->y_pos + h) - app->cam.cb;
        user->y_pos = app->cam.cb - h;
        app->cam.y -= avy;
        app->cam.y -= dcam;
    }
    else if (app->cam.config == CR_CAMERA_ALL &&
             user->y_pos <= app->cam.ct + 1 &&
             avy < 0 && !(app->ticks % 2))
    {
        int dcam = user->y_pos - (app->cam.ct + 1);
        user->y_pos = app->cam.ct + 1;
        app->cam.y -= avy;
        app->cam.y -= dcam;
    }
    else if (!(app->ticks % 2))
    {
        user->y_pos += avy;
    }

    // Perform veritcal inertia.
    if (user->y_acc > 0 && (!down_pressed))
    {
        user->y_acc--;
    }

    if (user->y_acc < 0 && (!up_pressed))
    {
        user->y_acc++;
    }

    //--------------------------------------------------------------------
    // Behavior Logic

    user->ticks++;

    if (user->cursor_x)
    {
        user->animation_ticks++;

        // up and down walking
        if (user->cursor_x < 3 && user->animation_ticks >= 40)
        {
            user->animation_ticks = 0;
        }

        // left and right walking
        if (user->cursor_x >= 3 && user->animation_ticks >= 20)
        {
            user->animation_ticks = 0;
        }
    }
}

void tort_register_user(cr_entity_type *t)
{
    t->width = 16;
    t->height = 16;
    t->render = render_user;
    t->update = update_user;
    t->get_x_vel = get_user_x_vel;
    t->get_y_vel = get_user_y_vel;
    t->control = 1;
}

cr_entity *tort_create_user(cr_app *app, int x, int y)
{
    cr_entity *user = NULL;

    user = cr_create_entity(app);
    if (user == NULL)
    {
        return NULL;
    }

    user->type = ENTITY_TYPE_USER;
    user->x_pos = x;
    user->y_pos = y;
    user->cursor_x = 0; // current animation
    user->cursor_y = 0; // most recent animation (which direction to face)

    return user;
}