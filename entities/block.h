#ifndef TORT_BLOCK_H
#define TORT_BLOCK_H

#include "tort.h"

// register and create functions for a small, square block.
void tort_register_small_block(cr_entity_type *);
cr_entity *tort_create_small_block(cr_app *, int, int);

#endif