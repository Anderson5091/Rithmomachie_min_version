
/*
 *    RITHMOMACHIE - Created by Anderson5091 10/Avril/17.
 *
 *    .
 */

#ifndef R_DEPLACEMENT_H
#define R_DEPLACEMENT_H

#include "Rithmomachie_Data.h"

//deplacement dans Echiquier
bool (*Valider_deplacement)(CASE *de_case, CASE* vers_case);
bool Valider_deplacement_cercle(CASE *de_case, CASE* vers_case);
bool Valider_glissement_carre(CASE *de_case, CASE* vers_case);
bool Valider_saut_carre(CASE *de_case, CASE* vers_case);
bool Valider_glissement_triangle(CASE *de_case, CASE* vers_case);
bool Valider_saut_triangle(CASE *de_case, CASE* vers_case);
bool Valider_deplacement_pyramide(CASE *de_case, CASE* vers_case);
bool Valider_glissement_pyramide(CASE *de_case, CASE* vers_case);
bool Isset_deplacer_de_case(void);
bool Isset_deplacer_vers_case(void);
void Set_deplacer_de_case(CASE* cs);
void Set_deplacer_vers_case(CASE* cs);
void set_domaine_validite_deplacement(CASE* cs);
void Deplacer_piece_dans_echiquier(CASE *de_case, CASE* vers_case);
void Deplacer_pyramide_dans_echiquier(CASE *de_case, CASE* vers_case);
void Lancer_deplacement_case_vers_case(void);

/*
void Deplacer_dans_echiquier(CASE *deplacer_de, CASE *deplacer_vers);
PIECE *deplacer_piece_de_echiquier(COORDECH de_position,COORDPOINT vers_point);
PIECE *deplacer_pyramide_de_echiquier();
void Deplacer_piece_vers_Echiquier(PIECE *Piece,COORDECH position);
PIECE *deplacer_pyramide_vers_echiquier();
*/

#endif //R_DEPLACEMENT_H
