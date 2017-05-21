
/*
 *    RITHMOMACHIE - Created by Anderson5091 15/Avril/17.
 *
 *    .
 */
 #include "Menu.h"
 #include "GUI.h"
 #include "Jeu.h"

BOUTON *menu_bouton_play, *menu_bouton_options, *menu_bouton_quitter, *sub_menu_quitter, *sub_menu_annuller;


void Init_sub_menu_jouer(void)
{

}

void Actualiser_sub_menu_jouer(void)
{

}

 void Detruire_sub_menu_jouer(void)
 {

 }

void Init_sub_menu_options(void)
{

}

void Actualiser_sub_menu_options(void)
{

}

void Detruire_sub_menu_options(void)
{

}

void Init_sub_menu_quitter(void)
{
    activite_encours=R_ACTIVITE_QUITTER;
}

void Actualiser_sub_menu_quitter(void)
{

}

void R_actualiser_sub_menu_quitter(void)
{
    al_draw_bitmap(Fond,0,0,0);
    Actualiser_sub_menu_quitter();
    al_flip_display();//
}

void Detruire_sub_menu_quitter(void)
{

}
/***********************************************/
 void Init_menu_principal(void)
 {
     printf("creation des boutons\n");
     menu_bouton_play=Creer_bouton(470,384,al_load_bitmap("bouton_jouer.png"),Init_jeu);
     menu_bouton_options=Creer_bouton(682,384,al_load_bitmap("bouton_options.png"),Init_jeu);
     menu_bouton_quitter=Creer_bouton(896,384,al_load_bitmap("bouton_quitter.png"),Init_sub_menu_quitter);
     activite_encours=R_ACTIVITE_MENU_PRINCIPAL;
     printf("boutons crees\n");

 }

void R_actualiser_menu_principal(void)
{
    al_draw_bitmap(Fond,0,0,0);
    Actualiser_menu_principal();
    al_flip_display();//
}

 void Actualiser_menu_principal(void)
 {
    static float sx_avant, sy_avant;
    ALLEGRO_BITMAP *Buffer_menu_principal=NULL;
    ALLEGRO_BITMAP *menu_titre=NULL;
    Buffer_menu_principal=al_create_bitmap(largeur_ecran,hauteur_ecran);
    menu_titre=al_load_bitmap("menu_titre.png");

    al_set_target_bitmap(Buffer_menu_principal);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_bitmap(menu_titre,
                   largeur_ecran/2.0-al_get_bitmap_width(menu_titre)/2.0,
                   138-al_get_bitmap_height(menu_titre)/2.0,0);

    if(sx_avant!=souris_x()||sy_avant!=souris_y()||souris_bouton_presse(1))
    {
        Actualiser_bouton(menu_bouton_play);
        Actualiser_bouton(menu_bouton_options);
        Actualiser_bouton(menu_bouton_quitter);
    }
    Afficher_bouton(menu_bouton_play);
    Afficher_bouton(menu_bouton_options);
    Afficher_bouton(menu_bouton_quitter);
    al_set_target_backbuffer(display);
    al_draw_bitmap(Buffer_menu_principal,0,0,0);
    al_destroy_bitmap(menu_titre);
    al_destroy_bitmap(Buffer_menu_principal);
 }

 void Detruire_menu_principal(void)
 {
    Detruire_bouton(menu_bouton_play);
    Detruire_bouton(menu_bouton_options);
    Detruire_bouton(menu_bouton_quitter);
 }
