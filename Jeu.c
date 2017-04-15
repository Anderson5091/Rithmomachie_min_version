
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#include "Jeu.h"
#include "Echiquier.h"

AFFICHAGE *Ecran_affichage;
AFFICHAGE *Echiquier_affichage;
AFFICHAGE *JeuMenu_affichage;
AFFICHAGE *Joueur1_affichage;
AFFICHAGE *Joueur2_affichage;
AFFICHAGE *Plateu1_affichaje;
AFFICHAGE *Plateu2_affichaje;

static JOUEUR Joueur[JOUEUR_MAX];


void Init_joueur(AFFICHAGE *affichage, int joueur, char *name)
{
   int i, j;
   float dx, dy;

    Joueur[joueur].Joueur_aff = affichage;
    Joueur[joueur].Name=name;
}

void Afficher_joueur(int joueur)
{

}

static void Afficher_jeu(void)
{
    //afficher_Echiquier();
    al_draw_bitmap(Ecran_affichage->Bmp, Ecran_affichage->X, Ecran_affichage->Y, 0);
}

void Init_affichage_jeu() {

    extern float largeur_ecran;
    extern float hauteur_ecran;

    Ecran_affichage = Init_affichage("ecran", NULL, 0, 0, largeur_ecran, hauteur_ecran);
    Joueur1_affichage = Init_affichage("joueur1", Ecran_affichage, (int)(3.0*largeur_ecran/4.0), 0, (int)(1.0*largeur_ecran/4.0), hauteur_ecran/2.0);
    Echiquier_affichage = Init_affichage("echiquier", Ecran_affichage, 0, 0, (int)(3.0*largeur_ecran/4.0), hauteur_ecran);
    Joueur2_affichage = Init_affichage("joueur2", Ecran_affichage, (int)(3.0*largeur_ecran/4.0), (int)(1.0*hauteur_ecran/2.0), (int)(1.0*largeur_ecran/4.0), hauteur_ecran/2.0);
}

void detruire_affichage_jeu()
{
    Detruire_affichage(Joueur1_affichage);
    Detruire_affichage(Joueur2_affichage);
    Detruire_affichage(Echiquier_affichage);
    Detruire_affichage(Ecran_affichage);
    al_destroy_bitmap(Fond);
}
