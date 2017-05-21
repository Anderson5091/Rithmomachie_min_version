
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */


#ifndef R_DATA_H
#define R_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define R_ACTIVITE_CHARGEMENT               0
#define R_ACTIVITE_MENU_PRINCIPAL           1
#define R_ACTIVITE_MENU_JOUER               2
#define R_ACTIVITE_MENU_OPTIONS             3
#define R_ACTIVITE_QUITTER                  4

#define R_ACTIVITE_JEU_NOUVEAU_JEU          5
#define R_ACTIVITE_JEU_ENCOURS              6
#define R_ACTIVITE_JEU_REPRENDRE            7
#define R_ACTIVITE_JEU_EN_PAUSE             8
#define R_ACTIVITE_JEU_OPTIONS              9
#define R_ACTIVITE_JEU_PYRAMIDE_REF         10
#define R_ACTIVITE_JEU_PARTIE_TERMINER      11

#define TABLIER_LIGNE_MAX   16
#define TABLIER_COLONNE_MAX 8
#define PLATEAU_LIGNE_MAX   3
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
extern COORDPOINT centre_ecran;

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY_MODE mode;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_BITMAP *icone, *Fond, *Buffer;
extern int framerate , chrono, nbmode, reafficher, activite_encours;
extern double duree;
extern double progression;

void erreur( const char*txt);

void Set_progress(double d, double p);
void Reset_progress(void);

void (*Actualiser_activite)(void);
void Config_activite(int activite);

#endif //R_DATA_H
