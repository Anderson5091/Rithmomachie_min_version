
/*
 *    RITHMOMACHIE - Created by Anderson5091 03/mai/17.
 *
 *    .
 */
 #include "Rithmomachie_Data.h"
 #include "Tablier.h"
 #include "Piece.h"
 #include "Prise.h"

 void GUX_deplacement_piece(CASE* cs)
{
    bool pyramide_piece=(cs->Pyramide)?TRUE:FALSE;
    int i, nomb_d;
    COORDTAB *liste_deplacement;
    COORDTAB position=cs->Position;

        if(cs->Piece->Type==Cercle){
            COORDTAB liste_d[4]={{position.Ligne-1,position.Colonne-1},{position.Ligne-1,position.Colonne+1},{position.Ligne+1,position.Colonne-1},{position.Ligne+1,position.Colonne+1}};
            nomb_d=4; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB));    for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i]; if(pyramide_piece){pyramide_piece=FALSE;}
        }
        else if(cs->Piece->Type==Carre){
            COORDTAB liste_d[12]={{position.Ligne+1,position.Colonne+3},{position.Ligne+1,position.Colonne-3},{position.Ligne-1,position.Colonne+3},{position.Ligne-1,position.Colonne-3},
                                  {position.Ligne+3,position.Colonne+1},{position.Ligne+3,position.Colonne-1},{position.Ligne-3,position.Colonne+1},{position.Ligne-3,position.Colonne-1},
                                  {position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-3},{position.Ligne+3,position.Colonne},{position.Ligne-3,position.Colonne}};
            nomb_d=12; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB));   for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i];
        }
        else if(cs->Piece->Type==Triangle){
            COORDTAB liste_d[12]={{position.Ligne+1,position.Colonne+2},{position.Ligne+1,position.Colonne-2},{position.Ligne-1,position.Colonne+2},{position.Ligne-1,position.Colonne-2},
                                  {position.Ligne+2,position.Colonne+1},{position.Ligne+2,position.Colonne-1},{position.Ligne-2,position.Colonne+1},{position.Ligne-2,position.Colonne-1},
                                  {position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne-2},{position.Ligne+2,position.Colonne},{position.Ligne-2,position.Colonne}};
            nomb_d=12; liste_deplacement=malloc(nomb_d*sizeof(COORDTAB)); for(i=0;i<nomb_d;i++)liste_deplacement[i]=liste_d[i];
        }
    nomb_d=(cs->Piece->Type==Cercle)?8:nomb_d;
    for(i=0;i<nomb_d-4;i++){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
                if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                    if(!Position_vers_adresse(liste_deplacement[i])->Piece&&!Position_vers_adresse(liste_deplacement[i])->Pyramide){
                        if(!pyramide_piece) al_draw_filled_circle(Position_vers_point(liste_deplacement[i]).X,Position_vers_point(liste_deplacement[i]).Y,4,al_map_rgb(43, 96, 127));
                        //else al_draw_filled_circle(Position_vers_point(liste_deplacement[i]).X,Position_vers_point(liste_deplacement[i]).Y,4,al_map_rgb(255, 0, 0));
                }
            }
        }
    }
    for(i=8;i<nomb_d;i++){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
                if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                    if((!Position_vers_adresse(liste_deplacement[i])->Piece&&!Position_vers_adresse(liste_deplacement[i])->Pyramide)
                        &&(Is_chemin_libre(cs,i))){
                        al_draw_filled_circle(Position_vers_point(liste_deplacement[i]).X,Position_vers_point(liste_deplacement[i]).Y,4,al_map_rgb(43, 96, 127));
                }
            }
        }
    }

    free(liste_deplacement);
}

