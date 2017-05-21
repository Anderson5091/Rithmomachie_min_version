
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#include "Rithmomachie_Data.h"
#include "Jeu.h"
#include "Menu.h"
#include "GUI.h"
#include "Moyeu.h"

extern CASE Tablier[TABLIER_LIGNE_MAX][TABLIER_COLONNE_MAX];

ALLEGRO_BITMAP *Fond_jeu;
BOUTON *jeu_bouton_pause, *jeu_bouton_options, *jeu_bouton_menu_principal;

void Actualiser_menu_jeu(void)
{
    static float sx_avant, sy_avant;

    if(sx_avant!=souris_x()||sy_avant!=souris_y()||souris_bouton_presse(1))
    {
        Actualiser_bouton(jeu_bouton_pause);
        Actualiser_bouton(jeu_bouton_options);
        Actualiser_bouton(jeu_bouton_menu_principal);
    }
    Afficher_bouton(jeu_bouton_pause);
    Afficher_bouton(jeu_bouton_options);
    Afficher_bouton(jeu_bouton_menu_principal);

}
void R_actualiser_jeu_encours(void)
{
    al_draw_bitmap(Fond_jeu,0,0,0);
    Actualiser_menu_jeu();
    Actualier_tablier();//
    Actualiser_moyeux();//
    al_flip_display();//
}

void Init_jeu(void)
{

    activite_encours=R_ACTIVITE_JEU_ENCOURS;
    Detruire_menu_principal();
    jeu_bouton_menu_principal=Creer_bouton(188.71,86.772,al_load_bitmap("jeu_bouton_menu.png"),Init_menu_principal);
    jeu_bouton_pause=Creer_bouton(307.71,86.772,al_load_bitmap("jeu_bouton_pause.png"),Init_menu_principal);
    jeu_bouton_options=Creer_bouton(247.71,86.772,al_load_bitmap("jeu_bouton_options.png"),Init_menu_principal);

    Fond_jeu=al_load_bitmap("uiArithom-01.png");//
    //al_draw_bitmap(Fond,0,0,0);
    Init_tablier_cases();
    printf("init tablier\n");
    Init_joueur(Trouver_joueur(0),Tablier[12][6].Pyramide);
    printf("init joueur1\n");
    Init_joueur(Trouver_joueur(1),Tablier[3][0].Pyramide);
    printf("init joueur2\n");
    printf("init moyeu1...\n");
    Init_moyeu(Trouver_joueur(0),0,0);
    printf("init moyeu2...\n");
    Init_moyeu(Trouver_joueur(1),0,0);
    //Init_Plateaux();
    joueur_actuel=Trouver_joueur(0);
    //activite_encours=R_ACTIVITE_JEU_ENCOURS;
    //reafficher=1;
}

void Detruire_jeu(void)
{
    al_destroy_bitmap(Fond_jeu);
    Detruire_bouton(jeu_bouton_pause);
    Detruire_bouton(jeu_bouton_options);
    Detruire_bouton(jeu_bouton_menu_principal);
    Detruire_moyeux_boutons();
}
