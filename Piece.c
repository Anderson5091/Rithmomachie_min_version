/*
 *    RITHMOMACHIE - Created by Anderson5091 07/Avril/17.
 *
 *    .
 */
#include "Piece.h"
#include "event.h"

extern CASE Echiquier[ECHIQUIER_LIGNE_MAX][ECHIQUIER_COLONNE_MAX];
PIECE* Plateau_1[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];
PIECE* Plateau_2[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];

/***************** Piece *****************/
void Modifier_piece_position(PIECE* piece,COORDPOINT nouvelle_position)
{
   piece->Position=nouvelle_position;
}
void Modifier_piece_etat(PIECE* piece, P_ETAT nouvel_etat)
{
    piece->Etat=nouvel_etat;
}
void Modifier_piece_color(PIECE* piece, P_COLOR nouvelle_color)
{
    ALLEGRO_COLOR Color_p,Color_b,Color_txt;
    int Poids_p=piece->Poids, largeur_b=2;

    piece->Color=nouvelle_color;

    Color_b=al_map_rgb(43, 96, 127);
    al_set_target_bitmap(piece->Image);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(piece->Color==P_Blanc)
     {
         Color_p=al_map_rgb(255,255,255);
         Color_txt=al_map_rgb(0,0,0);
     }
    else
    {
        Color_p=al_map_rgb(0,0,0);
        Color_txt=al_map_rgb(255,255,255);
    }

    if(piece->Type==Cercle)
       {al_draw_filled_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0,Color_p);
       al_draw_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0-1,Color_b,largeur_b);}
    else if(piece->Type==Carre)
        {al_draw_filled_rectangle(0,0,DIM_PIECE,DIM_PIECE,Color_p);
        al_draw_rectangle(1,1,DIM_PIECE-1,DIM_PIECE-1,Color_b,largeur_b);}
    else
        {al_draw_filled_triangle(DIM_PIECE/2,0,DIM_PIECE,DIM_PIECE,0,DIM_PIECE,Color_p);
        al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE-1,DIM_PIECE-1,1,DIM_PIECE-1,Color_b,largeur_b);}
}

ALLEGRO_BITMAP *Creer_piece_image(P_TYPE type_p, P_COLOR color_p, int poids_p)
{
    ALLEGRO_BITMAP *image_p=NULL;
    ALLEGRO_COLOR Color_p,Color_b,Color_txt;
    int Poids_p=poids_p, largeur_b=2;

    Color_b=al_map_rgb(43, 96, 127);
    image_p=al_create_bitmap(DIM_PIECE,DIM_PIECE);
    al_set_target_bitmap(image_p);

    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(color_p==P_Blanc)
     {
         Color_p=al_map_rgb(255,255,255);
         Color_txt=al_map_rgb(0,0,0);
     }
    else
    {
        Color_p=al_map_rgb(0,0,0);
        Color_txt=al_map_rgb(255,255,255);
    }

    if(type_p==Cercle)
       {al_draw_filled_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0,Color_p);
       al_draw_circle(DIM_PIECE/2.0,DIM_PIECE/2.0,DIM_PIECE/2.0-1,Color_b,largeur_b);}
    else if(type_p==Carre)
        {al_draw_filled_rectangle(0,0,DIM_PIECE,DIM_PIECE,Color_p);
        al_draw_rectangle(1,1,DIM_PIECE-1,DIM_PIECE-1,Color_b,largeur_b);}
    else
        {al_draw_filled_triangle(DIM_PIECE/2,0,DIM_PIECE,DIM_PIECE,0,DIM_PIECE,Color_p);
        al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE-1,DIM_PIECE-1,1,DIM_PIECE-1,Color_b,largeur_b);}

    //al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, )

    return image_p;

}

PIECE *Creer_piece(P_TYPE type_p, P_ETAT etat_p, P_COLOR color_p,ALLEGRO_BITMAP *image_p,int poids_p, float x_p, float y_p)
{
    PIECE *Adresse_piece;

       Adresse_piece= malloc(sizeof(PIECE)); // malloc(sizeof(PIECE)); //calloc (1 ,sizeof(PIECE));

       Adresse_piece->Type= type_p;
       Adresse_piece->Etat= etat_p;
       Adresse_piece->Color=color_p;
       Adresse_piece->Image=image_p;
       Adresse_piece->Poids=poids_p;
       Adresse_piece->Position.X=x_p;
       Adresse_piece->Position.Y=y_p;
        //printf("piece cree\n");
       return Adresse_piece;
}


