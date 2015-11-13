#include "driver.h"
#include <stdio.h>
//#include <allegro5/allegro.h>

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
		al_clear_to_color(al_map_rgb(i, i*2, 3*i));
	al_flip_display();
	//	cout << "costam";
	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}