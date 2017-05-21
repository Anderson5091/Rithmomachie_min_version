
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_GUI_H
#define R_GUI_H

#include "Rithmomachie_Data.h"
typedef enum B_ETAT{
    B_Normal,
    B_Actif,
    B_Survol,
} B_ETAT;

typedef struct BOUTON {
    float X, Y, W, H;
    B_ETAT Etat;
    ALLEGRO_BITMAP *Image;
    void (*Action)(void);
} BOUTON;

BOUTON *Creer_bouton(float x, float y, ALLEGRO_BITMAP *image, void *action);
void Actualiser_bouton(BOUTON *bouton);
void Afficher_bouton(BOUTON *bouton);
void Detruire_bouton(BOUTON *bouton);

#endif //R_GUI_H

