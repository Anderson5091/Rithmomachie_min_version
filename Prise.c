
/*
 *    RITHMOMACHIE - Created by Anderson5091 23/Avril/17.
 *                 - Fin de creation de prise par blocage 24/Avril/2017.
 *                 - Debut de creation de prise par arithmetique 27/Avril/2017.
 *      ce module peremet de gerer l'ensemble de tous les prise possible
 *      en prenant en compte qu'une case d'agression.
 */

#include "Prise.h"
#include "Deplacement.h"
#include "Moyeu.h"

CASE* zone_en_danger[8][9];
CASE* zone_aneantie[8][9];
bool prise;
int nomb_zone_en_danger=0,nomb_zone_aneantie=0, zone_actuel;


bool Isset_prise(void){
  return prise;
}
void Set_prise(void){
   prise=TRUE;
}

void Reset_prise(void){
    prise=FALSE;
}
void Reset_zone_en_danger(void)
{
    int i, j;
    for(i=0;i<8;i++){
         for(j=0;j<9;j++)
            zone_en_danger[i][j]=NULL;
    }
    nomb_zone_en_danger=0;
    zone_actuel=0;
}

void Reset_zone_aneantie(void)
{
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<9;j++)
        zone_aneantie[i][j]=NULL;
    }
    nomb_zone_aneantie=0;
}

int Nomb_zone_en_danger(void)
{
    return nomb_zone_en_danger;
}

int Nomb_zone_aneantie(void)
{
    return nomb_zone_aneantie;
}

void Ajouter_zone_en_danger_cible(CASE* cs_en_danger)
{
    zone_en_danger[nomb_zone_en_danger][0]=cs_en_danger;//on ajoute le cible dans la case zero de la zone
    nomb_zone_en_danger++;
}

void Ajouter_dans_zone_en_danger_agresseur(int zone,int num_agresseur, CASE* nouveau_agresseur){
    zone_en_danger[zone][num_agresseur]=nouveau_agresseur;
}

void Ajouter_zone_aneantie(CASE* cs_aneantie){
    zone_aneantie[nomb_zone_aneantie][0]=cs_aneantie;
    nomb_zone_aneantie++;
}

void Ajouter_dans_zone_aneantie_agresseur(int zone,int num_agresseur, CASE* nouveau_agresseur){
    zone_aneantie[zone][num_agresseur]=nouveau_agresseur;
}

void R_Anneantie(CASE *case_agresseur, CASE *case_victime){
    CASE* temp_case=case_victime;

    Deplacer_piece_vers_moyeu_plateau(case_victime->Piece,joueur_actuel->Id);
    case_victime->Piece=NULL;
    if(case_agresseur->Piece)
        Deplacer_piece_dans_tablier(case_agresseur,case_victime);
    else if(case_agresseur->Pyramide)
        Deplacer_pyramide_dans_tablier(case_agresseur,case_victime);
}
bool Verifier_prise(CASE *cible){

    if(zone_en_danger[zone_actuel][0]==cible&&(zone_en_danger[zone_actuel][1]||zone_en_danger[zone_actuel][2]||
        zone_en_danger[zone_actuel][3]||zone_en_danger[zone_actuel][4]||zone_en_danger[zone_actuel][5]||
        zone_en_danger[zone_actuel][6]||zone_en_danger[zone_actuel][7]||zone_en_danger[zone_actuel][8]))
        return TRUE;
    else
        return FALSE;

}

