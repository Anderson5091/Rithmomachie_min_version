
/*
 *    RITHMOMACHIE - Created by Anderson5091 02/Avril/17.
 *
 *    .
 */
#ifndef R_PLAYER_H
#define R_PLAYER_H

#include "GUI.h"

typedef struct PLAYER{
    VIEW *Player_view;
    char *Name;
}PLAYER;

void void Init_Player(VIEW *view, int player, char *name);
void Afficher_Player(void);

#endif //R_PLAYER_H