/***************** Pyramide *****************/

PYRAMIDE *Creer_pyramide(ALLEGRO_BITMAP *image_p, PIECE *piece_1, PIECE *piece_2, PIECE *piece_3, PIECE *piece_4, PIECE *piece_5,PIECE *piece_6)
{
    PYRAMIDE *Adresse_pyramide;
    Adresse_pyramide=malloc(sizeof(PYRAMIDE));

    Adresse_pyramide->Reference=NULL;
    Adresse_pyramide->Image=image_p;
    Adresse_pyramide->Compacite=TRUE;
    Adresse_pyramide->Pieces[0]=piece_1;
    Adresse_pyramide->Pieces[1]=piece_2;
    Adresse_pyramide->Pieces[2]=piece_3;
    Adresse_pyramide->Pieces[3]=piece_4;
    Adresse_pyramide->Pieces[4]=piece_5;
    Adresse_pyramide->Pieces[5]=piece_6;

    return Adresse_pyramide;
}


ALLEGRO_BITMAP *Creer_pyramide_image(P_COLOR color_p)
{
    ALLEGRO_BITMAP *image_p=NULL;
    ALLEGRO_COLOR Color_p, Color_b;
    int largeur_b=2;
    Color_b=al_map_rgb(43, 96, 127);

    image_p=al_create_bitmap(DIM_PIECE,DIM_PIECE);
    al_set_target_bitmap(image_p);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(color_p==P_Blanc)
     {
         Color_p=al_map_rgb(255,255,255);
     }
    else
    {
        Color_p=al_map_rgb(0,0,0);
    }

    al_draw_filled_triangle(DIM_PIECE/2.0,0,DIM_PIECE/2.0,DIM_PIECE,DIM_PIECE,2*DIM_PIECE/3.0,Color_p);
    al_draw_filled_triangle(DIM_PIECE/2.0,0,DIM_PIECE/2.0,DIM_PIECE,0,2*DIM_PIECE/3.0,Color_p);
    al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE/2.0,DIM_PIECE-1,DIM_PIECE-1,2*DIM_PIECE/3.0,Color_b,largeur_b);
    al_draw_triangle(DIM_PIECE/2.0,1,DIM_PIECE/2.0,DIM_PIECE-1,1,2*DIM_PIECE/3.0,Color_b,largeur_b);

    return image_p;

}


/***************** Plateaux *****************/
void Init_Plateau_1(void)
{
   /*
    Plateau_1[0][0]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,2),2,466.286,430.349);
    Plateau_1[0][1]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,4),4,426.286,430.349);
    Plateau_1[0][2]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,6),6,386.286,430.349);
    Plateau_1[0][3]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,8),8,346.286,430.349);
    Plateau_1[0][4]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,4),4,306.286,430.349);
    Plateau_1[0][5]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,16),16,266.286,430.349);
    Plateau_1[0][6]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,36),36,226.286,430.349);
    Plateau_1[0][7]=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,64),64,186.286,430.349);


    Plateau_1[1][0]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,6),6,466.286,470.349);
    Plateau_1[1][1]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,9),9,426.286,470.349);
    Plateau_1[1][2]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,20),20,386.286,470.349);
    Plateau_1[1][3]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,25),25,346.286,470.349);
    Plateau_1[1][4]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,42),42,306.286,470.349);
    Plateau_1[1][5]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,49),49,266.286,470.349);
    Plateau_1[1][6]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,72),72,226.286,470.349);
    Plateau_1[1][7]=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,81),81,186.286,470.349);


    Plateau_1[2][0]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,15),15,466.286,510.349);
    Plateau_1[2][1]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,25),25,426.286,510.349);
    Plateau_1[2][2]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,45),45,386.286,510.349);
    Plateau_1[2][3]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,81),81,346.286,510.349);
    Plateau_1[2][4]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,153),153,306.286,510.349);
    Plateau_1[2][5]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,169),169,266.286,510.349);
    Plateau_1[2][6]=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,281),281,226.286,510.349);

    Plateau_1[3][0]=Creer_piece(Carre,P_Associee,P_Blanc,Creer_piece_image(Carre,P_Blanc,281),0,466.286,550.349);
    Plateau_1[3][1]=Creer_piece(Carre,P_Associee,P_Blanc,Creer_piece_image(Carre,P_Blanc,281),0,426.286,550.349);
    Plateau_1[3][2]=Creer_piece(Cercle,P_Associee,P_Blanc,Creer_piece_image(Cercle,P_Blanc,281),0,386.286,550.349);
    Plateau_1[3][3]=Creer_piece(Cercle,P_Associee,P_Blanc,Creer_piece_image(Cercle,P_Blanc,281),0,346.286,550.349);
    Plateau_1[3][4]=Creer_piece(Triangle,P_Associee,P_Blanc,Creer_piece_image(Triangle,P_Blanc,281),0,306.286,550.349);
    Plateau_1[3][5]=Creer_piece(Triangle,P_Associee,P_Blanc,Creer_piece_image(Triangle,P_Blanc,281),0,266.286,550.349);
    */
}

