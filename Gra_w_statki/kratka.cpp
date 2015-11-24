#include "kratka.h"

 ALLEGRO_BITMAP* kratka::nieznane=nullptr;
 ALLEGRO_BITMAP* kratka::statek = nullptr;
 ALLEGRO_BITMAP* kratka::zakazane = nullptr;
 ALLEGRO_BITMAP* kratka::zbite = nullptr;
 ALLEGRO_BITMAP* kratka::zatopione = nullptr;
 ALLEGRO_BITMAP* kratka::puste = nullptr;
 ALLEGRO_BITMAP* kratka::nieznane_podswietl = nullptr;
 ALLEGRO_BITMAP* kratka::statek_podswietl = nullptr;
 ALLEGRO_BITMAP* kratka::zakazane_podswietl = nullptr;
 ALLEGRO_BITMAP* kratka::zbite_podswietl = nullptr;
 ALLEGRO_BITMAP* kratka::zatopione_podswietl = nullptr;
 ALLEGRO_BITMAP* kratka::puste_podswietl = nullptr;
 int kratka::zainicjalizowane = 0;
kratka::kratka(wspolrzedna kpolozenie, wspolrzedna kindeks, int kstan , bool kodkryte):
	polozenie(kpolozenie),indeks(kindeks), odkryte(kodkryte)
{
	al_init_image_addon();
	inicjalizuj();
	obrazek = puste;
	szer_ekranu = al_get_display_width(al_get_current_display());
	wys_ekranu = al_get_display_height(al_get_current_display());
	rozmiar_x = (szer_ekranu / 29);
	rozmiar_y = (szer_ekranu / 29);
	rozmiar_x_obrazka = al_get_bitmap_width(obrazek);
	rozmiar_y_obrazka = al_get_bitmap_height(obrazek);


	zmiana_stanu(kstan);
}

kratka::~kratka()
{}
//funkcja statyczna!
void kratka::inicjalizuj()
{
	if (zainicjalizowane == 0) {
		al_init_image_addon();
		nieznane = al_load_bitmap("nieznane.png");
		statek = al_load_bitmap("statek.png");
		zakazane = al_load_bitmap("zakazane.png");
		zbite = al_load_bitmap("zbite.png");
		zatopione = al_load_bitmap("zatopione.png");
		puste = al_load_bitmap("puste.png");
		nieznane_podswietl = al_load_bitmap("nieznane_podswietl.png");
		statek_podswietl = al_load_bitmap("statek_podswietl.png");
		zakazane_podswietl = al_load_bitmap("zakazane_podswietl.png");
		zbite_podswietl = al_load_bitmap("zbite_podswietl.png");
		zatopione_podswietl = al_load_bitmap("zatopione_podswietl.png");
		puste_podswietl = al_load_bitmap("puste_podswietl.png");
	}
	zainicjalizowane = 1;
}

void kratka::narysuj_sie()
{
	al_set_target_backbuffer(ekran);

	rozmiar_x = (szer_ekranu / 29);
	rozmiar_y = (szer_ekranu / 29);
	if (obrazek != NULL) {
		al_draw_scaled_bitmap(obrazek, 0, 0, rozmiar_x_obrazka, rozmiar_y_obrazka, polozenie.x, polozenie.y, rozmiar_x, rozmiar_y, 0);
	}

}

void kratka::podswietl_sie()
{
	if (!odkryte) {

		obrazek = nieznane_podswietl;
	}
	else {
		switch (stan)
		{
		case 1:

			obrazek = statek_podswietl;
			break;
		case 2:

			obrazek = zakazane_podswietl;
			break;
		case 3:

			obrazek = zbite_podswietl;
			break;
		case 4:

			obrazek = zatopione_podswietl;
			break;
		default:

			obrazek = puste_podswietl;
			break;
		}
	}
	narysuj_sie();
}

bool kratka::czy_kratka(int mysz_x, int mysz_y)
{
	if ((mysz_x >= polozenie.x && mysz_x <= polozenie.x + rozmiar_x)
		&& (mysz_y >= polozenie.y && mysz_y <= polozenie.y + rozmiar_y)) return true;
	return false;
}

void kratka::zmiana_stanu(int nowy_stan)
{
	if (stan != nowy_stan || odkryte) {
		stan = nowy_stan;
		zaladuj_obrazek();
	}
}

int kratka::zbij()
{
	if ((stan/2)==1) return 0; // stan== 2 lub 3; pole zakazane, zbite lub ju¿ odkryte;
	else if ( (stan / 2) == 0) {
		odkryj_i_zabij();
		if (stan == 3)return 1;
		return -1;
	}
	return 0;
}

void kratka::odkryj_i_zabij()
{
	odkryte = 1;
	if (stan == 1)stan = 3;
	if (stan == 0)stan = 2;
	zaladuj_obrazek();
}

void kratka::odkryj()
{
	odkryte = 1;
	zaladuj_obrazek();
}

void kratka::ustal_polozenie(wspolrzedna _polozenie)
{
	polozenie = _polozenie;
}

bool kratka::operator==(kratka wzor)
{
	if (polozenie == wzor.polozenie && indeks == wzor.indeks)return true;
	return false;
}

kratka & kratka::operator=(kratka &wzor)
{
	// sprawdzamy czy nie kopiujemy do siebie samego;
	if (&wzor == this) return *this;

	obrazek = wzor.obrazek;
	odkryte = wzor.odkryte;
	rozmiar_x = wzor.rozmiar_x;
	rozmiar_y = wzor.rozmiar_y;
	polozenie = wzor.polozenie;
	indeks = wzor.indeks;
	return *this;
}

kratka::kratka(kratka &wzor)
{

	obrazek = wzor.obrazek;
	odkryte = wzor.odkryte;
	rozmiar_x = wzor.rozmiar_x;
	rozmiar_y = wzor.rozmiar_y;
	polozenie = wzor.polozenie;
	indeks = wzor.indeks;

}

void kratka::zatop()
{
	zmiana_stanu(4);

}



void kratka::zaladuj_obrazek()
{
	if (!odkryte) {

		obrazek =nieznane ;
	}
	else {
		switch (stan)
		{
		case 1:

			obrazek = statek;
			break;
		case 2:

			obrazek = zakazane;
			break;
		case 3:

			obrazek =zbite ;
			break;
		case 4:

			obrazek =zatopione ;
			break;
		default:

			obrazek = puste;
			break;
		}
	}
}

