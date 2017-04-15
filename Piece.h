/*
 *    RITHMOMACHIE - Created by Anderson5091 07/Avril/17.
 *
 *    .
 */

#include "Echiquier.h"

#ifndef R_PIECE_H
#define R_PIECE_H

#include "Rithmomachie_Data.h"

 typedef enum P_TYPE{
    Cercle,
    Triangle,
    Carre,
    //Complex
} P_TYPE;

typedef enum P_COLOR{
    P_Blanc,
    P_Noir
} P_COLOR;

typedef enum P_ETAT{
    P_Libre,
    P_Associee,
    P_Prise
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
    bool Compacite;

}PYRAMIDE;



ALLEGRO_BITMAP *Creer_piece_image(P_TYPE type_p, P_COLOR color_p, int poids_p);
ALLEGRO_BITMAP *Creer_pyramide_image(P_COLOR color_p);
PIECE *Creer_piece(P_TYPE type_p, P_ETAT etat_p, P_COLOR color_p,
                         ALLEGRO_BITMAP *image_p,int poids_p, float x_p, float y_p);
PYRAMIDE* Creer_pyramide(ALLEGRO_BITMAP *image_p, PIECE *piece_1, PIECE *piece_2, PIECE *piece_3,
                    PIECE *piece_4, PIECE *piece_5, PIECE *piece_6);
ALLEGRO_BITMAP *Creer_pyramide_image(P_COLOR color_p);
void Modifier_piece_position(PIECE* piece,COORDPOINT nouvelle_position);
void Modifier_piece_etat(PIECE* piece, P_ETAT nouvel_etat);
void Modifier_piece_color(PIECE* piece, P_COLOR nouvelle_color);
void Modifier_piece_Image();//
void Detruire_pieces(void);

void Init_Plateau_1(void);
void Init_Plateau_2(void);
void Init_Plateaux(void);
void Dessiner_plateaux(void);
void Marquer_piece_plateau_selectionnee(PIECE piece);
void Actualiser_plateaux(void);

#endif //R_PIECE_H
