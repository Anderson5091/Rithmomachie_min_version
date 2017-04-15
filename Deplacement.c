
#include"Piece.h"
#include"Echiquier.h"
#include "Deplacement.h"

extern CASE Echiquier[ECHIQUIER_LIGNE_MAX][ECHIQUIER_COLONNE_MAX];
CASE *deplacer_de_case, *deplacer_vers_case;
PIECE *deplacer_piece_de_plateau, *deplacer_piece_de_plateau;

//extern PIECE* Plateau_1[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];
//extern PIECE* Plateau_2[PLATEAU_LIGNE_MAX][PLATEAU_COLONNE_MAX];
//extern PIECE *adresse_de_plateau, *adresse_vers_plateau;

bool Isset_deplacer_de_case(void)
{
    if(deplacer_de_case){
            printf("piece dans case(%d,%d) prete a deplacer\n",
                   deplacer_de_case->Position.Ligne,deplacer_de_case->Position.Colonne);
            return TRUE;
    }
    else{
            printf("aucune case n'a ete selectionnee\n");
            return FALSE;
    }
}

bool Isset_deplacer_vers_case(void)
{
    if(deplacer_vers_case)
    return TRUE;
    else
    return FALSE;
}

void Set_deplacer_de_case(CASE* cs)
{
    if((cs->Piece)||(cs->Pyramide))
    {deplacer_de_case=cs;
    set_domaine_validite_deplacement(cs);
    printf("case a deplaser reference...\n");
    printf("pointer sur case: (%d, %d)\n", deplacer_de_case->Position.Ligne,
                       deplacer_de_case->Position.Colonne);}
    else
    {
       printf("case vide\n");
    }
}

void Set_deplacer_vers_case(CASE* cs)
{
    if(!cs->Piece)
    {deplacer_vers_case=cs;
    printf("case recepteur reference...\n");
    printf("pointer vers case: (%d, %d)\n", deplacer_vers_case->Position.Ligne,
                       deplacer_vers_case->Position.Colonne);}
    else{
        printf("case occupee\n");
    }
}

void set_domaine_validite_deplacement(CASE* cs)
{

    if(cs->Piece)
    {
      switch(cs->Piece->Type)
      {
        case Cercle:
            Valider_deplacement=Valider_deplacement_cercle;
            break;
        case Triangle:
            Valider_deplacement=Valider_glissement_triangle;
            break;
        case Carre:
            Valider_deplacement=Valider_glissement_carre;
            break;
      }
    }
    else if(cs->Pyramide)
    {
        if(cs->Pyramide->Compacite)
        {
            Valider_deplacement=Valider_glissement_pyramide;
        }
        else if((!cs->Pyramide->Compacite)&&(cs->Pyramide->Reference))
        {
            switch(cs->Pyramide->Reference->Type)
              {
                case Cercle:
                    Valider_deplacement=Valider_deplacement_cercle;
                    break;
                case Triangle:
                    Valider_deplacement=Valider_glissement_triangle;
                    break;
                case Carre:
                    Valider_deplacement=Valider_glissement_carre;
                    break;
              }
        }
    }
}

void Deplacer_piece_dans_echiquier(CASE *de_case, CASE* vers_case)
{
    Modifier_piece_position(de_case->Piece, Position_vers_point(vers_case->Position));
    vers_case->Piece=de_case->Piece;
    de_case->Piece=NULL;
    vers_case=NULL;
    de_case=NULL;
}


void Deplacer_pyramide_dans_echiquier(CASE *de_case, CASE* vers_case)
{
    int i;
    for(i=0;i<6;i++)
    {
        if(de_case->Pyramide->Pieces[i])
        {
            Modifier_piece_position(de_case->Pyramide->Pieces[i], Position_vers_point(vers_case->Position));
        }
    }

    vers_case->Pyramide=de_case->Pyramide;
    de_case->Pyramide=NULL;
    vers_case=NULL;
    de_case=NULL;
}

void Lancer_deplacement_case_vers_case(void)
{
    if((((!deplacer_vers_case->Piece)&&(!deplacer_vers_case->Piece))&&
       ((deplacer_de_case->Piece)||(deplacer_de_case->Pyramide)))&&
       ((*Valider_deplacement)(deplacer_de_case,deplacer_vers_case)))
    {
        if(deplacer_de_case->Piece)
        {
            Deplacer_piece_dans_echiquier(deplacer_de_case,deplacer_vers_case);
            deplacer_vers_case=NULL;
            deplacer_de_case=NULL;
            printf("Piece deplacee avec succes\n\n");
        }
        else if(deplacer_de_case->Pyramide)
        {
            Deplacer_pyramide_dans_echiquier(deplacer_de_case,deplacer_vers_case);
            deplacer_de_case->Pyramide=NULL;
            deplacer_vers_case=NULL;
            deplacer_de_case=NULL;
            printf("Pyramide deplacee avec succes\n\n");
        }
    }
}

