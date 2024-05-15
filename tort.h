#ifndef TORT_H
#define TORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <crumbs/crumbs.h>

// image assets
#define TORT_TEXTURE_SPRITES 0

// font assets
#define TORT_FONT_POKEMON_FIRE_RED 0

// audio assets

// counters
#define TORT_COUNTER_MAX 20

// entity handles
#define TORT_HANDLE_USER 0
#define TORT_HANDLE_TRANSITION 1
#define TORT_MAX_ENTITY_HANDLES 10

// limits
#define TORT_MAX_ENTITIES 256
#define TORT_MAX_INPUT_HANDLERS 20
#define TORT_MAX_MENUS 10
#define TORT_MAX_DIALOGS 10
#define TORT_MAX_OVERLAYS 10
#define TORT_MAX_TEXTURES 10
#define TORT_MAX_FONTS 10
#define TORT_MAX_SOUNDS 10

// directions that entities can face
#define TORT_DIR_DOWN 1
#define TORT_DIR_UP 2
#define TORT_DIR_LEFT 3
#define TORT_DIR_RIGHT 4

// extension structure definition
struct cr_extension
{
    cr_entity **entity_handles;
    int *counters;
};

/**
 * Populates am app struct with the data needed for runtime.
 *
 * Params:
 *   cr_app* - a pointer to an app struct
 *
 * Returns:
 *   int - 1 on success or 0 on failure
 */
int tort_init_app(cr_app *);

#endif