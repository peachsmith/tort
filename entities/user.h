#ifndef TORT_USER_H
#define TORT_USER_H

#include "tort.h"

void tort_register_user(cr_entity_type *);

cr_entity *tort_create_user(cr_app *, int, int);

#endif