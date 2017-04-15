
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_EVENT_H
#define R_EVENT_H

#include <stdbool.h>
#include "Rithmomachie_Data.h"

bool souris_bouton_presse(int b);
bool souris_bouton_relache(int b);
int souris_x(void);
int souris_y(void);

void souris_set_event(ALLEGRO_EVENT *event);

void souris_tick(void);


#endif //R_EVENT_H

