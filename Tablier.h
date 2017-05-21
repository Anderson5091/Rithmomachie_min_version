
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_tablier_H
#define R_tablier_H

#include"Rithmomachie_Data.h"
#include "GUI.h"
#include "Piece.h"

typedef struct COORDTAB
{
    int Ligne;
    int Colonne;
}COORDTAB;

typedef struct CASE
{
    PIECE *Piece;
    PYRAMIDE *Pyramide;
    COORDTAB Position;
}CASE;

extern CASE Tablier[TABLIER_LIGNE_MAX][TABLIER_COLONNE_MAX];

COORDTAB Point_vers_position(COORDPOINT pt);
COORDPOINT Position_vers_point(COORDTAB position);
CASE* Position_vers_adresse(COORDTAB position);

void Init_tablier_cases(void);
void Dessiner_tablier_cases(void);
void Dessiner_tablier_P(void);
void Marquer_case_select(CASE* cs);
void Actualier_tablier(void);
#endif //R_tablier_H

