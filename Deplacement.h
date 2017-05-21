
/*
 *    RITHMOMACHIE - Created by Anderson5091 10/Avril/17.
 *
 *    .
 */

#ifndef R_DEPLACEMENT_H
#define R_DEPLACEMENT_H

#include"Moyeu.h"
#include "Rithmomachie_Data.h"


bool Isset_deplacer_de_case(void);
bool Isset_deplacer_vers_case(void);
bool Isset_deplacer_de_moyeux(void);
bool Isset_deplacement(void);
bool Is_chemin_libre(CASE *de_case, int i);

void Set_deplacement(void);
void Set_deplacer_de_case(CASE* cs);
void Set_deplacer_vers_case(CASE* cs);
void Set_deplacer_de_moyeux(PIECE* piece);
void Reset_deplacement(void);

CASE* Deplacer_vers_case(void);
CASE* Deplacer_de_case(void);
PIECE* Deplacer_de_moyeux(void);

void Deplacer_piece_dans_tablier(CASE *de_case, CASE* vers_case);
void Deplacer_piece_vers_tablier(PIECE* piece, MOYEU* moyeu, CASE* vers_case);
void Deplacer_pyramide_dans_tablier(CASE *de_case, CASE* vers_case);
void Deplacer_piece_vers_moyeu_plateau(PIECE* piece, int joueur_id);
void Lancer_deplacement(CASE* de_case,CASE* vers_case );
void GUX_deplacement_possible(CASE* cs);
void GUX_remplacement_possible(CASE cs);
#endif //R_DEPLACEMENT_H