bool Valider_deplacement_cercle(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_deplacement_carre[4]={{position.Ligne-1,position.Colonne-1},
                                         {position.Ligne-1,position.Colonne+1},
                                         {position.Ligne+1,position.Colonne-1},
                                         {position.Ligne+1,position.Colonne+1}};
    i=0;
    while((i<4)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_deplacement_carre[i].Ligne)
             &&(vers_case->Position.Colonne==liste_deplacement_carre[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else
        return FALSE;
}

bool Valider_glissement_carre(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_glissement_carre[4]={{position.Ligne,position.Colonne+3},
                                        {position.Ligne,position.Colonne-3},
                                        {position.Ligne+3,position.Colonne},
                                        {position.Ligne-3,position.Colonne}};
    i=0;
    while((i<4)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_glissement_carre[i].Ligne)
             &&(vers_case->Position.Colonne==liste_glissement_carre[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else if(de_case->Piece)
        return Valider_saut_carre(de_case,vers_case);
    else
        return FALSE;
}

bool Valider_saut_carre(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_saut_carre[8]={{position.Ligne+1,position.Colonne+3},
                                  {position.Ligne+1,position.Colonne-3},
                                  {position.Ligne-1,position.Colonne+3},
                                  {position.Ligne-1,position.Colonne-3},
                                  {position.Ligne+3,position.Colonne+1},
                                  {position.Ligne+3,position.Colonne-1},
                                  {position.Ligne-3,position.Colonne+1},
                                  {position.Ligne-3,position.Colonne-1}};
    i=0;
    while((i<8)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_saut_carre[i].Ligne)
             &&(vers_case->Position.Colonne==liste_saut_carre[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else
        return FALSE;
}

bool Valider_glissement_triangle(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_glissement_triangle[4]={{position.Ligne,position.Colonne+2},
                                           {position.Ligne,position.Colonne-2},
                                           {position.Ligne+2,position.Colonne},
                                           {position.Ligne-2,position.Colonne}};
    i=0;
    while((i<4)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_glissement_triangle[i].Ligne)
             &&(vers_case->Position.Colonne==liste_glissement_triangle[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else if(de_case->Piece)
        return Valider_saut_triangle(de_case,vers_case);
    else
        return FALSE;
}

bool Valider_saut_triangle(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_saut_carre[8]={{position.Ligne+1,position.Colonne+2},
                                  {position.Ligne+1,position.Colonne-2},
                                  {position.Ligne-1,position.Colonne+2},
                                  {position.Ligne-1,position.Colonne-2},
                                  {position.Ligne+2,position.Colonne+1},
                                  {position.Ligne+2,position.Colonne-1},
                                  {position.Ligne-2,position.Colonne+1},
                                  {position.Ligne-2,position.Colonne-1}};
    i=0;
    while((i<8)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_saut_carre[i].Ligne)
             &&(vers_case->Position.Colonne==liste_saut_carre[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else
        return FALSE;
}

bool Valider_glissement_pyramide(CASE *de_case, CASE* vers_case)
{
    int i,position_trouver=0;
    COORDECH position=de_case->Position;
    COORDECH liste_glissement_pyramide[24]={
        {position.Ligne+1,position.Colonne},{position.Ligne+2,position.Colonne},{position.Ligne+3,position.Colonne},
        {position.Ligne-1,position.Colonne},{position.Ligne-2,position.Colonne},{position.Ligne-3,position.Colonne},
        {position.Ligne,position.Colonne+1},{position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne+3},
        {position.Ligne,position.Colonne-1},{position.Ligne,position.Colonne-2},{position.Ligne,position.Colonne-3},
        {position.Ligne+1,position.Colonne+1},{position.Ligne+2,position.Colonne+2},{position.Ligne+3,position.Colonne+3},
        {position.Ligne+1,position.Colonne-1},{position.Ligne+2,position.Colonne-2},{position.Ligne+3,position.Colonne-3},
        {position.Ligne-1,position.Colonne-1},{position.Ligne-2,position.Colonne-2},{position.Ligne-3,position.Colonne-3},
        {position.Ligne-1,position.Colonne+1},{position.Ligne-2,position.Colonne+2},{position.Ligne-3,position.Colonne+3}};

    i=0;
    while((i<24)&&(!position_trouver))
    {
        if((vers_case->Position.Ligne==liste_glissement_pyramide[i].Ligne)
             &&(vers_case->Position.Colonne==liste_glissement_pyramide[i].Colonne))
        {
            position_trouver=1;
        }
        i++;
    }

    if(position_trouver)
        return TRUE;
    else
        return FALSE;
}

/*
bool piece_en_deplacement_de_tableau(void)
{
    if (deplacer_piece_de_plateau{
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

*/
/*
void Actualiser_piece_a_deplacer_de_plateau(PIECE* piece_a_deplacer)
{
    deplacer_piece_de_plateau=piece_a_deplacer;
}


void Deplacer_piece_vers_Echiquier(PIECE *Adresse_piece,COORDECH position)
{

    if(!Echiquier[position.Ligne][position.Colonne].Piece)
    {
        Echiquier[position.Ligne][position.Colonne].Piece=Adresse_piece;
        Adresse_piece=NULL;
        //regroupe les pieces en placant chaque piece a la place de la piece avant jusqua la piece retire;
    }
}


void Deplacer_dans_echiquier(CASE *deplacer_de, CASE *deplacer_vers)
{
    if((!pointer_vers_case->Piece) && (!pointer_vers_case->Pyramide))
    {
        printf(" deplacemnt piece case(%d,%d) vers case(%d,%d) encours ...\n",
                pointer_sur_case->Position.Ligne,pointer_sur_case->Position.Colonne,
                pointer_vers_case->Position.Ligne,pointer_vers_case->Position.Colonne);

        pointer_vers_case->Piece=pointer_sur_case->Piece;
        Echiquier[][]=
        Echiquier[][]
        printf("piece deplacee\n");
        pointer_sur_case->Piece=NULL;
    }
}
*/
