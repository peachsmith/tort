#ifndef TORT_UI_H
#define TORT_UI_H

#include "tort.h"

#define UI_INDICATOR_ADVANCE 1
#define UI_INDICATOR_SCROLL_UP 2
#define UI_INDICATOR_SCROLL_DOWN 3
#define UI_INDICATOR_SCROLL_LEFT 4
#define UI_INDICATOR_SCROLL_RIGHT 5

void ui_draw_panel(cr_app *, int, int, int, int);

void ui_draw_text(cr_app *);

void ui_draw_cursor(cr_app *, int, int);

void ui_draw_indicator(cr_app *, int, int, int);

#endif