void Init_Plateau_2(void)
{

    Plateau_2[0][0]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,3),3,900.286,430.349);
    Plateau_2[0][1]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,5),5,940.286,430.349);
    Plateau_2[0][2]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,7),7,980.286,430.349);
    Plateau_2[0][3]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,9),9,1020.286,430.349);
    Plateau_2[0][4]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,9),9,1060.286,430.349);
    Plateau_2[0][5]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,25),25,1100.286,430.349);
    Plateau_2[0][6]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,49),49,1140.286,430.349);
    Plateau_2[0][7]=Creer_piece(Cercle,P_Libre,P_Noir,Creer_piece_image(Cercle,P_Noir,81),81,1180.286,430.349);


    Plateau_2[1][0]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,12),12,900.286,470.349);
    Plateau_2[1][1]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,16),16,940.286,470.349);
    Plateau_2[1][2]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,36),36,980.286,470.349);
    Plateau_2[1][3]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,30),30,1020.286,470.349);
    Plateau_2[1][4]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,56),56,1060.286,470.349);
    Plateau_2[1][5]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,64),64,1100.286,470.349);
    Plateau_2[1][6]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,90),90,1140.286,470.349);
    Plateau_2[1][7]=Creer_piece(Triangle,P_Libre,P_Noir,Creer_piece_image(Triangle,P_Noir,100),100,1180.286,470.349);


    Plateau_2[2][0]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,28),28,900.286,510.349);
    Plateau_2[2][1]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,49),49,940.286,510.349);
    Plateau_2[2][2]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,66),66,980.286,510.349);
    Plateau_2[2][3]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,120),120,1020.286,510.349);
    Plateau_2[2][4]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,121),121,1060.286,510.349);
    Plateau_2[2][5]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,225),225,1100.286,510.349);
    Plateau_2[2][6]=Creer_piece(Carre,P_Libre,P_Noir,Creer_piece_image(Carre,P_Noir,361),361,1140.286,510.349);


    Plateau_2[3][0]=Creer_piece(Carre,P_Associee,P_Noir,Creer_piece_image(Carre,P_Noir,28),0,900.286,550.349);
    Plateau_2[3][1]=Creer_piece(Carre,P_Associee,P_Noir,Creer_piece_image(Carre,P_Noir,28),0,940.286,550.349);
    Plateau_2[3][2]=Creer_piece(Triangle,P_Associee,P_Noir,Creer_piece_image(Triangle,P_Noir,100),0,980.286,550.349);
    Plateau_2[3][3]=Creer_piece(Triangle,P_Associee,P_Noir,Creer_piece_image(Triangle,P_Noir,100),0,1020.286,550.349);
    Plateau_2[3][4]=Creer_piece(Cercle,P_Associee,P_Noir,Creer_piece_image(Carre,P_Blanc,81),0,1060.286,550.349);
    Plateau_2[3][5]=Creer_piece(Cercle,P_Associee,P_Noir,Creer_piece_image(Carre,P_Blanc,81),10,1060.286,550.349);

}

void Init_Plateaux(void)
{
    Init_Plateau_1();
    Init_Plateau_2();
}

