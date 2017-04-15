
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#include "Echiquier.h"
#include "Deplacement.h"
#include "Event.h"


CASE Echiquier[ECHIQUIER_LIGNE_MAX][ECHIQUIER_COLONNE_MAX];
CASE *pointer_sur_case, *pointer_vers_case;
//extern PIECE *adresse_de_plateau, *adresse_vers_plateau;
extern void erreur( const char*txt);


void Init_echiquier_cases(void)
{

    COORDECH position;
    int i, j;

    for (i=0; i< ECHIQUIER_LIGNE_MAX; i++)
    {
        for(j=0; j<ECHIQUIER_COLONNE_MAX; j++)
        {

            position.Ligne=i;
            position.Colonne=j;

            Echiquier[i][j].Piece=NULL;
            Echiquier[i][j].Pyramide=NULL;
            Echiquier[i][j].Position=position;

        }
    }

    //creer des pieces dans des positions de l'echiquier voulou
    //Pieces blanches
    Echiquier[10][2].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,2),
                                       2,Position_vers_point(Echiquier[10][2].Position).X,Position_vers_point(Echiquier[10][2].Position).Y);
    Echiquier[10][3].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,4),
                                       4,Position_vers_point(Echiquier[10][3].Position).X,Position_vers_point(Echiquier[10][3].Position).Y);
    Echiquier[10][4].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,6),
                                       6,Position_vers_point(Echiquier[10][4].Position).X,Position_vers_point(Echiquier[10][4].Position).Y);
    Echiquier[10][5].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,8),
                                       8,Position_vers_point(Echiquier[10][5].Position).X,Position_vers_point(Echiquier[10][5].Position).Y);
    Echiquier[11][2].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,4),
                                       4,Position_vers_point(Echiquier[11][2].Position).X,Position_vers_point(Echiquier[11][2].Position).Y);
    Echiquier[11][3].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,16),
                                       16,Position_vers_point(Echiquier[11][3].Position).X,Position_vers_point(Echiquier[11][3].Position).Y);
    Echiquier[11][4].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,36),
                                       36,Position_vers_point(Echiquier[11][4].Position).X,Position_vers_point(Echiquier[11][4].Position).Y);
    Echiquier[11][5].Piece=Creer_piece(Cercle,P_Libre,P_Blanc,Creer_piece_image(Cercle,P_Blanc,64),
                                       64,Position_vers_point(Echiquier[11][5].Position).X,Position_vers_point(Echiquier[11][5].Position).Y);


    Echiquier[11][1].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,6),
                                       6,Position_vers_point(Echiquier[11][1].Position).X,Position_vers_point(Echiquier[11][1].Position).Y);
    Echiquier[11][0].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,9),
                                       9,Position_vers_point(Echiquier[11][0].Position).X,Position_vers_point(Echiquier[11][0].Position).Y);
    Echiquier[12][3].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,20),
                                       20,Position_vers_point(Echiquier[12][3].Position).X,Position_vers_point(Echiquier[12][3].Position).Y);
    Echiquier[12][2].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,25),
                                       25,Position_vers_point(Echiquier[12][2].Position).X,Position_vers_point(Echiquier[12][2].Position).Y);
    Echiquier[12][4].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,42),
                                       42,Position_vers_point(Echiquier[12][4].Position).X,Position_vers_point(Echiquier[12][4].Position).Y);
    Echiquier[12][5].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,49),
                                       49,Position_vers_point(Echiquier[12][5].Position).X,Position_vers_point(Echiquier[12][5].Position).Y);
    Echiquier[11][6].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,72),
                                       72,Position_vers_point(Echiquier[11][6].Position).X,Position_vers_point(Echiquier[11][6].Position).Y);
    Echiquier[11][7].Piece=Creer_piece(Triangle,P_Libre,P_Blanc,Creer_piece_image(Triangle,P_Blanc,81),
                                       81,Position_vers_point(Echiquier[11][7].Position).X,Position_vers_point(Echiquier[11][7].Position).Y);


    Echiquier[12][0].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,15),
                                       15,Position_vers_point(Echiquier[12][0].Position).X,Position_vers_point(Echiquier[12][0].Position).Y);
    Echiquier[13][0].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,25),
                                       25,Position_vers_point(Echiquier[13][0].Position).X,Position_vers_point(Echiquier[13][0].Position).Y);
    Echiquier[12][1].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,45),
                                       45,Position_vers_point(Echiquier[12][1].Position).X,Position_vers_point(Echiquier[12][1].Position).Y);
    Echiquier[13][1].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,81),
                                       81,Position_vers_point(Echiquier[13][1].Position).X,Position_vers_point(Echiquier[13][1].Position).Y);
    Echiquier[12][7].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,153),
                                       153,Position_vers_point(Echiquier[12][7].Position).X,Position_vers_point(Echiquier[12][7].Position).Y);
    Echiquier[13][6].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,169),
                                       169,Position_vers_point(Echiquier[13][6].Position).X,Position_vers_point(Echiquier[13][6].Position).Y);
    Echiquier[13][7].Piece=Creer_piece(Carre,P_Libre,P_Blanc,Creer_piece_image(Carre,P_Blanc,281),
                                       281,Position_vers_point(Echiquier[13][7].Position).X,Position_vers_point(Echiquier[13][7].Position).Y);


    Echiquier[12][6].Pyramide=Creer_pyramide(Creer_pyramide_image(P_Blanc),
                                              Creer_piece(Cercle,P_Associee,P_Blanc,Creer_piece_image(Cercle,P_Blanc,1),
                                                          1,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y),
                                               Creer_piece(Cercle,P_Associee,P_Blanc,Creer_piece_image(Cercle,P_Blanc,4),
                                                           4,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y),
                                                Creer_piece(Triangle,P_Associee,P_Blanc,Creer_piece_image(Triangle,P_Blanc,9),
                                                            9,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y),
                                                Creer_piece(Triangle,P_Associee,P_Blanc,Creer_piece_image(Triangle,P_Blanc,16),
                                                            16,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y),
                                                 Creer_piece(Carre,P_Associee,P_Blanc,Creer_piece_image(Carre,P_Blanc,25),
                                                             25,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y),
                                                  Creer_piece(Carre,P_Associee,P_Blanc,Creer_piece_image(Carre,P_Blanc,36),
                                                              36,Position_vers_point(Echiquier[12][6].Position).X,Position_vers_point(Echiquier[12][6].Position).Y));


    //fini la creation des pieces
}

