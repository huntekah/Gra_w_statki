#pragma once
//klasa pomocnicza, która wyœwietla liczby na ekranie
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_font.h> 
#include <allegro5\allegro_ttf.h>
#include "wspolrzedna.h"
#include <sstream>
class statystyka {
protected:
	ALLEGRO_FONT * czcionka_statystyki;
	wspolrzedna polozenie;
	std::string nazwa;
	int rozmiar;
	int rozmiar_x;
	int rozmiar_y;
public:
	statystyka(wspolrzedna, std::string,int);
	~statystyka();
	void wyswietl(int);
};