#include "tort.h"
#include "input/input.h"
#include "scenes/scenes.h"
#include "entities/transition.h"
#include "entities/user.h"
#include "entities/noodletown_map.h"
#include "entities/sign_interaction.h"
#include "entities/sign_dialog.h"
#include "entities/block.h"

#include "common/util.h"

void tort_load_noodletown_scene(cr_app *app)
{
    cr_entity **handles = app->extension->entity_handles;

    app->scene = TORT_SCENE_NOODLETOWN;

    util_set_camera(app, CR_CAMERA_ALL);
    int x_offset = (16 * 4);
    int y_offset = (16 * 0);
    app->cam.x = -x_offset;
    app->cam.y = -y_offset;

    // menus
    // TODO

    // dialogs
    tort_create_sign_dialog(app);

    // scene transition
    handles[TORT_HANDLE_TRANSITION] = tort_create_transition(app);

    // contents
    tort_create_noodletown_map(app, 0, 0);
    tort_create_sign_interaction(app, 80 + x_offset, 48 + y_offset);
    tort_create_small_block(app, 81 + x_offset, 49 + y_offset);

    // boundaries
    tort_create_vertical_block(app, -16 + x_offset, -32 + y_offset);
    tort_create_vertical_block(app, -16 + x_offset, 32 + y_offset);
    tort_create_vertical_block(app, -16 + x_offset, 96 + y_offset);

    // house boundaries
    tort_create_tile_block(app, 160 + x_offset, 0 + y_offset);
    tort_create_tile_block(app, 176 + x_offset, 0 + y_offset);
    tort_create_tile_block(app, 192 + x_offset, 0 + y_offset);
    tort_create_tile_block(app, 160 + x_offset, 16 + y_offset);
    tort_create_tile_block(app, 176 + x_offset, 16 + y_offset);
    tort_create_tile_block(app, 192 + x_offset, 16 + y_offset);

    tort_create_narrow_tile_block(app, 160 + x_offset, 32 + y_offset);
    tort_create_narrow_tile_block(app, 193 + x_offset, 32 + y_offset);

    // trigger to transition to my house
    tort_create_transition_block(app, 175 + x_offset, 32 + y_offset, TORT_SCENE_MY_HOUSE);

    tort_create_horizontal_block(app, x_offset, 160 + y_offset);
    tort_create_horizontal_block(app, 64 + x_offset, 160 + y_offset);
    tort_create_horizontal_block(app, 128 + x_offset, 160 + y_offset);
    tort_create_horizontal_block(app, 192 + x_offset, 160 + y_offset);

    // user
    app->extension->entity_handles[TORT_HANDLE_USER] = tort_create_user(app, 112, 64);
}

void tort_perform_noodletown(cr_app *app)
{
    if (app->pause)
    {
        return;
    }
}
