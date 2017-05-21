
/*
 *    RITHMOMACHIE - Created by Anderson5091 01/Avril/17.
 *
 *    .
 */

#include "GUI.h"
#include "Event.h"

 BOUTON *Creer_bouton(float x, float y, ALLEGRO_BITMAP *image, void* action){
    BOUTON *bouton = malloc(sizeof(BOUTON));
    bouton->X = x;
    bouton->Y = y;
    bouton->W=al_get_bitmap_width(image)/2.0;
    bouton->H=al_get_bitmap_height(image);
    bouton->Image = image;
    bouton->Etat= B_Normal;
    bouton->Action=action;
    return bouton;
}

void Afficher_bouton(BOUTON *bouton){

    float x, y;
    x = bouton->X - bouton->W/2.0;
    y = bouton->Y - bouton->H/2.0;
    if(bouton->Etat==B_Normal)
    al_draw_bitmap_region(bouton->Image,0, 0, bouton->W, bouton->H, x, y, 0);
    else
    al_draw_bitmap_region(bouton->Image, bouton->W, 0,bouton->W, bouton->H, x, y, 0);
}

void Actualiser_bouton(BOUTON *bouton)
{
    if (souris_x() > ( bouton->X - bouton->W/ 2.0) && souris_x() < (bouton->X + bouton->W / 2.0)) {
        if (souris_y() > (bouton->Y - bouton->H / 2.0) && souris_y() < (bouton->Y + bouton->H / 2.0)) {
            bouton->Etat =B_Survol ;
            if (souris_bouton_presse(1)) {
                bouton->Etat=B_Actif;
                bouton->Action();
            }
        } else {
            bouton->Etat =B_Normal ;
        }
    } else {
        bouton->Etat =B_Normal ;
    }
}

void Detruire_bouton(BOUTON *bouton)
{
    al_destroy_bitmap(bouton->Image);
    //free(bouton);
    bouton=NULL;
}