void Dessiner_plateaux(void)
{
    //ALLEGRO_BITMAP *Plateau_af=NULL;
    int i,j;

    printf("Affichage plateaux encours\n");
    //Plateau_af=al_create_bitmap(largeur_ecran,hauteur_ecran);
    //al_set_target_bitmap(Plateau_af);
    //al_clear_to_color(al_map_rgba(0,0,0,0));

    for(i=0; i<PLATEAU_LIGNE_MAX;i++)
    {
        j=0;
        //for ( j = 0; j<PLATEAU_COLONNE_MAX; j++)
        //{
        while(Plateau_1[i][j])
        //if(Plateau_1[i][j])
        {
            al_draw_bitmap(Plateau_1[i][j]->Image,
                           Plateau_1[i][j]->Position.X-DIM_PIECE/2.0,Plateau_1[i][j]->Position.Y-DIM_PIECE/2.0,0);
            j++;
        }
    }


    for(i=0; i<PLATEAU_LIGNE_MAX;i++)
    {
        j=0;
        //for ( j = 0; j<PLATEAU_COLONNE_MAX; j++)
        //{
        while(Plateau_2[i][j])
            //if(Plateau_2[i][j])
        {
                al_draw_bitmap(Plateau_2[i][j]->Image,
                               Plateau_2[i][j]->Position.X-DIM_PIECE/2.0,Plateau_2[i][j]->Position.Y-DIM_PIECE/2.0,0);
                j++;
        }
    }

    //al_set_target_backbuffer(display);
    //al_draw_bitmap(Plateau_af,0,0,0);
    //al_destroy_bitmap(Plateau_af);
    printf("Affichage plateaux reussi\n");
}

void Detruire_pieces(void)
{
   int i,j,k;

        for (i=0; i< ECHIQUIER_LIGNE_MAX; i++)
        {
            for(j=0; j<ECHIQUIER_COLONNE_MAX; j++)
            {

                if(Echiquier[i][j].Piece)
                {
                    al_destroy_bitmap(Echiquier[i][j].Piece->Image);
                    free(Echiquier[i][j].Piece);
                    Echiquier[i][j].Piece=NULL;
                }
                else if(Echiquier[i][j].Pyramide)
                {
                    al_destroy_bitmap(Echiquier[i][j].Pyramide->Image);
                    for(k=0; k<6; k++)
                    {
                        if(Echiquier[i][j].Pyramide->Pieces[k])
                        {
                            al_destroy_bitmap(Echiquier[i][j].Pyramide->Pieces[k]->Image);
                            free(Echiquier[i][j].Pyramide->Pieces[k]);
                            Echiquier[i][j].Pyramide->Pieces[k]=NULL;
                        }
                    }
                    free(Echiquier[i][j].Pyramide);
                    Echiquier[i][j].Pyramide=NULL;
                }

            }
        }

        printf("Pieces sur Echiquier detruit\n");

        for ( i = 0; i<PLATEAU_LIGNE_MAX; i++)
        {
            j=0;
            //for ( j = 0; j<PLATEAU_COLONNE_MAX; j++)
            //{
            while(Plateau_1[i][j] && j<PLATEAU_COLONNE_MAX)
             {
               if(Plateau_1[i][j])
                {
                        al_destroy_bitmap(Plateau_1[i][j]->Image);
                        free(Plateau_1[i][j]);
                        Plateau_1[i][j]=NULL;
                        j++;
                }
            }
        }

        printf("Pieces dans Plateau_1 detruit\n");

        for ( i = 0; i<PLATEAU_LIGNE_MAX; i++)
        {
            j=0;
            //for ( j = 0; j<PLATEAU_COLONNE_MAX; j++)
            //{
            while(Plateau_2[i][j] && j<PLATEAU_COLONNE_MAX)
            {
                if(Plateau_2[i][j])
                {
                        al_destroy_bitmap(Plateau_2[i][j]->Image);
                        free(Plateau_2[i][j]);
                        Plateau_2[i][j]=NULL;
                        j++;
                }
            }
        }

        printf("pieces dans Plateau_2 detruit\n");

}

//ALLEGRO_BITMAP *Buffer_plateaux=NULL;

