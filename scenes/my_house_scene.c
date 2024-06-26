#include "tort.h"
#include "input/input.h"
#include "scenes/scenes.h"
#include "entities/transition.h"
#include "entities/user.h"
#include "entities/my_house_map.h"
#include "entities/sign_interaction.h"
#include "entities/sign_dialog.h"
#include "entities/block.h"

#include "common/util.h"

void tort_load_my_house_scene(cr_app *app)
{
    cr_entity **handles = app->extension->entity_handles;

    app->scene = TORT_SCENE_MY_HOUSE;

    util_set_camera(app, CR_CAMERA_ALL);
    int x_offset = (16 * 0);
    int y_offset = (16 * 0);
    app->cam.x = -x_offset;
    app->cam.y = -y_offset;

    // menus
    // TODO

    // dialogs

    // scene transition
    handles[TORT_HANDLE_TRANSITION] = tort_create_transition(app);

    // contents
    tort_create_my_house_map(app, 64, 35);

    // trigger to transition to noodletown
    tort_create_transition_block(app, 112 + x_offset, 90 + y_offset, TORT_SCENE_NOODLETOWN);

    // user
    app->extension->entity_handles[TORT_HANDLE_USER] = tort_create_user(app, 112, 73);
}
