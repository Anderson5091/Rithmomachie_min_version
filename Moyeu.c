
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/Avril/17.
 *
 *    .
 */

#include"Moyeu.h"
#include"Event.h"

MOYEU Moyeux[JOUEUR_MAX];
static JOUEUR Joueurs[JOUEUR_MAX];
JOUEUR *joueur_actuel;

/***************** joueur *****************/
JOUEUR* Trouver_joueur(int id)
{
    return &Joueurs[id];
}

void Changer_joueur(void)
{
   joueur_actuel=(joueur_actuel==&Joueurs[0])?&Joueurs[1]:&Joueurs[0];
}

void Modifier_joueur_name(JOUEUR *joueur, const char* nouveau_nom){
    joueur->Name=nouveau_nom;
}

void Modifier_joueur_Image(JOUEUR *joueur,ALLEGRO_BITMAP* nouvelle_image){
    joueur->Image=nouvelle_image;
}

void Init_joueur(JOUEUR *joueur,PYRAMIDE *pyramide){

    int id=(joueur==&Joueurs[0])?0:1;

    joueur->Id=id;
    joueur->Name=(id=0)?"JOUEUR 1":"JOUEUR 2";
    joueur->Image=NULL;
    joueur->Pyramide=pyramide;

    id++;

}

void Actualiser_joueurs_pyramide(void){
    ALLEGRO_FONT* police_poids;
    ALLEGRO_BITMAP* pyramide_moyeu_joueur_1;
    ALLEGRO_BITMAP* pyramide_moyeu_joueur_2;
    int pyramide_1_poids,pyramide_2_poids,i;

        police_poids=al_load_font("Roboto-Light.ttf",10,0);
        pyramide_moyeu_joueur_1=al_load_bitmap("moyeu_pyramide_1.png");
        pyramide_moyeu_joueur_2=al_load_bitmap("moyeu_pyramide_2.png");

    if(joueur_actuel->Id==0){
        al_draw_bitmap_region(pyramide_moyeu_joueur_1, 40, 0, 40, 40, 32.667, 341, 0);
        al_draw_bitmap_region(pyramide_moyeu_joueur_2, 0, 0, 40, 40, 1292.968, 341, 0);
    }
    else{
        al_draw_bitmap_region(pyramide_moyeu_joueur_1,0, 0, 40, 40, 32.667, 341, 0);
        al_draw_bitmap_region(pyramide_moyeu_joueur_2,40, 0, 40, 40, 1292.968, 341, 0);
    }

    for(i=0;i<6;i++){
            if(Moyeux[0].Joueur->Pyramide->Pieces[i])
                pyramide_1_poids=pyramide_1_poids+Moyeux[0].Joueur->Pyramide->Pieces[i]->Poids;
            if(Moyeux[1].Joueur->Pyramide->Pieces[i])
                pyramide_2_poids=pyramide_2_poids+Moyeux[1].Joueur->Pyramide->Pieces[i]->Poids;
    }

    al_draw_textf(police_poids, al_map_rgb(0,0,0),52.667,357, ALLEGRO_ALIGN_CENTRE,
                     "%d", pyramide_1_poids);
    al_draw_textf(police_poids, al_map_rgb(255,255,255),1312.968,357, ALLEGRO_ALIGN_CENTRE,
                      "%d", pyramide_2_poids);

    if(Moyeux[0].Joueur->Pyramide->Poids==0){

    }else if(Moyeux[1].Joueur->Pyramide->Poids==0){
    }
    al_destroy_font(police_poids);
    al_destroy_bitmap(pyramide_moyeu_joueur_1);
    al_destroy_bitmap(pyramide_moyeu_joueur_2);

}
/***************** Moyeu *****************/

void Init_moyeu(JOUEUR *joueur, float dx, float dy){
    ALLEGRO_BITMAP* bouton_image=NULL;
    int i, id=(joueur->Id==0)?0:1;
    Moyeux[id].X=dx;
    Moyeux[id].Y=dy;
    Moyeux[id].Joueur=joueur;
    //printf("joueur id:%d\n",id);
    Init_moyeu_boutons(&Moyeux[id]);
}