void Actualiser_plateaux(void)
{
    ALLEGRO_BITMAP *Buffer_plateaux=NULL;
    Buffer_plateaux=al_create_bitmap(largeur_ecran,hauteur_ecran);

    al_set_target_bitmap(Buffer_plateaux);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    Dessiner_plateaux();

    if (souris_bouton_relache(1)) {

        COORDPOINT pt,coin_sup, coin_inf;
        pt.X = souris_x();
        pt.Y= souris_y();
        int piece_selectionnee=0, i, j;

        printf("selectionner piece dans plateau encours... \n");//
        printf("%f %f",pt.X , pt.Y);//

        for ( i = 0; i<PLATEAU_LIGNE_MAX; i++)
        {
            j=0;
            while((Plateau_1[i][j] && j<PLATEAU_COLONNE_MAX) && (!piece_selectionnee))
            {
                    coin_sup.X=Plateau_1[i][j]->Position.X-20;
                    coin_sup.Y=Plateau_1[i][j]->Position.Y-20;
                    coin_inf.X=Plateau_1[i][j]->Position.X+20;
                    coin_inf.Y=Plateau_1[i][j]->Position.Y+20;

                    if((pt.X>coin_sup.X&&pt.X<coin_inf.X)&&(pt.Y>coin_sup.Y&&pt.Y<coin_inf.Y))
                    {
                        piece_selectionnee=1;
                        //adresse_de_plateau=Plateau_1[i][j];
                        Marquer_piece_plateau_selectionnee(*Plateau_1[i][j]);
                    }
                    else
                    {
                        j++;
                    }
            }
            if(piece_selectionnee)
                break;
        }

        if(!piece_selectionnee)
        {
            for ( i = 0; i<PLATEAU_LIGNE_MAX; i++)
            {
                j=0;
                while((Plateau_2[i][j] && j<PLATEAU_COLONNE_MAX) && (!piece_selectionnee))
                {
                        coin_sup.X=Plateau_2[i][j]->Position.X-20;
                        coin_sup.Y=Plateau_2[i][j]->Position.Y-20;
                        coin_inf.X=Plateau_2[i][j]->Position.X+20;
                        coin_inf.Y=Plateau_2[i][j]->Position.Y+20;

                        if((pt.X>coin_sup.X&&pt.X<coin_inf.X)&&(pt.Y>coin_sup.Y&&pt.Y<coin_inf.Y))
                        {
                            piece_selectionnee=1;
                            //adresse_de_plateau=Plateau_2[i][j];
                            Marquer_piece_plateau_selectionnee(*Plateau_2[i][j]);
                        }
                        else
                        {
                            j++;
                        }

                }
                if(piece_selectionnee)
                break;
            }
        }

    }
    al_set_target_backbuffer(display);
    al_draw_bitmap(Buffer_plateaux,0,0,0);
            //al_flip_display();//
            //return 1;
    al_destroy_bitmap(Buffer_plateaux);
    Buffer_plateaux=NULL;

}

void Marquer_piece_plateau_selectionnee(PIECE piece)
{
    ALLEGRO_COLOR Color_border_p;

    if(piece.Etat!=P_Associee)
       {
            //Buffer=al_create_bitmap(largeur_ecran,hauteur_ecran);
            //al_set_target_bitmap(Buffer);
            //al_clear_to_color(al_map_rgba(0,0,0,0));

            //if(piece.Color==P_Blanc)
            // {
                 Color_border_p=al_map_rgb(43, 96, 127);
             //}
            //else
            //{
            //    Color_border_p=al_map_rgb(255,255,255);
            //}

            if(piece.Type==Cercle)
               al_draw_circle(piece.Position.X,piece.Position.Y,DIM_PIECE/2.0,Color_border_p,4);
            else if(piece.Type==Carre)
                al_draw_rectangle(piece.Position.X-DIM_PIECE/2.0,piece.Position.Y-DIM_PIECE/2.0,piece.Position.X+DIM_PIECE/2.0,piece.Position.Y+DIM_PIECE/2.0,Color_border_p,4);
            else if(piece.Type==Triangle)
                al_draw_triangle(piece.Position.X,piece.Position.Y-DIM_PIECE/2.0,piece.Position.X+DIM_PIECE/2.0,piece.Position.Y+DIM_PIECE/2.0,piece.Position.X-DIM_PIECE/2.0,piece.Position.Y+DIM_PIECE/2.0,Color_border_p,4);

            //al_set_target_backbuffer(display);
            //al_draw_bitmap(Buffer_plateaux,0,0,0);
            //al_flip_display();//
            //return 1;
            //al_destroy_bitmap(Buffer);
            //Buffer=NULL;
       }
}
