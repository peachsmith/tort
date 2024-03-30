#ifndef TORT_SIGN_DIALOG_H
#define TORT_SIGN_DIALOG_H

#include "tort.h"

void tort_register_sign_dialog(cr_entity_type *);
cr_entity *tort_create_sign_dialog(cr_app *);
void tort_open_sign_dialog(cr_app *, cr_entity *);

#endif