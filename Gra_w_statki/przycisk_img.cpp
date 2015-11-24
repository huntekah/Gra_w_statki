#include "przycisk_img.h"


przycisk_img::przycisk_img(int wsp_x, int wsp_y, std::string kadres_obrazka):przycisk(wsp_x,wsp_y),adres_obrazka(kadres_obrazka){
	al_init_image_addon();
	obrazek = al_load_bitmap(adres_obrazka.data());

	if (!obrazek) {
		al_show_native_message_box(NULL, "Blad", "Cos nie tak",
			"Nie moge wczytac bitmapy kwadrat!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}
	szer_ekranu = al_get_display_width(al_get_current_display());
	wys_ekranu = al_get_display_height(al_get_current_display());
	rozmiar_y=al_get_bitmap_height(obrazek);
	rozmiar_x=al_get_bitmap_width(obrazek);
	al_shutdown_image_addon();
}

przycisk_img::~przycisk_img()
{
	al_destroy_bitmap(obrazek);
}

void przycisk_img::narysuj_sie(ALLEGRO_DISPLAY *okno)
{
	al_set_target_bitmap(al_get_backbuffer(okno));
	al_draw_scaled_bitmap(obrazek, 0, 0, rozmiar_x, rozmiar_y, polozenie.x, polozenie.y,(szer_ekranu* rozmiar_x) / 1280, (wys_ekranu*rozmiar_y)/720, 0);

}

void przycisk_img::narysuj_sie()
{
	al_draw_scaled_bitmap(obrazek, 0, 0, rozmiar_x, rozmiar_y, polozenie.x, polozenie.y, (szer_ekranu* rozmiar_x) / 1280, (wys_ekranu*rozmiar_y) / 720, 0);
}

bool przycisk_img::czy_to_przycisk(int mysz_x, int mysz_y)
{
	if ((mysz_x >= polozenie.x && mysz_x <= polozenie.x + rozmiar_x)
		&& (mysz_y >= polozenie.y && mysz_y <= polozenie.y + rozmiar_y)) return true;
	return false;
}

void przycisk_img::ustaw_na_srodku(int wsp_x, int wsp_y)
{
	polozenie.x = wsp_x - (rozmiar_x / 2);
	polozenie.y = wsp_y;
}

void przycisk_img::ustaw_do_lewej(int wsp_x, int wsp_y)
{
	polozenie.x = wsp_x;
	polozenie.y = wsp_y;
}

void przycisk_img::podswietl(ALLEGRO_COLOR kolor)
{
	al_init_primitives_addon();
	al_draw_rectangle(polozenie.x, polozenie.y, (szer_ekranu* rozmiar_x)/1280 + polozenie.x,(wys_ekranu *rozmiar_y)/720 + polozenie.y, kolor, 2);

}

bool przycisk_img::operator==(przycisk_img temp) //przesy³amy przez adres przycisku
{
	if ((temp.polozenie == polozenie) && (adres_obrazka == temp.adres_obrazka))return true;
	return false;
}

bool przycisk_img::operator==(przycisk_img& temp)
{
	if ((temp.polozenie == polozenie) && (adres_obrazka == temp.adres_obrazka))return true;
	return false;
}
