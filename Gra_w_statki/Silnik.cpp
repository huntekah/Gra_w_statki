#include "silnik.h"


silnik::silnik(int szer, int wys):szer_okna(szer), wys_okna(wys)
{

	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();

	ekran = al_create_display(szer_okna, wys_okna);
	if (!ekran) {
		fprintf(stderr, "failed to create display!\n");
		exit(-1);
	}
	tlo = al_load_bitmap("tlo_menu1.png");
	al_clear_to_color(al_map_rgb(203, 237, 150));
	al_draw_scaled_bitmap(tlo,0,0, al_get_bitmap_width(tlo), al_get_bitmap_height(tlo),0,0,szer_okna,wys_okna,0);
	kolejka_eventow = al_create_event_queue();

	if (!kolejka_eventow) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(ekran);
		exit(-1);
	}
	al_register_event_source(kolejka_eventow, al_get_display_event_source(ekran));
	al_register_event_source(kolejka_eventow, al_get_mouse_event_source());

	pt_dwoch_graczy=przycisk_txt(0, 10, "1 vs 1", 3 * wys_okna / 20);
	pt_dwoch_graczy.ustaw_funkcje(fgra_1_vs_1);
	p_dwoch_graczy = &pt_dwoch_graczy;
	pt_z_komputerem = przycisk_txt(0, 20, "1 vs AI", 3 * wys_okna / 20);
	pt_z_komputerem.ustaw_funkcje(fgra_1_vs_ai);
	p_z_komputerem = &pt_z_komputerem;
	pt_wczytaj = przycisk_txt(0, 10, "wczytaj", 3 * wys_okna / 20);
	pt_wczytaj.ustaw_funkcje(fwczytaj);
	p_wczytaj = &pt_wczytaj;
	pt_wyjscie = przycisk_txt(0, 10, "wyjscie", 3 * wys_okna / 20);
	pt_wyjscie.ustaw_funkcje(zamknij_program);
	p_wyjscie = &pt_wyjscie;


	timer = al_get_time();
	
	menu_gry.gdzie = wspolrzedna(szer_okna/2,wys_okna/5);
	menu_gry += p_dwoch_graczy;
	menu_gry += p_z_komputerem;
	menu_gry += p_wczytaj;
	menu_gry += p_wyjscie;
	menu_gry.justuj();
	menu_gry.narysuj_menu();

	bool petla_menu=1;
	bool rysuj_menu = 0;
	while (petla_menu) {
		al_init_timeout(&timeout, 0.05);
		timer = al_get_time();
		bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
		if (get_event) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				menu_gry.kliknij_przycisk(menu_gry.jaki_przycisk(event.mouse.x, event.mouse.y));
				rysuj_menu = 1;
			}
			else {
				menu_gry.wymaz_podswietlenia();
				menu_gry.podswietl(menu_gry.jaki_przycisk(event.mouse.x, event.mouse.y));
				al_rest(0.05 - (al_get_time() - timer));
			}
		}
		al_flush_event_queue(kolejka_eventow);
		if (rysuj_menu) { // po wykonaniu akcji (np. gry) rysujemy z powrotem menu
			al_draw_scaled_bitmap(tlo, 0, 0, al_get_bitmap_width(tlo), al_get_bitmap_height(tlo), 0, 0, szer_okna, wys_okna, 0);
			menu_gry.narysuj_menu();
			rysuj_menu = 0;
		}
	}
	al_rest(5.0);
}

silnik::~silnik()
{
	al_destroy_event_queue(kolejka_eventow);
	al_destroy_display(ekran);
}

