
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

//#include "Rithmomachie_Data.h"
#include "Echiquier.h"
#include "Event.h"

void erreur( const char*txt)
{
    ALLEGRO_DISPLAY *d;
    d = al_is_system_installed( )? al_get_current_display( ) : NULL;
    al_show_native_message_box( d, "ERREUR", txt, NULL, NULL, 0);
    exit( EXIT_FAILURE);
}

ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_DISPLAY_MODE mode;
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *icone;
int framerate = 100, chrono = 0, nbmode;
int reafficher=1;

int main(int argc, char **argv)
{
    if(!Init_Rithmomachie())
        erreur( "Init_Rithmomachie()");

    Lancer_Rithmomachie();

    return Arreter_Rithmomachie();
}

int Afficher_Rithmomachie(void)
{
    al_draw_bitmap(Fond,0,0,0);
    Actualier_echiquier();//
    Actualiser_plateaux();//
    //Selectionner_Piece_plateau();//
    al_flip_display();//
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
    int fin = 0;
    extern int reafficher ;
    bool paused = false;

    int test = 0;

    if(test)
    {
        //executer test
        fin=1;
    }

    R_chargement();
    //printf("initialisation plateaux encours...\n");
    Init_echiquier_cases();
    Init_Plateaux();
    //printf("initialisation plateaux reussi\n");

    while (!fin) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES:
                souris_set_event(&event);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                printf("boton prese");
                souris_set_event(&event);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                souris_set_event(&event);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                fin = 1;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (!paused)
                    chrono++;
                break;
        }

        if (!al_is_event_queue_empty(event_queue)) continue;

        while (chrono > 0)
        {
            --chrono;
        }

        //reafficher=Actualier_echiquier();//

        if (reafficher)
        {
            reafficher=Afficher_Rithmomachie();
            //Actualier_echiquier();//
        }

            souris_tick();
    }
}

int Init_Rithmomachie(void)
{

    if ( ! al_init( ))
        erreur( "al_init() ");
    if ( ! al_init_image_addon( ))
    erreur( "al_init_image_addon()");
    if ( ! al_init_primitives_addon( ))
    erreur( "al_init_primitives_addon()");
    if ( ! al_install_keyboard( ))
    erreur( "al_install_keyboard()");
    if ( ! al_install_mouse( ))
    erreur( "al_install_mouse()");
    if ( ! al_install_audio( ))
    erreur( "al_install_audio()");
    if ( ! al_init_acodec_addon( ))
    erreur( "al_init_acodec_addon");
    if(! al_reserve_samples(8))
    erreur( "al_reserve_samples");
    al_init_font_addon( );
    al_init_ttf_addon( );


    al_set_app_name("RITMOMACHIE");
    al_set_org_name("@FDS");

    nbmode = al_get_num_display_modes( );
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
