#ifndef TORT_TERRAIN_H
#define TORT_TERRAIN_H

#include "tort.h"

void tort_register_terrain(cr_entity_type *);

cr_entity *tort_create_terrain(cr_app *, int, int);

#endif