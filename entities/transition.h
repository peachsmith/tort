#ifndef TORT_TRANSITION_H
#define TORT_TRANSITION_H

#include "tort.h"

void tort_register_transition(cr_entity_type *);
cr_entity *tort_create_transition(cr_app *);

void tort_register_house_transition(cr_entity_type *);
cr_entity *tort_create_house_transition(cr_app *);

#endif