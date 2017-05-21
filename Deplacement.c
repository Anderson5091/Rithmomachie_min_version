
/*
 *    RITHMOMACHIE - Created by Anderson5091 10/Avril/17.
 *                 - Fin de creation 23/Avril/2017.
 *      ce module peremet de gerer l'ensemble de tous les deplacement possible
 *      en prenant en compte que deux parametre une case de depart et une case d'arrivee dans l'Tablier.
 *    .
 */

#include"Piece.h"
#include"Tablier.h"
#include"Deplacement.h"

bool deplacement;
CASE *deplacer_de_case, *deplacer_vers_case;
PIECE *deplacer_de_moyeux;


bool Isset_deplacement(void){
    return deplacement;
}

void Set_deplacement(void){
   deplacement=TRUE;
}

void Reset_deplacement(void){
    deplacer_de_case=NULL;
    deplacer_vers_case=NULL;
    deplacer_de_moyeux=NULL;
    deplacement=FALSE;
}

bool Isset_deplacer_de_case(void){
    if(deplacer_de_case){
            //printf("piece dans case(%d,%d) prete a deplacer\n",
                   //deplacer_de_case->Position.Ligne,deplacer_de_case->Position.Colonne);
            return TRUE;
    }
    else{
            //printf("aucune case n'a ete selectionnee\n");
            return FALSE;
    }
}

bool Isset_deplacer_vers_case(void){
    if(deplacer_vers_case)
    return TRUE;
    else
    return FALSE;
}

bool Isset_deplacer_de_moyeux(void){
    if(deplacer_de_moyeux)
    return TRUE;
    else
    return FALSE;
}

void Set_deplacer_de_case(CASE* cs){
    if((cs->Piece)||(cs->Pyramide))
        deplacer_de_case=cs;
    else{
       // printf("case vide\n");
    }
}

void Set_deplacer_vers_case(CASE* cs){
    //if(!cs->Piece&&!cs->Pyramide)
        deplacer_vers_case=cs;
    //else{
        //printf("case occupee\n");
    //}
}

void Set_deplacer_de_moyeux(PIECE *piece){
    deplacer_de_moyeux=piece;
}

CASE* Deplacer_vers_case(void){
  return deplacer_vers_case;
}

CASE* Deplacer_de_case(void){
    return deplacer_de_case;
}

PIECE* Deplacer_de_moyeux(void){
    return deplacer_de_moyeux;
}

void Deplacer_piece_dans_tablier(CASE *de_case, CASE* vers_case){
    Modifier_piece_position(de_case->Piece, Position_vers_point(vers_case->Position));
    vers_case->Piece=de_case->Piece;
    de_case->Piece=NULL;
    vers_case=NULL;
    de_case=NULL;
}


void Deplacer_pyramide_dans_tablier(CASE *de_case, CASE* vers_case){
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
    de_case->Piece=NULL;
    vers_case=NULL;
    de_case=NULL;
}

