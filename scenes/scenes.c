#include "tort.h"
#include "scenes/scenes.h"

void tort_clear_scene(cr_app *app)
{
    for (int i = 0; i < app->entity_cap; i++)
    {
        app->entities[i].present = 0;
    }

    for (int i = 0; i < TORT_MAX_ENTITY_HANDLES; i++)
    {
        app->extension->entity_handles[i] = NULL;
    }

    app->entity_count = 0;
    app->menu_count = 0;
    app->dialog_count = 0;
    app->overlay_count = 0;
}
