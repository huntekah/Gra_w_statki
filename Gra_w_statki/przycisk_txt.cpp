#include "przycisk_txt.h"

przycisk_txt::przycisk_txt(int wsp_x, int wsp_y, std::string knazwa, int rozm_cz) :
	przycisk(wsp_x, wsp_y), 
	nazwa(knazwa),
	rozmiar_czcionki(rozm_cz)
{
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	rozmiar_x = rozmiar_czcionki*nazwa.size();
	rozmiar_y = rozmiar_czcionki;
	czcionka = al_load_ttf_font("times.ttf", rozmiar_czcionki,0);
}

przycisk_txt::przycisk_txt(const przycisk_txt &wzor)
{
	nazwa = wzor.nazwa;
	polozenie = wzor.polozenie;
	rozmiar_x = wzor.rozmiar_x;
	rozmiar_y = wzor.rozmiar_y;
	rozmiar_czcionki = wzor.pokaz_rozmiar_czcionki();
	czcionka= al_load_ttf_font("times.ttf", rozmiar_czcionki, 0);

}

przycisk_txt::~przycisk_txt()
{
	al_destroy_font(czcionka);
}

void przycisk_txt::narysuj_sie(ALLEGRO_DISPLAY * okno)
{
	al_set_target_bitmap(al_get_backbuffer(okno));
	al_draw_text(czcionka, al_map_rgb(0, 0, 0), polozenie.x, polozenie.y, ALLEGRO_ALIGN_CENTRE, nazwa.data());
}

void przycisk_txt::narysuj_sie()
{
	al_draw_text(czcionka, al_map_rgb(0, 0, 0), polozenie.x, polozenie.y, ALLEGRO_ALIGN_CENTRE, nazwa.data());
}

bool przycisk_txt::czy_to_przycisk(int mysz_x, int mysz_y)
{
	if ((mysz_y >= polozenie.y && mysz_y <= polozenie.y + rozmiar_y)
		&& (mysz_x >= (polozenie.x - (rozmiar_x / 2)) && mysz_x <= (polozenie.x + (rozmiar_x / 2)))) return true;
	return false;
}

void przycisk_txt::ustaw_na_srodku(int wsp_x, int wsp_y)
{
	polozenie.x = wsp_x;
	polozenie.y = wsp_y;
}

void przycisk_txt::ustaw_do_lewej(int wsp_x, int wsp_y)
{
	polozenie.x = (rozmiar_x / 2) + wsp_x;
	polozenie.y = wsp_y;
}

void przycisk_txt::podswietl(ALLEGRO_COLOR kolor)
{
	al_draw_rectangle(polozenie.x- (rozmiar_x/2), polozenie.y, rozmiar_x + (polozenie.x/2), rozmiar_y + polozenie.y, kolor, 2);
}

bool przycisk_txt::operator==(przycisk_txt temp)
{
	if ((temp.polozenie == polozenie) && (nazwa == temp.nazwa))return true;
	return false;
}

bool przycisk_txt::operator==(przycisk_txt & temp)
{
	if ((temp.polozenie == polozenie) && (nazwa == temp.nazwa))return true;
	return false;
}

int przycisk_txt::pokaz_rozmiar_czcionki()const
{
	return rozmiar_czcionki;
}

przycisk_txt & przycisk_txt::operator=(przycisk_txt &wzor)
{
	al_destroy_font(czcionka);
	nazwa = wzor.nazwa;
	polozenie = wzor.polozenie;
	rozmiar_x = wzor.rozmiar_x;
	rozmiar_y = wzor.rozmiar_y;
	rozmiar_czcionki = wzor.pokaz_rozmiar_czcionki();
	czcionka = al_load_ttf_font("times.ttf", rozmiar_czcionki, 0);
	return *this;
}
