#include "statystyka.h"
//klasa pomocnicza, która wyœwietla liczby na ekranie
statystyka::statystyka(wspolrzedna wsp, std::string _nazwa, int _rozm)
	:polozenie(wsp),
	nazwa(_nazwa),
	rozmiar(_rozm)
{
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	czcionka_statystyki = al_load_ttf_font("times.ttf", rozmiar, 0);
	rozmiar_x = 2*al_get_text_width(czcionka_statystyki,nazwa.c_str());
	rozmiar_y = rozmiar;
}

statystyka::~statystyka()
{
	al_destroy_font(czcionka_statystyki);
}

void statystyka::wyswietl(int liczba)
{
	std::string temp_nazwa;
	std::ostringstream temp_stream;
	temp_stream <<" "<< liczba;
	temp_nazwa = nazwa;
	temp_nazwa += temp_stream.str();
	al_draw_filled_ellipse(polozenie.x, polozenie.y+rozmiar_y/2, ((double)5 / 4)*rozmiar_x / 2,  ((double)5/4)*rozmiar_y/2, al_map_rgb(0, 0, 0));
	al_draw_text(czcionka_statystyki, al_map_rgb(250, 250, 250), polozenie.x, polozenie.y, ALLEGRO_ALIGN_CENTRE, temp_nazwa.c_str());
}
