
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_ECHIQUIER_H
#define R_ECHIQUIER_H

#include"Rithmomachie_Data.h"
#include "GUI.h"
#include "Piece.h"

typedef struct COORDECH
{
    int Ligne;
    int Colonne;
}COORDECH;

typedef struct CASE
{
    PIECE *Piece;
    PYRAMIDE *Pyramide;
    COORDECH Position;
}CASE;


COORDECH Point_vers_position(COORDPOINT pt);
COORDPOINT Position_vers_point(COORDECH position);

void Init_echiquier_cases(void);//OK//
void Dessiner_echiquier_cases(void);//ok//
void Dessiner_echiquier_P(void);//ok//
void marquer_case_select(COORDECH position);//ok//
void Actualier_echiquier(void);//
#endif //R_ECHIQUIER_H