void GUX_deplacement_pyramide(CASE* cs){
  int i, nomb_d=24;
    COORDTAB position=cs->Position;
    COORDTAB liste_deplacement[24]={{position.Ligne+1,position.Colonne},{position.Ligne+2,position.Colonne},{position.Ligne+3,position.Colonne},{position.Ligne-1,position.Colonne},{position.Ligne-2,position.Colonne},{position.Ligne-3,position.Colonne},
        {position.Ligne,position.Colonne+1},{position.Ligne,position.Colonne+2},{position.Ligne,position.Colonne+3},{position.Ligne,position.Colonne-1},{position.Ligne,position.Colonne-2},{position.Ligne,position.Colonne-3},
        {position.Ligne+1,position.Colonne+1},{position.Ligne+2,position.Colonne+2},{position.Ligne+3,position.Colonne+3},{position.Ligne+1,position.Colonne-1},{position.Ligne+2,position.Colonne-2},{position.Ligne+3,position.Colonne-3},
        {position.Ligne-1,position.Colonne-1},{position.Ligne-2,position.Colonne-2},{position.Ligne-3,position.Colonne-3},{position.Ligne-1,position.Colonne+1},{position.Ligne-2,position.Colonne+2},{position.Ligne-3,position.Colonne+3}};

    for(i=0;i<24;i++){
        if(liste_deplacement[i].Colonne<TABLIER_COLONNE_MAX&&liste_deplacement[i].Ligne<TABLIER_LIGNE_MAX){
                if(liste_deplacement[i].Colonne>=0&&liste_deplacement[i].Ligne>=0){
                    if((!Position_vers_adresse(liste_deplacement[i])->Piece&&!Position_vers_adresse(liste_deplacement[i])->Pyramide)
                        &&(Is_chemin_libre(cs,i))){
                        al_draw_filled_circle(Position_vers_point(liste_deplacement[i]).X,Position_vers_point(liste_deplacement[i]).Y,4,al_map_rgb(43, 96, 127));
                }
            }
        }
    }
}

void GUX_deplacement_possible(CASE* cs){

   if(cs->Piece)
       GUX_deplacement_piece(cs);
   else if(cs->Pyramide){
       if(cs->Pyramide->Compacite)
           GUX_deplacement_pyramide(cs);
       else{
            if(cs->Pyramide->Reference){
                cs->Piece=cs->Pyramide->Reference;
                GUX_deplacement_piece(cs); cs->Piece=NULL;
            }
       }
   }
}

void GUX_zone_aneantie(void){

    int i,j; float dx, dy;

    for(i=0;i<Nomb_zone_aneantie();i++){
         if(zone_aneantie[i][0]){
            dx=Position_vers_point(zone_aneantie[i][0]->Position).X;
            dy=Position_vers_point(zone_aneantie[i][0]->Position).Y;
            al_draw_filled_rectangle(dx-DIM_CASE/2.0,dy-DIM_CASE/2.0,dx+DIM_CASE/2.0,dy+DIM_CASE/2.0,al_map_rgba(255,0,0,90));
            for(j=1;j<9;j++){
               if(zone_aneantie[i][j]){
                dx=Position_vers_point(zone_aneantie[i][j]->Position).X;
                dy=Position_vers_point(zone_aneantie[i][j]->Position).Y;
                al_draw_filled_rectangle(dx-DIM_CASE/2.0,dy-DIM_CASE/2.0,dx+DIM_CASE/2.0,dy+DIM_CASE/2.0,al_map_rgb(67, 146, 192));
               }
            }
         }
    }
}

void GUX_remplacement_possible(CASE cs){
    int i,j; float dx, dy;
    for(i=0; i<8;i++){
        j=1;
       for(j=1; j<9;j++){
           if(zone_aneantie[i][j]){
               if(zone_aneantie[i][j]->Piece==cs.Piece||zone_aneantie[i][j]->Pyramide==cs.Pyramide){
                dx=Position_vers_point(zone_aneantie[i][0]->Position).X;
                dy=Position_vers_point(zone_aneantie[i][0]->Position).Y;
                al_draw_filled_rectangle(dx-DIM_CASE/2.0,dy-DIM_CASE/2.0,dx+DIM_CASE/2.0,dy+DIM_CASE/2.0,al_map_rgb(27, 254, 191));
               }
           }
       }
    }
}
void GUX_zone_en_danger(void)
{

    //for()
}



