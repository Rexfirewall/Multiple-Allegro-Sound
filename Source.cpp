#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include<iostream>
using namespace std;
int main(void)
{


	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool Burp = false;
	bool redraw = false;

	ALLEGRO_SAMPLE *boom = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;


	al_init();

	display = al_create_display(200, 200);


	al_install_audio();
	al_init_acodec_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	al_install_keyboard();


	al_reserve_samples(10);


	boom = al_load_sample("just-like-magic.ogg");
	song = al_load_sample("solar_eclipse.ogg");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);

	songInstance = al_create_sample_instance(boom);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());


	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (Burp == true)
				al_play_sample_instance(songInstance);
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return 0;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				Burp = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				Burp = false;
				break;

			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;



			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}


	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);                        //destroy our display object

	return 0;
}