void Actualiser_moyeux(void){
    extern int fin;
    ALLEGRO_BITMAP *Buffer_moyeux_plateau=NULL;
    Buffer_moyeux_plateau=al_create_bitmap(largeur_ecran,hauteur_ecran);
    al_set_target_bitmap(Buffer_moyeux_plateau);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    Actualiser_moyeux_boutons();
    Afficher_moyeux_plateau();
    Actualiser_joueurs_pyramide();

    if (souris_bouton_relache(1)){
        PIECE *piece_selectionnee=NULL;
        COORDPOINT pt,coin_sup, coin_inf;
        pt.X = souris_x();
        pt.Y= souris_y();
        int moyeu=0, i, j;

        //printf("selectionner piece dans plateau encours... \n");//
        //printf("%f %f",pt.X , pt.Y);//
        moyeu=joueur_actuel->Id;
        for ( i = 0; i<PLATEAU_LIGNE_MAX; i++){
                j=0;
                while((Moyeux[moyeu].Plateau[i][j]&&j<PLATEAU_COLONNE_MAX)&&(!piece_selectionnee)){
                        coin_sup.X=Moyeux[moyeu].Plateau[i][j]->Position.X-20;
                        coin_sup.Y=Moyeux[moyeu].Plateau[i][j]->Position.Y-20;
                        coin_inf.X=Moyeux[moyeu].Plateau[i][j]->Position.X+20;
                        coin_inf.Y=Moyeux[moyeu].Plateau[i][j]->Position.Y+20;

                        if((pt.X>coin_sup.X&&pt.X<coin_inf.X)&&(pt.Y>coin_sup.Y&&pt.Y<coin_inf.Y)){
                            piece_selectionnee=Moyeux[moyeu].Plateau[i][j];
                            Set_deplacer_de_moyeux(piece_selectionnee);
                        }
                        else
                            j++;
                }
                if(piece_selectionnee)
                    break;
        }
    }
    if(Isset_deplacer_de_moyeux())
        Marquer_piece_plateau_selectionnee(Deplacer_de_moyeux());

    al_set_target_backbuffer(display);
    al_draw_bitmap(Buffer_moyeux_plateau,0,0,0);
    al_destroy_bitmap(Buffer_moyeux_plateau);
    Buffer_moyeux_plateau=NULL;
}

/***************** Moyeu Boutons *****************/
int moyeu_bouton;
BOUTON *bouton_reference[2];

void Init_moyeu_boutons(MOYEU* moyeu)
{
    ALLEGRO_BITMAP* bouton_image=NULL;
    ALLEGRO_FONT* police_boutons_poids=al_load_font("Roboto-Light.ttf",8,0);
    int i, id=moyeu->Joueur->Id;
    float dx=(id==0)?82:1283, dy=361;
    char path[30];

        i=0;
        while(moyeu->Joueur->Pyramide->Pieces[i]){
                if(moyeu->Joueur->Pyramide->Pieces[i]->Type==Cercle){
                    snprintf(path,30,"moyeu_%d_bouton_cercle.png",id+1);
                }
                else if(moyeu->Joueur->Pyramide->Pieces[i]->Type==Triangle){
                    snprintf(path,30,"moyeu_%d_bouton_triangle.png",id+1);
                }
                else if(moyeu->Joueur->Pyramide->Pieces[i]->Type==Carre){
                    snprintf(path,30,"moyeu_%d_bouton_carre.png",id+1);
                }
                bouton_image=al_load_bitmap(path);
                al_set_target_bitmap(bouton_image);
                al_draw_textf(police_boutons_poids,(id==0)?al_map_rgb(0,0,0):al_map_rgb(255,255,255),7.5,7.5-4,
                              ALLEGRO_ALIGN_CENTRE,"%d", moyeu->Joueur->Pyramide->Pieces[i]->Poids);
                al_draw_textf(police_boutons_poids,(id==0)?al_map_rgb(0,0,0):al_map_rgb(255,255,255),22.5,7.5-4,
                              ALLEGRO_ALIGN_CENTRE,"%d", moyeu->Joueur->Pyramide->Pieces[i]->Poids);
                Moyeux[id].Boutons[i]=Creer_bouton((id==0)?dx+i*17:dx-i*17,dy, bouton_image, moyeu_bouton_action);
                //printf("bouton%d\n",i);
            i++;
        }
        //printf("moyeu%d boutons\n",id);
    al_destroy_font(police_boutons_poids);
}

void Re_init_moyeu_boutons(MOYEU* moyeu)
{
    Detruire_moyeu_boutons(moyeu);
    Init_moyeu_boutons(moyeu);
    //printf("moyeu reinitialiser\n");

}

void Detruire_moyeu_boutons(MOYEU *moyeu)
{
    int i;
    for(i=0;i<6;i++){
        if(moyeu->Boutons[i]){
            Detruire_bouton(moyeu->Boutons[i]);
            //printf("bouton %d detruit\n",i);
        }
    }
}

