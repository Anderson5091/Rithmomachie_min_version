
/*
 *    RITHMOMACHIE - Created by Anderson5091 16/Avril/17.
 *
 *    .
 */
#include "Chargement.h"

 void Afficher_titre(void)
{
    ALLEGRO_BITMAP *n_titre, *titre, *separator;
    titre=al_load_bitmap("R_title.png");
    separator=al_load_bitmap("R_titre_separateur.png");
    n_titre=al_create_bitmap((int)largeur_ecran,(int)hauteur_ecran);
    al_set_target_bitmap(n_titre);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_bitmap(separator,largeur_ecran/2.0-al_get_bitmap_width(separator)/2.0,
                   hauteur_ecran/2.0-al_get_bitmap_height(separator)/2.0-5,0);
    al_draw_bitmap_region(titre,
                          0,0,
                          progression/duree*al_get_bitmap_width(titre)/2.0,al_get_bitmap_height(titre),
                          largeur_ecran/2.0-2-progression/duree*al_get_bitmap_width(titre)/2.0,hauteur_ecran/2.0-al_get_bitmap_height(titre)/2.0,0);
    al_draw_bitmap_region(titre,
                          al_get_bitmap_width(titre)-progression/duree*al_get_bitmap_width(titre)/2.0,0,
                          progression/duree*al_get_bitmap_width(titre)/2.0,al_get_bitmap_height(titre),
                          largeur_ecran/2.0+2,hauteur_ecran/2-al_get_bitmap_height(titre)/2.0,0);

    al_set_target_backbuffer(display);
    al_draw_bitmap(n_titre,0,0,0);
    al_destroy_bitmap(n_titre);
    al_destroy_bitmap(titre);
    al_destroy_bitmap(separator);

}

void Afficher_progression(void)
{
   ALLEGRO_BITMAP *n_chargement, *chargement_1, *chargement_2, *chargement_3;
   float x=683, y=683;
   chargement_1=al_load_bitmap("chargement_1.png");
   chargement_2=al_load_bitmap("chargement_2.png");
   chargement_3=al_load_bitmap("chargement_3.png");
   n_chargement=al_create_bitmap((int)largeur_ecran,(int)hauteur_ecran);
   al_set_target_bitmap(n_chargement);
   al_clear_to_color(al_map_rgba(0,0,0,0));
   al_draw_rotated_bitmap(chargement_1, al_get_bitmap_width(chargement_1)/2.0, al_get_bitmap_height(chargement_1)/2.0,
                          x, y, 4*progression/duree*ALLEGRO_PI/2.0, 0);
   al_draw_rotated_bitmap(chargement_2, al_get_bitmap_width(chargement_2)/2.0, al_get_bitmap_height(chargement_2)/2.0,
                          x, y, 6*progression/duree*ALLEGRO_PI/4.0, 0);
   al_draw_rotated_bitmap(chargement_3, al_get_bitmap_width(chargement_3)/2.0, al_get_bitmap_height(chargement_3)/2.0,
                          x, y, 8*progression/duree*ALLEGRO_PI/6.0, 0);

   al_set_target_backbuffer(display);
   al_draw_bitmap(n_chargement,0,0,0);
   al_destroy_bitmap(chargement_1);
   al_destroy_bitmap(chargement_2);
   al_destroy_bitmap(chargement_3);
   al_destroy_bitmap(n_chargement);
}

void R_chargement(void)
{
    ALLEGRO_BITMAP *logo, *titre;
    logo=al_load_bitmap("R_logo.png");
    titre=al_load_bitmap("R_title.png");

    Fond = al_load_bitmap("R_fond.png");//

    Set_progress(100.0f,0.0f);//200.0f,0.0f
    while(progression<duree)
    {

        al_set_target_backbuffer(display);
        al_draw_bitmap(Fond,0,0,0);
        Afficher_titre();
        al_flip_display();

        progression++;
    }

    al_draw_bitmap(Fond,0,0,0);
    al_draw_bitmap(titre, largeur_ecran/2-al_get_bitmap_width(titre)/2.0, hauteur_ecran/2-al_get_bitmap_height(titre)/2.0,0);
    al_flip_display();
    al_rest(1.0);

    al_draw_bitmap(Fond,0,0,0);
    al_draw_bitmap(logo, largeur_ecran/2-al_get_bitmap_width(logo)/2.0, hauteur_ecran/2-al_get_bitmap_height(logo)/2.0,0);
    al_flip_display();
    al_rest(1.0);

    Set_progress(100.0f,0.0f);//100.0f,0.0f
    while(progression<5*duree)
    {
        al_set_target_backbuffer(display);
        al_draw_bitmap(Fond,0,0,0);
        al_draw_bitmap(logo, largeur_ecran/2-al_get_bitmap_width(logo)/2.0, hauteur_ecran/2-al_get_bitmap_height(logo)/2.0,0);
        Afficher_progression();
        al_flip_display();

        progression++;
    }
    al_destroy_bitmap(logo);
    //mise en place fond
}
