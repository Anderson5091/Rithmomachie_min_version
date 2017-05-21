/*
 *    RITHMOMACHIE - Created by Anderson5091 07/Avril/17.
 *
 *    .
 */
#include "Piece.h"
#include "Moyeu.h"

extern CASE Tablier[TABLIER_LIGNE_MAX][TABLIER_COLONNE_MAX];
extern MOYEU Moyeux[JOUEUR_MAX];

/***************** Piece *****************/
void Modifier_piece_position(PIECE* piece,COORDPOINT nouvelle_position){
   piece->Position=nouvelle_position;
}

void Modifier_piece_etat(PIECE* piece, P_ETAT nouvel_etat){
    piece->Etat=nouvel_etat;
}

void Modifier_piece_color(PIECE* piece, P_COLOR nouvelle_color)
{
    piece->Color=nouvelle_color;
    Modifier_piece_Image(piece);
}

void Modifier_piece_Image(PIECE* piece){

    ALLEGRO_COLOR Color_p,Color_b,Color_txt;
    ALLEGRO_FONT* police_poids=al_load_font("Roboto-Light.ttf",10,0);
    int Poids_p=piece->Poids, largeur_b=2;

    Color_b=al_map_rgb(43, 96, 127);
    al_set_target_bitmap(piece->Image);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(piece->Color==P_Blanc){
         Color_p=al_map_rgb(255,255,255);
         Color_txt=al_map_rgb(0,0,0);
     }
    else{
        Color_p=al_map_rgb(0,0,0);
        Color_txt=al_map_rgb(255,255,255);
    }

    if(piece->Type==Cercle){
        al_draw_filled_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0,Color_p);
        al_draw_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0-1,Color_b,largeur_b);
    }
    else if(piece->Type==Carre){
        al_draw_filled_rectangle(0,0,DIM_PIECE,DIM_PIECE,Color_p);
        al_draw_rectangle(1,1,DIM_PIECE-1,DIM_PIECE-1,Color_b,largeur_b);
    }
    else{
        al_draw_filled_triangle(DIM_PIECE/2,0,DIM_PIECE,DIM_PIECE,0,DIM_PIECE,Color_p);
        al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE-1,DIM_PIECE-1,1,DIM_PIECE-1,Color_b,largeur_b);
    }

    if(piece->Type==Triangle)
       al_draw_textf(police_poids, Color_txt, DIM_PIECE/2.0, DIM_PIECE/2.0, ALLEGRO_ALIGN_CENTRE,"%d", Poids_p);
    else
        al_draw_textf(police_poids, Color_txt, DIM_PIECE/2.0, DIM_PIECE/2.0-5, ALLEGRO_ALIGN_CENTRE,"%d", Poids_p);

    al_destroy_font(police_poids);
}

PIECE* _Piece(P_TYPE type_p, P_ETAT etat_p, P_COLOR color_p,int poids_p){
    PIECE *Adresse_piece;

    Adresse_piece= malloc(sizeof(PIECE));
    Adresse_piece->Type=type_p;
    Adresse_piece->Etat=etat_p;
    Adresse_piece->Color=color_p;
    Adresse_piece->Poids=poids_p;
    Adresse_piece->Image=al_create_bitmap(DIM_PIECE,DIM_PIECE);

    return Adresse_piece;
}

void Detruire_piece(PIECE *piece){
    if(piece){
        al_destroy_bitmap(piece->Image);
        piece->Image=NULL;
        free(piece);
        piece=NULL;
    }
}
/***************** Pyramide *****************/
PYRAMIDE* _Pyramide(PIECE *piece_1, PIECE *piece_2, PIECE *piece_3,PIECE *piece_4, PIECE *piece_5, PIECE *piece_6){
    PYRAMIDE *Adresse_pyramide;
    int poids_pyramide=0, i;
    Adresse_pyramide=malloc(sizeof(PYRAMIDE));
    Adresse_pyramide->Reference=NULL;
    Adresse_pyramide->Compacite=TRUE;
    Adresse_pyramide->Image=Creer_pyramide_image(piece_1->Color);
    Adresse_pyramide->Pieces[0]=piece_1;
    Adresse_pyramide->Pieces[1]=piece_2;
    Adresse_pyramide->Pieces[2]=piece_3;
    Adresse_pyramide->Pieces[3]=piece_4;
    Adresse_pyramide->Pieces[4]=piece_5;
    Adresse_pyramide->Pieces[5]=piece_6;

    for(i=0;i<6;i++){
        if(Adresse_pyramide->Pieces[i]){
            poids_pyramide+=Adresse_pyramide->Pieces[i]->Poids;
        }
    }
    Adresse_pyramide->Poids=poids_pyramide;

}

