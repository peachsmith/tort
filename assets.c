#include "assets.h"

#include <stdio.h>
#include <stdlib.h>

int tort_load_all_assets(cr_app *app)
{
    // images
    if (cr_load_texture(app, "sprite-sheet.png") == NULL)
    {
        fprintf(stderr, "failed to load sprite sheet\n");
        return 0;
    }

    // fonts
    if (cr_load_font(app, "pokemon_fire_red.ttf", 16) == NULL)
    {
        fprintf(stderr, "failed to load pokemon_fire_red font\n");
        return 0;
    }

    // sounds

    return 1;
}
