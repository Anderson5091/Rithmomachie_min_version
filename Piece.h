/*
 *    RITHMOMACHIE - Created by Anderson5091 07/Avril/17.
 *
 *    .
 */

#include "Tablier.h"

#ifndef R_PIECE_H
#define R_PIECE_H

#include "Rithmomachie_Data.h"

 typedef enum P_TYPE{
    Cercle,
    Triangle,
    Carre,
} P_TYPE;

typedef enum P_COLOR{
    P_Blanc,
    P_Noir
} P_COLOR;

typedef enum P_ETAT{
    P_Libre,
    P_Associee,
    P_Prise,
    P_Bloquer
} P_ETAT;

typedef struct PIECE
{
    P_TYPE Type;
    P_ETAT Etat;
    P_COLOR Color;
    ALLEGRO_BITMAP *Image;
    int Poids;
    COORDPOINT Position;
}PIECE;

typedef struct PYRAMIDE
{
    PIECE *Pieces[6];
    PIECE *Reference;
    ALLEGRO_BITMAP *Image;
    int Poids;
    bool Compacite;

}PYRAMIDE;

PIECE *_Piece(P_TYPE type_p, P_ETAT etat_p, P_COLOR color_p,int poids_p);
PYRAMIDE* _Pyramide(PIECE *piece_1, PIECE *piece_2, PIECE *piece_3,PIECE *piece_4, PIECE *piece_5, PIECE *piece_6);
ALLEGRO_BITMAP *Creer_pyramide_image(P_COLOR color_p);

void Modifier_piece_position(PIECE* piece,COORDPOINT nouvelle_position);
void Modifier_piece_etat(PIECE* piece, P_ETAT nouvel_etat);
void Modifier_piece_color(PIECE* piece, P_COLOR nouvelle_color);
void Modifier_piece_Image(PIECE* piece);
void Modifier_pyramide_reference(PYRAMIDE *pyramide, PIECE *piece);
void Retirer_piece_dans_pyramide(PIECE* piece, PYRAMIDE* pyramide);
void Detruire_pieces(void);

#endif //R_PIECE_H