void Dessiner_echiquier_cases(void)
{
    ALLEGRO_COLOR Case_color;
    int dx, dy, i, j;


    for (i=0; i<ECHIQUIER_LIGNE_MAX; i++)
    {
        for(j=0; j< ECHIQUIER_COLONNE_MAX; j++)
        {

            if((i%2==0 && j%2==0)||(i%2==1 && j%2==1))
                Case_color=al_map_rgb( 135, 193, 211);
            else
                Case_color=al_map_rgb( 237, 237, 237);

            dx=523+DIM_CASE*j;
            dy=64+DIM_CASE*i;
            al_draw_filled_rectangle(dx, dy, dx+DIM_CASE, dy+DIM_CASE,Case_color);

        }
    }
}

void Dessiner_echiquier_P(void)
{
    int i, j;
    float dx, dy;

    for(i=0; i<ECHIQUIER_LIGNE_MAX; i++)
    {
        for(j=0; j<ECHIQUIER_COLONNE_MAX; j++)
        {

            if(Echiquier[i][j].Piece)
            {
                dx=Echiquier[i][j].Piece->Position.X-DIM_PIECE/2.0;
                dy=Echiquier[i][j].Piece->Position.Y-DIM_PIECE/2.0;
                al_draw_bitmap(Echiquier[i][j].Piece->Image,dx,dy,0);
                //printf("piece desinnee\n");
            }
            else if(Echiquier[i][j].Pyramide)
            {
                dx=Position_vers_point(Echiquier[i][j].Position).X-DIM_PIECE/2.0;
                dy=Position_vers_point(Echiquier[i][j].Position).Y-DIM_PIECE/2.0;
                al_draw_bitmap(Echiquier[i][j].Pyramide->Image,dx,dy,0);
                 //printf("pyramide desinnee\n");
            }
        }
    }
}