void Deplacement_piece(CASE* de_case,CASE* vers_case){
    bool pyramide_piece=(de_case->Pyramide)?TRUE:FALSE,still_true;
    int i=0, nomb_d=0;
    COORDTAB *liste_deplacement;
    COORDTAB position=de_case->Position;

        if(de_case->Piece->Type==Cercle){

            COORDTAB liste_d[4]={{position.Ligne-1,position.Colonne-1},{position.Ligne-1,position.Colonne+1},{position.Ligne+1,position.Colonne-1},{position.Ligne+1,position.Colonne+1}};
            nomb_d=4; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB));    for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i]; if(pyramide_piece){pyramide_piece=FALSE; still_true=TRUE;}
        }
        else if(de_case->Piece->Type==Carre){
            COORDTAB liste_d[12]={{position.Ligne+1,position.Colonne+3},{position.Ligne+1,position.Colonne-3},{position.Ligne-1,position.Colonne+3},{position.Ligne-1,position.Colonne-3},
                                  {position.Ligne+3,position.Colonne+1},{position.Ligne+3,position.Colonne-1},{position.Ligne-3,position.Colonne+1},{position.Ligne-3,position.Colonne-1},
                                  {position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-3},{position.Ligne+3,position.Colonne},{position.Ligne-3,position.Colonne}};
            nomb_d=12; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB));   for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i];
        }
        else if(de_case->Piece->Type==Triangle){
            COORDTAB liste_d[12]={{position.Ligne+1,position.Colonne+2},{position.Ligne+1,position.Colonne-2},{position.Ligne-1,position.Colonne+2},{position.Ligne-1,position.Colonne-2},
                                  {position.Ligne+2,position.Colonne+1},{position.Ligne+2,position.Colonne-1},{position.Ligne-2,position.Colonne+1},{position.Ligne-2,position.Colonne-1},
                                  {position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne-2},{position.Ligne+2,position.Colonne},{position.Ligne-2,position.Colonne}};
            nomb_d=12; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB)); for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i];
        }
    i=0;
    nomb_d=(de_case->Piece->Type==Cercle)?8:nomb_d;
    while(i<nomb_d-4&&!Isset_deplacement()&&!pyramide_piece){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
                if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                    if(vers_case==Position_vers_adresse(liste_deplacement[i])){
                        if(!still_true){
                            Deplacer_piece_dans_tablier(de_case,vers_case); Set_deplacement();}
                        else{
                            de_case->Piece=NULL;
                            Deplacement_pyramide(de_case,vers_case); Set_deplacement();still_true=FALSE;
                        }
                    } else i++;
                }else i++;
            }else i++;

        }
    i=8;
    while(i<nomb_d&&!Isset_deplacement()){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
                if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                    if(vers_case==Position_vers_adresse(liste_deplacement[i])
                       &&(Is_chemin_libre(de_case,i))){
                        if(!pyramide_piece){
                            Deplacer_piece_dans_tablier(de_case,vers_case); Set_deplacement();}
                        else{
                              de_case->Piece=NULL;
                              Deplacement_pyramide(de_case,vers_case);pyramide_piece=FALSE; Set_deplacement();
                        }
                    }else i++;
                }else i++;
            } else i++;
    }
    for(i=0;i<nomb_d;i++)
        free(liste_deplacement);
}

void Deplacement_pyramide(CASE* de_case,CASE* vers_case){
  int i=0, nomb_d=24;
    COORDTAB position=de_case->Position;
    COORDTAB liste_deplacement[24]={{position.Ligne+1,position.Colonne},{position.Ligne+2,position.Colonne},{position.Ligne+3,position.Colonne},{position.Ligne-1,position.Colonne},{position.Ligne-2,position.Colonne},{position.Ligne-3,position.Colonne},
        {position.Ligne,position.Colonne+1},{position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-1},{position.Ligne,position.Colonne-2},{position.Ligne,position.Colonne-3},
        {position.Ligne+1,position.Colonne+1},{position.Ligne+2,position.Colonne+2},{position.Ligne+3,position.Colonne+3},{position.Ligne+1,position.Colonne-1},{position.Ligne+2,position.Colonne-2},{position.Ligne+3,position.Colonne-3},
        {position.Ligne-1,position.Colonne-1},{position.Ligne-2,position.Colonne-2},{position.Ligne-3,position.Colonne-3},{position.Ligne-1,position.Colonne+1},{position.Ligne-2,position.Colonne+2},{position.Ligne-3,position.Colonne+3}};

    while(i<24 && !Isset_deplacement()){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
            if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                if(vers_case==Position_vers_adresse(liste_deplacement[i])&&
                    (Is_chemin_libre(de_case,i))){
                        Deplacer_pyramide_dans_tablier(de_case,vers_case); Set_deplacement();
                }else i++;
            }else i++;
        } else i++;
    }
}

void Lancer_deplacement(CASE* de_case,CASE* vers_case ){
   if(de_case->Piece){
       Deplacement_piece(de_case,vers_case);
   }
   else if(de_case->Pyramide){
       if(de_case->Pyramide->Compacite){
           Deplacement_pyramide(de_case,vers_case);
       }
       else{
            if(de_case->Pyramide->Reference){
                de_case->Piece=de_case->Pyramide->Reference;
                Deplacement_piece(de_case,vers_case); de_case->Piece=NULL;
            }
       }
   }
}

