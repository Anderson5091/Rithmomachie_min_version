
/*
 *    RITHMOMACHIE - Created by Anderson5091 16/Avril/17.
 *
 *    .
 */

#include "Rithmomachie_Data.h"

#ifndef R_MOYEU_H
#define R_MOYEU_H

#include "GUI.h"
#include"Piece.h"

typedef struct JOUEUR{
    int   Id;
    char *Name;
    ALLEGRO_BITMAP* Image;
    PYRAMIDE *Pyramide;
}JOUEUR;

typedef struct MOYEU{
    float X;
    float Y;
    JOUEUR  *Joueur;
    BOUTON  *Boutons[6];
    PIECE   *Plateau[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];

}MOYEU;

extern MOYEU Moyeux[JOUEUR_MAX];
extern JOUEUR *joueur_actuel;

JOUEUR* Trouver_joueur(int id);
void Changer_joueur(void);
void Init_joueur(JOUEUR *joueur,PYRAMIDE *pyramide);
void Init_moyeu(JOUEUR *joueur, float dx, float dy);
void Actualiser_moyeux(void);

void moyeu_bouton_action(void);
void Init_moyeu_boutons(MOYEU* moyeu);
void Re_init_moyeu_boutons(MOYEU* moyeu);
void Actualier_moyeux_boutons(void);
void Detruire_moyeu_boutons(MOYEU *moyeu);
void Detruire_moyeux_boutons(void);

void Retirer_piece_dans_moyeu_plateau(PIECE* piece, MOYEU* moyeu);
void Afficher_moyeux_plateau(void);
void Actualiser_moyeux_plateau(void);
#endif //R_MOYEU_H