bool Verifier_blocage_piece(CASE *cible, CASE* block)
{
    P_COLOR _couleur_block, couleur_block;
    int i,j,l, c, nomb_d;
    bool Blocage=FALSE, Annuller_blocage=FALSE;
    CASE *_block[3]={NULL,NULL,NULL};
    COORDTAB *liste_deplacement;
    COORDTAB position=cible->Position;
    if(cible->Piece->Type==Cercle){
        COORDTAB liste_d[4]={{position.Ligne-1,position.Colonne-1},{position.Ligne-1,position.Colonne+1},{position.Ligne+1,position.Colonne-1},{position.Ligne+1,position.Colonne+1}};
        nomb_d=1; liste_deplacement=malloc(4*sizeof(COORDTAB));    for(i=0;i<4;i++){liste_deplacement[i]=liste_d[i];printf("depl(%d,%d)     ",liste_d[i].Ligne,liste_d[i].Colonne);}printf("\n cercle endanger\n");
    }
    else if(cible->Piece->Type==Triangle){
        COORDTAB liste_d[4]={{position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne-2},{position.Ligne+2,position.Colonne},{position.Ligne-2,position.Colonne}};
        nomb_d=2; liste_deplacement=malloc(4*sizeof(COORDTAB)); for(i=0;i<4;i++){liste_deplacement[i]=liste_d[i];printf("depl(%d,%d)        ",liste_d[i].Ligne,liste_d[i].Colonne);} printf("triangle endanger\n");
    }
    else if(cible->Piece->Type==Carre){
        COORDTAB liste_d[4]={{position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-3},{position.Ligne+3,position.Colonne},{position.Ligne-3,position.Colonne}};
        nomb_d=3; liste_deplacement=malloc(4*sizeof(COORDTAB));   for(i=0;i<4;i++){liste_deplacement[i]=liste_d[i];printf("depl(%d,%d)      ",liste_d[i].Ligne,liste_d[i].Colonne);} printf("carre endanger\n");
    }
    couleur_block=(block->Piece)?block->Piece->Color:block->Pyramide->Pieces[0]->Color;
    printf("verification blocage....\n");

    for(i=0;i<4;i++){
        if(Position_vers_adresse(liste_deplacement[i])){
        printf("direction %d\n",i);
            Blocage=FALSE;
            l=liste_deplacement[i].Ligne-cible->Position.Ligne; c=liste_deplacement[i].Colonne-cible->Position.Colonne;
            printf("l:%d, c:%d\n\n",l,c);
            if(((l==0&&c>0)||(c==0&&l>0))||((l==0&&c<0)||(c==0&&l<0)))
                for(j=0;j<nomb_d;j++){
                _block[j]=cible+(j+1)*l/nomb_d*8+(j+1)*c/nomb_d; printf("block%d: %d,%d     ",j,_block[j]->Position.Ligne,_block[j]->Position.Colonne);}
            else{
                _block[0]=Position_vers_adresse(liste_deplacement[i]);printf("block%d: %d,%d     ",0,_block[0]->Position.Ligne,_block[0]->Position.Colonne);}
            printf("\n\n");
           j=0;
           printf("verifier blocage sur....:\n ");
           while(!Blocage&&j<nomb_d){
            printf("block:%d\n",j);
              if(_block[j]->Piece||_block[j]->Pyramide){
                    _couleur_block=(_block[j]->Piece)?_block[j]->Piece->Color:_block[j]->Pyramide->Pieces[0]->Color;
                    if(couleur_block==_couleur_block){
                        Blocage=TRUE; printf("blocage\n");
                    }
                    else{
                        Blocage=FALSE;  printf("piece de meme couleur\n");
                        Annuller_blocage=TRUE;
                        break;
                    }
               }else{
                    j++; printf("suivant...\n");
               }
           }
            if(j>=nomb_d){
                Blocage=FALSE;
                Annuller_blocage=TRUE;
                printf("pas de piece dan cette direction\n");
           }
           if(Blocage){
                switch(cible->Piece->Type){
                    case Cercle:    if(_block[j]->Piece){
                                        if(_block[j]->Piece->Type==Cercle){
                                            if(j+1==1){
                                            Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                                            printf("cecle ajoute comme agresseur \n");
                                            }
                                        }
                                    }
                                    else
                                        Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                    break;
                    case Triangle:  if(_block[j]->Piece){
                                        if(_block[j]->Piece->Type==Triangle){
                                            if(j+1==2){
                                                Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                                                printf("triangle(%d,%d) ajoute comme agresseur \n",_block[j]->Position.Ligne,_block[j]->Position.Colonne);
                                            }
                                        }
                                    }
                                    else
                                        Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                    break;
                    case Carre:     if(_block[j]->Piece){
                                        if(_block[j]->Piece->Type==Triangle){
                                            if(j+1==2){
                                                Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                                                printf("triangle ajoute comme agresseur \n");
                                            }
                                        }
                                        else if(_block[j]->Piece->Type==Carre){
                                            if(j+1==3){
                                                Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                                                printf("carre ajoute comme agresseur \n");
                                            }
                                        }
                                    }
                                    else
                                        Ajouter_dans_zone_en_danger_agresseur(zone_actuel,i+1,_block[j]);
                    break;
                }
           }
           if(Annuller_blocage)
                break;
        }
    }
    free(liste_deplacement);
    if(Blocage)
        printf("blocage reussi....\n");
    return Blocage;
}

