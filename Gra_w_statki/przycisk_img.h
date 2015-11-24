#pragma once
//przycisk graficzny
#include "przycisk.h"
class przycisk_img : public przycisk {
	std::string adres_obrazka;
	ALLEGRO_BITMAP *obrazek;
public:
	przycisk_img(int = 0, int = 0, std::string = "rysunek1.png");
	~przycisk_img();
	void narysuj_sie(ALLEGRO_DISPLAY *okno);
	void narysuj_sie();
	bool czy_to_przycisk(int, int);
	void ustaw_na_srodku(int, int);
	void ustaw_do_lewej(int, int);
	void podswietl(ALLEGRO_COLOR);
	bool operator==(przycisk_img temp);
	bool operator==(przycisk_img& temp);
};