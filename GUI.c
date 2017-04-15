
/*
 *    RITHMOMACHIE - Created by Anderson5091 01/Avril/17.
 *
 *    .
 */

#include "GUI.h"

 BOUTON *Init_bouton(float x, float y, ALLEGRO_BITMAP *main) {
    BOUTON *bouton = malloc(sizeof(BOUTON));
    bouton->X = x;
    bouton->Y = y;
    bouton->Main = main;
    bouton->Etat= Normal;
    return bouton;
}

void Afficher_bouton(BOUTON *bouton){
    float x, y;

    x = bouton->X - al_get_bitmap_width(bouton->Main)/4.0;
    y = bouton->Y - al_get_bitmap_height(bouton->Main)/4.0;
    if(bouton->Etat==Normal)
    al_draw_bitmap_region(bouton->Main, x, y, 0, 0, 0, 0, 0);
    else if(bouton->Etat==Survol)
    al_draw_bitmap_region(bouton->Main, x, y, 0, 0, 0, 0, 0);
}

AFFICHAGE * Init_affichage(char *name, AFFICHAGE *parent, int x, int y, int w, int h){
    AFFICHAGE *affichage = malloc(sizeof(AFFICHAGE));
    affichage->Bmp = al_create_bitmap(w, h);
    affichage->Parent = (parent == 0) ? NULL : parent;
    affichage->Name = name;
    affichage->X = x;
    affichage->Y = y;
    affichage->W = w;
    affichage->H = h;
}

void Afficher_affichage(AFFICHAGE *affichage){
    ALLEGRO_BITMAP *last_bmp = al_get_target_bitmap();
    if (affichage->Parent) al_set_target_bitmap(affichage->Parent->Bmp);
    al_draw_bitmap(affichage->Bmp, affichage->X, affichage->Y, 0);
    al_set_target_bitmap(last_bmp);
}

void Detruire_affichage(AFFICHAGE *affichage){
    al_destroy_bitmap(affichage->Bmp);
    free(affichage);
}