bool Verifier_blocage_pyramide(CASE *cible,CASE* block)
{
    P_COLOR _couleur_block, couleur_block;
    int i,j,l, c, nomb_d;
    bool Blocage=FALSE, Annuller_blocage=FALSE;
    CASE *_block[3]={NULL,NULL,NULL};
    COORDTAB position=cible->Position;
    COORDTAB liste_glissement_pyramide[8]={{position.Ligne+3,position.Colonne},{position.Ligne-3,position.Colonne},
                                           {position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-3},
                                           {position.Ligne+3,position.Colonne+3},{position.Ligne+3,position.Colonne-3},
                                           {position.Ligne-3,position.Colonne-3},{position.Ligne-3,position.Colonne+3}};

    couleur_block=(block->Piece)?block->Piece->Color:block->Pyramide->Pieces[0]->Color;

    return Blocage;
}

void R_Prise(CASE* block)
{
    int i, j, danger;
    CASE *cible=NULL;
    P_COLOR couleur_block=(block->Piece)?block->Piece->Color:block->Pyramide->Pieces[0]->Color;
    COORDTAB position=block->Position;
    COORDTAB zone_de_danger[8][3]={
        {{position.Ligne,position.Colonne-1},{position.Ligne,position.Colonne-2},{position.Ligne,position.Colonne-3}},
        {{position.Ligne,position.Colonne+1},{position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne+3}},
        {{position.Ligne-1,position.Colonne},{position.Ligne-2,position.Colonne},{position.Ligne-3,position.Colonne}},
        {{position.Ligne+1,position.Colonne},{position.Ligne+2,position.Colonne},{position.Ligne+3,position.Colonne}},
        {{position.Ligne-1,position.Colonne-1},{position.Ligne-2,position.Colonne-2},{position.Ligne-3,position.Colonne-3}},
        {{position.Ligne-1,position.Colonne+1},{position.Ligne-2,position.Colonne+2},{position.Ligne-3,position.Colonne+3}},
        {{position.Ligne+1,position.Colonne-1},{position.Ligne+2,position.Colonne-2},{position.Ligne+3,position.Colonne-3}},
        {{position.Ligne+1,position.Colonne+1},{position.Ligne+2,position.Colonne+2},{position.Ligne+3,position.Colonne+3}}};


    Reset_zone_en_danger();
    Reset_zone_aneantie();

    printf("recuperation des zone de danger\n");

    for(i=0;i<8;i++){
        bool cible_ami=FALSE;
        j=0;
        while(!cible&&j<3&&!cible_ami){
            cible=Position_vers_adresse(zone_de_danger[i][j]);

            if(cible){
                P_COLOR couleur_cible=(cible->Piece)?cible->Piece->Color:
                                      ((cible->Pyramide)?cible->Pyramide->Pieces[0]->Color:100);
                if(couleur_cible!=couleur_block)
                    cible=cible;
                else{
                    cible_ami=TRUE;
                    cible=NULL;
                }
                if(cible){
                    if(cible->Piece){
                        if(cible->Piece->Type==Cercle)
                        {
                           if(j<1)
                               Ajouter_zone_en_danger_cible(cible);
                           //else
                                //pas de rencontre avec le cercle
                        }
                        else if(cible->Piece->Type==Triangle)
                        {
                            if(i<4&&j<2)
                                Ajouter_zone_en_danger_cible(cible);
                            //else
                                //pas de rencontre avec le triangle
                        }
                        else if(cible->Piece->Type==Carre)
                        {
                            if(i<4&&j<3)
                                Ajouter_zone_en_danger_cible(cible);
                            //else
                                //pas de rencontre avec le carre
                        }
                    }
                    else if(cible->Pyramide){//dans tous les cas la rencontre avec le pyramide sera vrai
                        Ajouter_zone_en_danger_cible(cible);
                    }
                } //fin de verification de rencontre
            }//fin de verification cible adverse
            j++; //pochain cible dans la meme direction si on est encore dans la zone de danger et il n'y a pas encore de cible
        }
        //prochaine direction
        cible=NULL;
    }//fin de la recuperation des zones en danger


    printf("verification du blocage\n");
    danger=Nomb_zone_en_danger();
    for(i=0; i<danger; i++){//recuperation des autres blocs pour chaque zone de danger
        cible=zone_en_danger[i][0];
        zone_actuel=i;

        if(cible->Piece){
            if(Verifier_blocage_piece(cible, block)){
                cible->Piece->Etat=P_Bloquer;
                if(Verifier_prise(cible)){
                    Ajouter_zone_aneantie(cible);
                    for(j=1;j<5;j++){
                        if(zone_en_danger[i][j]){
                            Ajouter_dans_zone_aneantie_agresseur(i,j,zone_en_danger[i][j]);
                        }
                    }
                }
            }
            else if(Try_Out_arithmetique(cible, block)){
                //R_Arithmetique(cible,block,i);
            }
            cible=NULL;
        }
        else{
            if(cible->Pyramide->Compacite){
                printf("pyramide compact\n");
                if(Verifier_blocage_pyramide(cible,block)){
                    Ajouter_zone_aneantie(cible);
                }
                else{
                   printf("verification arithmetique pyramide\n");
                  // R_Arithmetique(cible,block,i);
                }
                cible=NULL;
            }
            else{//cible pyramide et compacite:faux , a revoirrrr
                int ref=0; bool blocage_piece_v=TRUE;
                cible->Piece=cible->Pyramide->Pieces[ref];
                blocage_piece_v=Verifier_blocage_piece(cible,block);
                while(blocage_piece_v&&cible->Pyramide->Pieces[ref]){
                    //tant que le blocage reste vraie trouver une porte de sortie
                    cible->Piece=cible->Pyramide->Pieces[ref];
                    blocage_piece_v=Verifier_blocage_piece(cible,block);
                    ref++;
                }
                cible->Piece=NULL;

                if(blocage_piece_v){
                    Ajouter_zone_aneantie(cible);
                    //
                }
                else{
                    //R_Arithmetique(cible,block,i);
                }
                cible=NULL;
            }
        }
    }
    //traitement des zone anneanties
    danger=Nomb_zone_aneantie();
    cible=NULL;

    for(i=0; i<danger; i++)
    {
        cible=zone_aneantie[i][0];
        //gere le cible actuel pour le moment on eface les pieces

        if(cible->Piece)
        {
            Set_prise();
        }
        else if(cible->Pyramide)
        {
            j=0;
            while(cible->Pyramide->Pieces[j])
            {
                Deplacer_piece_vers_moyeu_plateau(cible->Pyramide->Pieces[j],joueur_actuel->Id);
                cible->Pyramide->Pieces[j]=NULL;
                j++;
            }
            cible->Pyramide=NULL;
        }
        cible=NULL;
    }

}