void Actualier_echiquier(void)
{

    ALLEGRO_BITMAP *Buffer_echiquier=NULL;
    Buffer_echiquier=al_create_bitmap(largeur_ecran,hauteur_ecran);

    al_set_target_bitmap(Buffer_echiquier);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    Dessiner_echiquier_cases();

    printf("test actualiser echiquier desinner case selectionner\n");
  if (souris_bouton_relache(1))
    {

            COORDPOINT pt;
            COORDECH cs;

            pt.X = souris_x();
            pt.Y= souris_y();

            cs.Ligne=Point_vers_position(pt).Ligne;
            cs.Colonne=Point_vers_position(pt).Colonne;
            if((cs.Colonne>=0)&&(cs.Colonne>=0)){

            if(!Isset_deplacer_de_case())
            {
                Set_deplacer_de_case(&Echiquier[cs.Ligne][cs.Colonne]);

            }
            else
            {
                Set_deplacer_vers_case(&Echiquier[cs.Ligne][cs.Colonne]);
            }

            printf("actualisation encours... \n");//
            printf("%f %f",pt.X , pt.Y);//

                marquer_case_select(cs);
            if(Isset_deplacer_de_case() && Isset_deplacer_vers_case())
            {
              printf("deplacement encour....\n");
              Lancer_deplacement_case_vers_case();
            }
        }
        else{
                printf("click efectuer endehors de l'echiquier.\n");
        }
    }
    else
    {
        //return 0;
        printf("Actualisation Impossible. Aucun action effectuer \n");//
    }

    Dessiner_echiquier_P();

    al_set_target_backbuffer(display);
    al_draw_bitmap(Buffer_echiquier,0,0,0);
            //al_flip_display();//
            //return 1;
    al_destroy_bitmap(Buffer_echiquier);
    Buffer_echiquier=NULL;
}

void marquer_case_select(COORDECH position)
{

    COORDPOINT Pt;
    float dx, dy;

    //al_set_target_bitmap(Buffer);//

    printf("marqueur encours...\n");//
    printf("case(%d,%d)\n",position.Ligne,  position.Colonne);//

    if((position.Colonne>=0 && position.Colonne<ECHIQUIER_COLONNE_MAX)&&
       (position.Ligne>=0 && position.Ligne<ECHIQUIER_LIGNE_MAX))
    {
        Pt=Position_vers_point(position);
        dx=Pt.X-DIM_CASE/2;
        dy=Pt.Y-DIM_CASE/2;
        al_draw_rectangle(dx, dy, dx+DIM_CASE, dy+DIM_CASE, al_map_rgb(43, 96, 127), 4);
        printf("Reussi... case marque\n");//
    }
    //al_set_target_backbuffer(display);
    //al_draw_bitmap(Buffer_echiquier,0,0,0);
    //al_flip_display();//

}
/************************************************************************************/

COORDECH Point_vers_position(COORDPOINT pt)
{
    COORDECH position;
    printf(" converstion pixel to case...\n");//
    printf("pt(%f,%f)\n", pt.X, pt.Y);//

    position.Colonne= (int) floor((843-pt.X)/DIM_CASE);
    if(position.Colonne>=ECHIQUIER_COLONNE_MAX)
        position.Colonne=-1;

    position.Ligne=(int)floor((pt.Y-64)/DIM_CASE);

    if(position.Ligne>=ECHIQUIER_LIGNE_MAX)
        position.Ligne=-1;

    printf("case(%d,%d)\n", position.Ligne,position.Colonne);//
    return position;
}

COORDPOINT Position_vers_point(COORDECH position)
{
    COORDPOINT Pt;
    printf(" converstion case to pixel...\n");
    printf("case(%d,%d)\n", position.Ligne,position.Colonne);//

    Pt.X=843-(position.Colonne+0.5)*DIM_CASE;
    Pt.Y=64+(position.Ligne+0.5)*DIM_CASE;

    printf("pt(%f,%f)\n", Pt.X, Pt.Y);//

    return Pt;
}
