#pragma once
// klasa czysto wirtualna, dziêki której mo¿emy umieœciæ w menu zarówno przyciski textowe jak i graficzne - i zarz¹dzaæ nimi jednoczeœnie
#include "wspolrzedna.h"
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
class przycisk {
	void(*wsk_fun)();
public:
	wspolrzedna polozenie;
	int rozmiar_x;
	int rozmiar_y;
	int szer_ekranu;
	int wys_ekranu;
	przycisk(int = 0,int = 0);
	virtual ~przycisk() {};
	void przycisniecie();
	virtual void podswietl(ALLEGRO_COLOR) {};
	void ustaw_funkcje(void(*wskf)());
	virtual void narysuj_sie(ALLEGRO_DISPLAY *okno) {};
	virtual void narysuj_sie() =0;
	virtual bool operator==(przycisk& temp) { return false; };
	virtual bool czy_to_przycisk(int, int) { return false; };
	virtual void ustaw_na_srodku(int, int) {};
	virtual void ustaw_do_lewej(int, int) {};
};
