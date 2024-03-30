#ifndef TORT_SIGN_INTERACTION_H
#define TORT_SIGN_INTERACTION_H

#include "tort.h"

void tort_register_sign_interaction(cr_entity_type *);

cr_entity *tort_create_sign_interaction(cr_app *, int, int);

#endif