ALLEGRO_BITMAP *Creer_pyramide_image(P_COLOR color_p){

    ALLEGRO_BITMAP *image_p=NULL;
    ALLEGRO_COLOR Color_p, Color_b;
    int largeur_b=2;
    Color_b=al_map_rgb(43, 96, 127);

    image_p=al_create_bitmap(DIM_PIECE,DIM_PIECE);
    al_set_target_bitmap(image_p);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(color_p==P_Blanc)
         Color_p=al_map_rgb(255,255,255);
    else
        Color_p=al_map_rgb(0,0,0);

    al_draw_filled_triangle(DIM_PIECE/2.0,0,DIM_PIECE/2.0,DIM_PIECE,DIM_PIECE,2*DIM_PIECE/3.0,Color_p);
    al_draw_filled_triangle(DIM_PIECE/2.0,0,DIM_PIECE/2.0,DIM_PIECE,0,2*DIM_PIECE/3.0,Color_p);
    al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE/2.0,DIM_PIECE-1,DIM_PIECE-1,2*DIM_PIECE/3.0,Color_b,largeur_b);
    al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE/2.0,DIM_PIECE-1,1,2*DIM_PIECE/3.0,Color_b,largeur_b);

    return image_p;

}

void Modifier_pyramide_reference(PYRAMIDE *pyramide, PIECE *piece){
    int i;
    for(i=0;i<6;i++){
        if(pyramide->Pieces[i]==piece){
            pyramide->Reference=piece;
            break;
        }
    }
}

void Reordonner_pyramide_pieces(PYRAMIDE* pyramide){
    int i;

    //while((!pyramide->Pieces[i]&&pyramide->Pieces[i+1])&&i<6){
    for(i=0;i<6;i++){
        if(!pyramide->Pieces[i]&&pyramide->Pieces[i+1]){
            pyramide->Pieces[i]=pyramide->Pieces[i+1];
            pyramide->Pieces[i+1]=NULL;
        }
    }
}
void Retirer_piece_dans_pyramide(PIECE* piece, PYRAMIDE* pyramide)
{
    int i=0;
    while(pyramide->Pieces[i]!=piece&&i<6)
        i++;
    if(i<6){
        pyramide->Pieces[i]=NULL;
        pyramide->Compacite=FALSE;
        Reordonner_pyramide_pieces(pyramide);
    }

}
void Detruire_pyramide(PYRAMIDE *pyramide){
    int i;
    if(pyramide){
       for(i=0;i<6;i++){
            if(pyramide->Pieces[i])
                Detruire_piece(pyramide->Pieces[i]);

       }
        al_destroy_bitmap(pyramide->Image);
        pyramide->Image=NULL;
        free(pyramide);
        pyramide=NULL;
    }
}

void Detruire_pieces(void)
{
   int i, j, moyeu;

        for (i=0; i< TABLIER_LIGNE_MAX; i++){
            for(j=0; j<TABLIER_COLONNE_MAX; j++){
                if(Tablier[i][j].Piece){
                    Detruire_piece(Tablier[i][j].Piece);
                    //printf("pieces tabliers detruie\n");
                }
                else if(Tablier[i][j].Pyramide){
                    Detruire_pyramide(Tablier[i][j].Pyramide);
                }
            }
        }
        //printf("Pieces sur Tablier detruit\n");
        for(moyeu=0;moyeu<2;moyeu++){
            for ( i = 0; i<PLATEAU_LIGNE_MAX; i++){
                j=0;
                while(Moyeux[moyeu].Plateau[i][j] && j<PLATEAU_COLONNE_MAX){
                   if(Moyeux[moyeu].Plateau[i][j]){
                        Detruire_piece(Moyeux[moyeu].Plateau[i][j]);
                    }
                    j++;
                }
            }
            //printf("Pieces dans Plateau%d detruit\n",moyeu+1);
        }
}
