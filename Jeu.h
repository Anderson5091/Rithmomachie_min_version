
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_JEU_H
#define R_JEU_H

#include "Rithmomachie_Data.h"
#include "GUI.h"

typedef struct JOUEUR{
    AFFICHAGE *Joueur_aff;
    char *Name;
}JOUEUR;

void Init_affichage_jeu(void);

void Init_joueur(AFFICHAGE *affichage, int joueur, char *name);
void Afficher_joueur(int joueur);
static void Afficher_jeu(void);

#endif //R_JEU_H
