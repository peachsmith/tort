#ifndef TORT_BLOCK_H
#define TORT_BLOCK_H

#include "tort.h"

// register and create functions for a square block the size of one tile
void tort_register_tile_block(cr_entity_type *);
cr_entity *tort_create_tile_block(cr_app *, int, int);

// small, square block slightly smaller than one tile
void tort_register_small_block(cr_entity_type *);
cr_entity *tort_create_small_block(cr_app *, int, int);

// slightly thinner than one tile wide
void tort_register_narrow_tile_block(cr_entity_type *);
cr_entity *tort_create_narrow_tile_block(cr_app *, int, int);

// collision triggers a scene transition
void tort_register_transition_block(cr_entity_type *);
cr_entity *tort_create_transition_block(cr_app *, int, int);

// long, rectangular blocks
void tort_register_horizontal_block(cr_entity_type *);
cr_entity *tort_create_horizontal_block(cr_app *, int, int);
void tort_register_vertical_block(cr_entity_type *);
cr_entity *tort_create_vertical_block(cr_app *, int, int);

#endif