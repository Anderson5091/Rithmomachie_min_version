
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_GUI_H
#define R_GUI_H

#include "Rithmomachie_Data.h"

typedef enum B_ETAT{
    Normal,
    Survol,
} B_ETAT;

typedef struct BOUTON {
    float X, Y;
    B_ETAT Etat;
    ALLEGRO_BITMAP *Main;
    void (*Action)(void);
} BOUTON;

typedef struct AFFICHAGE{
    char *Name;
    struct AFFICHAGE *Parent;
    ALLEGRO_BITMAP * Bmp;
    int W;
    int H;
    int X;
    int Y;
}AFFICHAGE;

BOUTON *Init_bouton(float x, float y, ALLEGRO_BITMAP *main);
void Afficher_bouton(BOUTON *bouton);
void Detruire_bouton(BOUTON *bouton);

AFFICHAGE * Init_affichage(char *name, AFFICHAGE *parent, int x, int y, int l, int h);
void Afficher_affichage(AFFICHAGE *affichage);
void Detruire_affichage(AFFICHAGE *affichage);


#endif //R_GUI_H

