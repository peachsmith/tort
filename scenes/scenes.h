#ifndef TORT_SCENES_H
#define TORT_SCENES_H

#include "tort.h"

// scenes
#define TORT_SCENE_NOODLETOWN 0

void tort_clear_scene(cr_app *);

// scene loaders
void tort_load_noodletown_scene(cr_app *);

// scene behavior
void tort_perform_noodletown(cr_app *);

#endif