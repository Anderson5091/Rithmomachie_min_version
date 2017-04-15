
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_DATA_H
#define R_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define ECHIQUIER_LIGNE_MAX   16
#define ECHIQUIER_COLONNE_MAX 8
#define PLATEAU_LIGNE_MAX   4
#define PLATEAU_COLONNE_MAX 12

#define DIM_CASE    40
#define DIM_PIECE   28
#define JOUEUR_MAX  2
#define Joueur_1    0
#define Joueur_2    1

typedef struct COORDPOINT
{
    float X;
    float Y;

}COORDPOINT;

extern float largeur_ecran;
extern float hauteur_ecran;
extern ALLEGRO_BITMAP *Fond;
extern ALLEGRO_BITMAP *Buffer;
extern COORDPOINT centre_ecran;
extern ALLEGRO_DISPLAY* display;
extern int reafficher;

void R_chargement(void);
//extern CASE Echiquier[ECHIQUIER_LIGNE_MAX][ECHIQUIER_COLONNE_MAX];
//extern CASE *pointer_sur_case, *pointer_vers_case;

//extern PIECE* Plateau_1[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];
//extern PIECE* Plateau_2[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];
//extern PIECE *adresse_de_plateau, *adresse_vers_plateau;

#endif //R_DATA_H
