#ifndef TORT_SCENES_H
#define TORT_SCENES_H

#include "tort.h"

// scenes
#define TORT_SCENE_NOODLETOWN 0
#define TORT_SCENE_MY_HOUSE 1

void tort_clear_scene(cr_app *);

// scene loaders
void tort_load_noodletown_scene(cr_app *);
void tort_load_my_house_scene(cr_app *);

// scene behavior
void tort_perform_noodletown(cr_app *);

#endif