/***************************************************************************/
bool Compte_est_bon(int cible, int nomb_1, int nomb_2)
{
    float _cible, _nomb_1, _nomb_2;
    if((_cible==(_nomb_1+_nomb_2))||(_cible==(_nomb_1-_nomb_2))||(_cible==(_nomb_2-_nomb_1)))
        return TRUE;
    else if((_cible==_nomb_1*_nomb_2)||(_cible==(_nomb_1/_nomb_2))||(_cible==(_nomb_2/_nomb_1)))
        return TRUE;
    else if(_cible==(_nomb_1+_nomb_2)/2.0)
        return TRUE;
    else
        return FALSE;
}

bool Try_Out_arithmetique(CASE* cible,CASE* tire){
    if(zone_en_danger[zone_actuel][0]==cible&&(zone_en_danger[zone_actuel][1]==tire||zone_en_danger[zone_actuel][2]==tire||
        zone_en_danger[zone_actuel][3]==tire||zone_en_danger[zone_actuel][4]==tire||zone_en_danger[zone_actuel][5]==tire||
        zone_en_danger[zone_actuel][6]==tire||zone_en_danger[zone_actuel][7]==tire||zone_en_danger[zone_actuel][8]==tire))
        return TRUE;
    else
        return FALSE;
}

void R_Arithmetique(CASE* cible, CASE* tire, int ordre)
{
    CASE* compte_agresseur;
    bool le_compte_est_bon=FALSE;
    int nomb_0, nomb_1, nomb_2, i, j, zone;
    P_TYPE type_tire=(tire->Piece)?tire->Piece->Type:tire->Pyramide->Pieces[0]->Type;//

    if(cible->Piece){
       nomb_0=cible->Piece->Poids;
       nomb_1=(tire->Piece)?tire->Piece->Poids:tire->Pyramide->Poids;

       if(cible->Piece->Type!=type_tire&&nomb_0==nomb_1){
           le_compte_est_bon=TRUE;
           zone=Nomb_zone_aneantie();
           Ajouter_zone_aneantie(cible);
           Ajouter_dans_zone_aneantie_agresseur(zone,1,tire);

       }
       else{
            j=1;
            while(!le_compte_est_bon&&zone_en_danger[ordre][j]){
                if(zone_en_danger[ordre][j]!=tire){
                   nomb_2=(zone_en_danger[ordre][j]->Piece)?zone_en_danger[ordre][j]->Piece->Poids:
                                                            zone_en_danger[ordre][j]->Pyramide->Poids;
                   le_compte_est_bon=Compte_est_bon(nomb_0, nomb_1, nomb_2);
                }

                if(le_compte_est_bon){
                    compte_agresseur=zone_en_danger[ordre][j];
                    zone=Nomb_zone_aneantie();
                    Ajouter_zone_aneantie(cible);
                    Ajouter_dans_zone_aneantie_agresseur(zone,1,tire);
                    Ajouter_dans_zone_aneantie_agresseur(zone,2,compte_agresseur);
                }
                else
                    j++;
            }
       }
    }
    else if(cible->Pyramide){
        printf("Arith metique cible pyramide\n");
        nomb_0=cible->Pyramide->Poids;
        nomb_1=(tire->Piece)?tire->Piece->Poids:tire->Pyramide->Poids;
            j=1;
            while(!le_compte_est_bon&&zone_en_danger[ordre][j]){
                if(zone_en_danger[ordre][j]!=tire){
                   nomb_2=(zone_en_danger[ordre][j]->Piece)?zone_en_danger[ordre][j]->Piece->Poids:
                                                            zone_en_danger[ordre][j]->Pyramide->Poids;
                   le_compte_est_bon=Compte_est_bon(nomb_0, nomb_1, nomb_2);
                }

                if(le_compte_est_bon){
                    compte_agresseur=zone_en_danger[ordre][j];
                    zone=Nomb_zone_aneantie();
                    Ajouter_zone_aneantie(cible);
                    Ajouter_dans_zone_aneantie_agresseur(zone,1,tire);
                    Ajouter_dans_zone_aneantie_agresseur(zone,2,compte_agresseur);
                }
                else
                    j++;
            }
            if(!le_compte_est_bon){
                for(i=0; i<6; i++)
                {
                    if(cible->Pyramide->Pieces[i]){
                        nomb_0=cible->Pyramide->Pieces[i]->Poids;
                        if(type_tire!=cible->Pyramide->Pieces[i]->Type&&nomb_0==nomb_1){
                           le_compte_est_bon=TRUE;
                           Deplacer_piece_vers_moyeu_plateau(cible->Pyramide->Pieces[i],joueur_actuel->Id);
                           Retirer_piece_dans_pyramide(cible->Pyramide->Pieces[i], cible->Pyramide);
                           Re_init_moyeu_boutons(&Moyeux[(joueur_actuel->Id==0)?1:0]);
                        }
                        while(!le_compte_est_bon&&zone_en_danger[ordre][j]){
                            if(zone_en_danger[ordre][j]!=tire){
                               nomb_2=(zone_en_danger[ordre][j]->Piece)?zone_en_danger[ordre][j]->Piece->Poids:
                                                                        zone_en_danger[ordre][j]->Pyramide->Poids;
                               le_compte_est_bon=Compte_est_bon(nomb_0, nomb_1, nomb_2);
                            }
                            if(le_compte_est_bon){
                                Deplacer_piece_vers_moyeu_plateau(cible->Pyramide->Pieces[i],joueur_actuel->Id);
                                Retirer_piece_dans_pyramide(cible->Pyramide->Pieces[i], cible->Pyramide);
                                Re_init_moyeu_boutons(&Moyeux[(joueur_actuel->Id==0)?1:0]);
                            }
                            else
                                j++;
                        }
                    }
                    if(le_compte_est_bon)
                        break;
                }
            }
    }//fin arithmetique cible type pyramide
}

