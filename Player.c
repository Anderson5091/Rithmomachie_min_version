
/*
 *    RITHMOMACHIE - Created by Anderson5091 02/Avril/17.
 *
 *    .
 */
#include "Player.h"


static PLAYER Player[MAX_PLAYER];

void Init_Player(View *view, int player, char *name)
{
    Player[player].Player_view = view;
    Player[player].Name=name;
}

void Afficher_Player()
{

}

