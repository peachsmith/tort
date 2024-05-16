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
    app->cam.x = 0;
    app->cam.y = 0;

    // menus
    // TODO

    // dialogs
    tort_create_sign_dialog(app);

    // scene transition
    handles[TORT_HANDLE_TRANSITION] = tort_create_transition(app);

    // contents
    tort_create_noodletown_map(app, 0, 0);
    tort_create_sign_interaction(app, 80, 48);
    tort_create_small_block(app, 81, 49);

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
