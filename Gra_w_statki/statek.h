#pragma once
#include "kratka.h"
class statek {
	int hp;
	int rozmiar_x; //tablicy
	int rozmiar_y;
public:
	statek( bool**, int, int);
	~statek();
	kratka **wyglad;
	void obroc();
	int zbij(kratka*);
};