bool fin_prise(void)
{
    if(((!zone_aneantie[0][1]&&!zone_aneantie[0][2]&&!zone_aneantie[0][3]&&!zone_aneantie[0][4]&&!zone_aneantie[0][5]&&!zone_aneantie[0][6]&&!zone_aneantie[0][7]&&!zone_aneantie[0][8])&&
        (!zone_aneantie[1][1]&&!zone_aneantie[1][2]&&!zone_aneantie[1][3]&&!zone_aneantie[1][4]&&!zone_aneantie[1][5]&&!zone_aneantie[1][6]&&!zone_aneantie[1][7]&&!zone_aneantie[1][8])&&
        (!zone_aneantie[2][1]&&!zone_aneantie[2][2]&&!zone_aneantie[2][3]&&!zone_aneantie[2][4]&&!zone_aneantie[2][5]&&!zone_aneantie[2][6]&&!zone_aneantie[2][7]&&!zone_aneantie[2][8])&&
        (!zone_aneantie[3][1]&&!zone_aneantie[3][2]&&!zone_aneantie[3][3]&&!zone_aneantie[3][4]&&!zone_aneantie[3][5]&&!zone_aneantie[3][6]&&!zone_aneantie[3][7]&&!zone_aneantie[3][8])&&
        (!zone_aneantie[4][1]&&!zone_aneantie[4][2]&&!zone_aneantie[4][3]&&!zone_aneantie[4][4]&&!zone_aneantie[4][5]&&!zone_aneantie[4][6]&&!zone_aneantie[4][7]&&!zone_aneantie[4][8])&&
        (!zone_aneantie[5][1]&&!zone_aneantie[5][2]&&!zone_aneantie[5][3]&&!zone_aneantie[5][4]&&!zone_aneantie[5][5]&&!zone_aneantie[5][6]&&!zone_aneantie[5][7]&&!zone_aneantie[5][8])&&
        (!zone_aneantie[6][1]&&!zone_aneantie[6][2]&&!zone_aneantie[6][3]&&!zone_aneantie[6][4]&&!zone_aneantie[6][5]&&!zone_aneantie[6][6]&&!zone_aneantie[6][7]&&!zone_aneantie[6][8])&&
        (!zone_aneantie[7][1]&&!zone_aneantie[7][2]&&!zone_aneantie[7][3]&&!zone_aneantie[7][4]&&!zone_aneantie[7][5]&&!zone_aneantie[7][6]&&!zone_aneantie[7][7]&&!zone_aneantie[7][8]))||
        (!zone_aneantie[0][0]&&!zone_aneantie[1][0]&&!zone_aneantie[2][0]&&!zone_aneantie[3][0]&&!zone_aneantie[4][0]&&!zone_aneantie[5][0]&&!zone_aneantie[6][0]&&!zone_aneantie[7][0]))
        return TRUE;
    else
        return FALSE;
}