void Deplacer_piece_vers_moyeu_plateau(PIECE* piece, int joueur_id)
{
    extern MOYEU Moyeux[JOUEUR_MAX];
   float dx=(joueur_id==0)?26.286:1340.286, dy=449.34;
   int j=0, i=(piece->Type==Cercle)?0:((piece->Type==Triangle)?1:2);
   COORDPOINT pt;

   while(Moyeux[joueur_id].Plateau[i][j]&&j<PLATEAU_COLONNE_MAX){
       j++;
   }
   if(j<PLATEAU_COLONNE_MAX){
        pt.X=(joueur_id==0)?dx+j*DIM_CASE:dx-j*DIM_CASE; pt.Y=dy+i*DIM_CASE;
        Moyeux[joueur_id].Plateau[i][j]=piece;
        Modifier_piece_position(piece, pt);
        Modifier_piece_etat(piece, P_Prise);
   }
}

void Deplacer_piece_vers_tablier(PIECE* piece, MOYEU* moyeu, CASE* vers_case)
{
    Modifier_piece_color(piece,(moyeu->Joueur->Id==0)?P_Blanc:P_Noir);
    Modifier_piece_position(piece, Position_vers_point(vers_case->Position));
    Modifier_piece_etat(piece, P_Libre);
    vers_case->Piece=piece;
    //printf("pieces deplacer\n");
    Retirer_piece_dans_moyeu_plateau(piece, moyeu);
    //printf("piece retire dans moyeu\n");
}

bool Is_chemin_libre(CASE *de_case, int i)
{
    CASE* chemin[2]={NULL,NULL};
    bool chemin_libre=FALSE;
    if(de_case->Piece){
        if(de_case->Piece->Type==Triangle){
            switch(i){
                case 8: chemin[0]=de_case+1; break; case 9: chemin[0]=de_case-1;break;
                case 10:chemin[0]=de_case+8; break; case 11: chemin[0]=de_case-8; break;
            }
            if(!chemin[0]->Piece&&!chemin[0]->Pyramide)
                chemin_libre=TRUE;
        }
        else if(de_case->Piece->Type==Carre){
            switch(i){
                case 8: chemin[0]=de_case+1; chemin[1]=de_case+2; break; case 9: chemin[0]=de_case-1; chemin[1]=de_case-2; break;
                case 10: chemin[0]=de_case+8; chemin[1]=de_case+16; break; case 11: chemin[0]=de_case-8; chemin[1]=de_case-16; break;
            }
            if((!chemin[0]->Piece&&!chemin[0]->Pyramide)&&(!chemin[1]->Piece&&!chemin[1]->Pyramide))
                chemin_libre=TRUE;
        }
    }
    else if(de_case->Pyramide){
        switch(i){
            case 1: chemin[0]=de_case+8; break; case 2: chemin[0]=de_case+8; chemin[1]=de_case+16; break; case 4: chemin[0]=de_case-8;break; case 5: chemin[0]=de_case-8; chemin[1]=de_case-16; break;
            case 7: chemin[0]=de_case+1; break; case 8: chemin[0]=de_case+1; chemin[1]=de_case+2; break; case 10: chemin[0]=de_case-1;break; case 11: chemin[0]=de_case-1; chemin[1]=de_case-2; break;
            case 13: chemin[0]=de_case+1+8; break; case 14: chemin[0]=de_case+1+8; chemin[1]=de_case+2+16; break; case 16: chemin[0]=de_case-1+8; break; case 17: chemin[0]=de_case-1; chemin[1]=de_case-2+16;break;
            case 19: chemin[0]=de_case-1-8; break; case 20: chemin[0]=de_case-1-8; chemin[1]=de_case-2-16; break; case 22: chemin[0]=de_case+1-8;break; case 23: chemin[0]=de_case+1-8; chemin[1]=de_case+2-16;break;
            default: chemin_libre=TRUE; break;
        }
        if(chemin[0]&&!chemin[1]){
            if(!chemin[0]->Piece&&!chemin[0]->Pyramide)
                chemin_libre=TRUE;
        }
        else if(chemin[0]&&chemin[1]){
            if((!chemin[0]->Piece&&!chemin[0]->Pyramide)&&(!chemin[1]->Piece&&!chemin[1]->Pyramide))
                chemin_libre=TRUE;
        }

    }

    return chemin_libre;
}

