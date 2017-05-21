
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_PRISE_H
#define R_PRISE_H

#include"Tablier.h"
extern CASE* zone_aneantie[8][9];

bool Verifier_blocage_piece(CASE *cible, CASE* block);
bool Verifier_blocage_pyramide(CASE *cible,CASE* block);
void R_Prise(CASE* block);
bool Isset_prise(void);
bool fin_prise(void);
void Set_prise(void);
void Reset_prise(void);
bool Try_Out_arithmetique(CASE* cible,CASE* tire);
void R_Arithmetique(CASE* cible, CASE* tire, int ordre);
void R_Anneantie(CASE *case_agresseur,CASE *case_victime);
void GUX_zone_aneantie(void);
#endif //R_PRISE_H