void Detruire_moyeux_boutons(void)
{
    int i;
    for(i=0;i<2;i++){
        for(moyeu_bouton=0; moyeu_bouton<6; moyeu_bouton++){
            if(Moyeux[i].Boutons[moyeu_bouton]){
                Detruire_bouton(Moyeux[i].Boutons[moyeu_bouton]);
            }
        }
    }
}

void moyeu_bouton_action(void){
    if(!joueur_actuel->Pyramide->Compacite){
        Modifier_pyramide_reference(Moyeux[joueur_actuel->Id].Joueur->Pyramide,
                                joueur_actuel->Pyramide->Pieces[moyeu_bouton]);
        bouton_reference[joueur_actuel->Id]=Moyeux[joueur_actuel->Id].Boutons[moyeu_bouton];

    }
}

void Actualiser_moyeux_boutons(void)
{
    int moyeu=0;

    for(moyeu=0;moyeu<2;moyeu++){
        for(moyeu_bouton=0; moyeu_bouton<6; moyeu_bouton++){
            if(Moyeux[moyeu].Boutons[moyeu_bouton]&&Moyeux[moyeu].Joueur->Pyramide->Pieces[moyeu_bouton]){
                if(bouton_reference[moyeu]!=Moyeux[moyeu].Boutons[moyeu_bouton])
                    Actualiser_bouton(Moyeux[moyeu].Boutons[moyeu_bouton]);
                Afficher_bouton(Moyeux[moyeu].Boutons[moyeu_bouton]);
            }
        }
    }
}

/***************** Moyeu Plateau *****************/
void Reordonner_moyeu_plateau(MOYEU* moyeu){
    int i, j;
    float dx=(moyeu->Joueur->Id==0)?26.286:1340.286, dy=449.34; COORDPOINT pt;
    for(i=0;i<PLATEAU_LIGNE_MAX;i++){
            j=0;
        while((!moyeu->Plateau[i][j]&&moyeu->Plateau[i][j+1])&&j<PLATEAU_COLONNE_MAX){
            pt.X=(moyeu->Joueur->Id==0)?dx+j*40:dx-j*40; pt.Y=dy+i*40;
            moyeu->Plateau[i][j]=moyeu->Plateau[i][j+1];
            Modifier_piece_position(moyeu->Plateau[i][j+1],pt);
            moyeu->Plateau[i][j+1]=NULL;
            j++;
        }
    }
}

void Retirer_piece_dans_moyeu_plateau(PIECE* piece, MOYEU* moyeu){
    int i,j=0;
    for(i=0; i<PLATEAU_LIGNE_MAX; i++){
        j=0;
        while((moyeu->Plateau[i][j]!=piece)&&j<PLATEAU_COLONNE_MAX){
            j++;
        }
        if(j<PLATEAU_COLONNE_MAX){
            moyeu->Plateau[i][j]=NULL;
    //printf("reordonner moyeu");
            Reordonner_moyeu_plateau(moyeu);
            break;
        }
    }
}

void Afficher_moyeux_plateau(void){
    int i, j, moyeu;
    for(moyeu=0;moyeu<2;moyeu++){
        for(i=0; i<PLATEAU_LIGNE_MAX;i++){
                j=0;
                while(Moyeux[moyeu].Plateau[i][j]){
                    al_draw_bitmap(Moyeux[moyeu].Plateau[i][j]->Image,
                                   Moyeux[moyeu].Plateau[i][j]->Position.X-DIM_PIECE/2.0,
                                   Moyeux[moyeu].Plateau[i][j]->Position.Y-DIM_PIECE/2.0,0);
                    j++;
                }
            }
        //printf("Affichage plateau%d reussi\n",moyeu);
    }
}

void Marquer_piece_plateau_selectionnee(PIECE* piece)
{
    ALLEGRO_COLOR Color_border_p;

    if(piece){
            Color_border_p=al_map_rgb(43, 96, 127);

            if(piece->Type==Cercle)
               al_draw_circle(piece->Position.X,piece->Position.Y,DIM_PIECE/2.0,Color_border_p,4);
            else if(piece->Type==Carre)
                al_draw_rectangle(piece->Position.X-DIM_PIECE/2.0,piece->Position.Y-DIM_PIECE/2.0,piece->Position.X+DIM_PIECE/2.0,piece->Position.Y+DIM_PIECE/2.0,Color_border_p,4);
            else if(piece->Type==Triangle)
                al_draw_triangle(piece->Position.X,piece->Position.Y-DIM_PIECE/2.0,piece->Position.X+DIM_PIECE/2.0,piece->Position.Y+DIM_PIECE/2.0,piece->Position.X-DIM_PIECE/2.0,piece->Position.Y+DIM_PIECE/2.0,Color_border_p,4);

       }
}

