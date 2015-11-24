#pragma once
// przycisk tekstowy
#include "przycisk.h"
#include <allegro5\allegro_font.h> 
#include <allegro5\allegro_ttf.h>
class przycisk_txt : public przycisk {
	int rozmiar_czcionki;
public:
	ALLEGRO_FONT * czcionka;
	std::string nazwa;
	przycisk_txt(int = 0, int = 0, std::string = "pole NN", int =10);
	przycisk_txt(const przycisk_txt&);
	~przycisk_txt();
	void narysuj_sie(ALLEGRO_DISPLAY *okno);
	void narysuj_sie();
	bool czy_to_przycisk(int, int);
	void ustaw_na_srodku(int, int);
	void ustaw_do_lewej(int, int);
	void podswietl(ALLEGRO_COLOR);
	bool operator==(przycisk_txt temp);
	bool operator==(przycisk_txt& temp);
	int pokaz_rozmiar_czcionki()const;
	przycisk_txt& operator=(przycisk_txt&);
};