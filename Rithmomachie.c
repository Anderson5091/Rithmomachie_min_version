
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#include "Rithmomachie_Data.h"
#include "Chargement.h"
#include "Tablier.h"
#include "Event.h"


int main(int argc, char **argv)
{
    if(!Init_Rithmomachie())
        erreur( "Init_Rithmomachie()");

    Lancer_Rithmomachie();

    return Arreter_Rithmomachie();
}

int Afficher_Rithmomachie(void)
{
    Actualiser_activite();
    return 0;
}

int Arreter_Rithmomachie(void)
{

    al_destroy_timer( timer);
    printf("timer detruit\n");
    al_destroy_event_queue(event_queue);
    printf("queu detruit\n");
    al_destroy_display( display);
    printf("fenetre detruit\n");
    //al_destroy_bitmap(icone);//
    al_destroy_bitmap(Fond);//
    printf("fond detruit\n");
    al_stop_samples();
    int sp;
    for(sp=0; sp<8; sp++)
    {
        //al_destroy_sample();
    }
    Detruire_pieces();
    printf("Rithmomachie Arreter\n");
    return 0;
}

void Lancer_Rithmomachie(void)
{

    extern int reafficher,fin, chrono;
    bool paused;

    int test = 0;

    if(test)
    {
        //executer test

    }

    R_chargement();
    Init_menu_principal();


    while (!fin) {

        R_wait_for_event();

        if(R_pool_event())
        {
          Config_activite(activite_encours);
        }

        if (!al_is_event_queue_empty(event_queue)) continue;

        while (chrono > 0)
        {
            --chrono;
        }


        if (reafficher)
        {
            reafficher=Afficher_Rithmomachie();
        }

            souris_tick();
    }
}

int Init_Rithmomachie(void)
{

    if ( ! al_init())
        erreur( "al_init() ");
    if ( ! al_init_image_addon())
    erreur( "al_init_image_addon()");
    if ( ! al_init_primitives_addon())
    erreur( "al_init_primitives_addon()");
    if ( ! al_install_keyboard())
    erreur( "al_install_keyboard()");
    if ( ! al_install_mouse())
    erreur( "al_install_mouse()");
    if ( ! al_install_audio())
    erreur( "al_install_audio()");
    if ( ! al_init_acodec_addon())
    erreur( "al_init_acodec_addon");
    if(! al_reserve_samples(8))
    erreur( "al_reserve_samples");
    al_init_font_addon();
    al_init_ttf_addon();


    al_set_app_name("RITMOMACHIE");
    al_set_org_name("@FDS");

    nbmode = al_get_num_display_modes();
    al_set_new_display_flags( ALLEGRO_FULLSCREEN_WINDOW);
    al_get_display_mode( nbmode-1, &mode);
    largeur_ecran=mode.width;
    printf("largeur: %f\n", largeur_ecran);
    hauteur_ecran=mode.height;
    printf("hauteur: %f\n", hauteur_ecran);
    centre_ecran.X=largeur_ecran/2;
    centre_ecran.Y=hauteur_ecran/2;
    display = al_create_display(largeur_ecran,hauteur_ecran);
    if ( ! display) erreur( "al_create_display()");
    al_set_window_title(  display, "RITMOMACHIE");
    al_clear_to_color(al_map_rgb(43, 96, 127));//
    al_flip_display();//
    //icone = al_load_bitmap("resources/icon/ico.png");
    //Fond = al_load_bitmap("uiArithom-02.png");
    //if ( ! icone) erreur( "al_load_bitmap(icone)");
    //al_set_display_icon(display, icone);

    event_queue = al_create_event_queue();

    al_register_event_source( event_queue,
                              al_get_mouse_event_source( ));
    al_register_event_source( event_queue,
                              al_get_keyboard_event_source( ));

    timer = al_create_timer(1.0 /framerate);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    return 1;

}
