#pragma once
#include "wspolrzedna.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class Artificial_inteligence {
	//klasa odpowiada za sztuczn¹ inteligencjê gry
	static int **plansza_ai;
	static int wymiar_x;
	static int wymiar_y;
	static int licznik;// licznik strza³ów
	static int ile;
	static int ile_pustych;
	static int czy_zdefiniowano;
public:
	//przy pierwszym u¿yciu inicjalizujemy zmienne statyczne
	static void inicjalizuj(int);
	wspolrzedna strzel_ai();
	void wpisz_do_planszy_ai(wspolrzedna,int);// wspolrzedne, stan
};