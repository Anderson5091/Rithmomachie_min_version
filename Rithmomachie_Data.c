


#include"Rithmomachie_Data.h"
#include "Jeu.h"
#include"Menu.h"

float largeur_ecran;
float hauteur_ecran;
COORDPOINT centre_ecran;
//ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_DISPLAY_MODE mode;
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *icone;
ALLEGRO_BITMAP* Fond = NULL;
int activite_encours, framerate = 100, chrono = 0, nbmode, reafficher=1, fin =0;
bool paused = false;

double duree=10.0f;
double progression=0.0f;

void Set_progress(double d, double p)
{
    duree=d;
    progression=p;
}
void Reset_progress(void)
{
    duree=10.0f;
    progression=0.0f;
}

void erreur( const char*txt)
{
    ALLEGRO_DISPLAY *d;
    d = al_is_system_installed( )? al_get_current_display( ) : NULL;
    al_show_native_message_box( d, "ERREUR", txt, NULL, NULL, 0);
    exit( EXIT_FAILURE);
}

void Config_activite(int activite)
{
    switch(activite)
    {
        case  R_ACTIVITE_MENU_PRINCIPAL:
            Actualiser_activite=R_actualiser_menu_principal;
            reafficher=1;
            break;
        case  R_ACTIVITE_MENU_JOUER:
            break;
        case  R_ACTIVITE_MENU_OPTIONS:
            break;
        case  R_ACTIVITE_QUITTER:
            break;
        case  R_ACTIVITE_JEU_NOUVEAU_JEU:
            break;
        case  R_ACTIVITE_JEU_ENCOURS:
            Actualiser_activite=R_actualiser_jeu_encours;
            reafficher=1;
            break;
        case  R_ACTIVITE_JEU_REPRENDRE:
            break;
        case  R_ACTIVITE_JEU_EN_PAUSE:
            break;
        case  R_ACTIVITE_JEU_OPTIONS:
            break;
        case  R_ACTIVITE_JEU_PYRAMIDE_REF:
            break;
        case  R_ACTIVITE_JEU_PARTIE_TERMINER:
            break;
    }
}


