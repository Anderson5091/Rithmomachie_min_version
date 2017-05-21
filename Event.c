
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/Mars/17.
 *
 *    .
 */

#include "Event.h"
#define  BOUTONS_SOURIS 10

static  int tableau_souris[BOUTONS_SOURIS];
static  int sx, sy;


bool souris_bouton_presse(int b){
    return tableau_souris[b] & 1;
    //printf("bouton %d relache bouton\n", b);//
}

bool souris_bouton_relache(int b) {
    return tableau_souris[b] & 2;
    //printf("bouton %d relache bouton\n", b);//
}

int souris_x(void) {
    return sx;
}

int souris_y(void) {
    return sy;
}

void souris_set_event(ALLEGRO_EVENT *event) {
    switch (event->type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            tableau_souris[event->mouse.button] |= (1 << 0);
            tableau_souris[event->mouse.button] |= (1 << 1);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            tableau_souris[event->mouse.button] &= ~(1 << 0);
            tableau_souris[event->mouse.button] |= (1 << 2);
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            sx = event->mouse.x;
            sy = event->mouse.y;
            break;
    }
}

void souris_tick(void) {
    // effacer les bits presse/relache
    int i;
    for(i = 0; i < BOUTONS_SOURIS; i++) {
        tableau_souris[i] &= ~(1 << 1);
        tableau_souris[i] &= ~(1 << 2);
    }

}
/******************************************************************************/

static ALLEGRO_EVENT event;
ALLEGRO_EVENT_QUEUE *event_queue;

void R_wait_for_event(void)
{
    al_wait_for_event(event_queue, &event);
}

bool R_pool_event()
{
    extern chrono;
    extern paused;
    extern fin;

    switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES:
                souris_set_event(&event);
                return TRUE;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                printf("boton prese");
                souris_set_event(&event);
                return TRUE;

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                souris_set_event(&event);
                return TRUE;

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                fin = 1;
                return TRUE;

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                return TRUE;

                break;
            case ALLEGRO_EVENT_TIMER:
                if (!paused)
                    chrono++;
                return FALSE;
                break;
        }
}


