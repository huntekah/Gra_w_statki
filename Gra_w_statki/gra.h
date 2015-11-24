#pragma once
//klasa w której dzieje siê akcja gry
#include "plansza.h"
#include "menu.h"
#include "odszyfrowywanie.h"
#include "Artificial_Inteligence.h"
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "statystyka.h"
extern 	ALLEGRO_DISPLAY *ekran;
class gra: private odszyfrowywanie,private Artificial_inteligence{
	ALLEGRO_FONT * czcionka;
	plansza AGraczA;	//plansza A widok gracza A
	plansza AGraczB;	//plansza A widok gracza B
	plansza BGraczA;	//plansza B widok gracza A
	plansza BGraczB;	//plansza B widok gracza B
	int tura;
	bool AI;
	ALLEGRO_MOUSE_STATE myszka;
	ALLEGRO_EVENT_QUEUE *kolejka_eventow;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;
	ALLEGRO_BITMAP *tlo_gry;
	ALLEGRO_BITMAP *tlo_zmiana_tury;
	//ALLEGRO_BITMAP *zapisz_img;
	int szer_okna;
	int wys_okna;
	int ROZMIAR_CZCIONKI = 70;
	przycisk_img p_zapisu;
	void zmiana_tury(std::string="test");
	void edytuj(bool);
	void ruch_gracz_A();
	void ruch_gracz_B();
	void ruch_AI();
	void wpisz_plansze_do_ai();
	void generuj_ai();
public:
	int odczyt;
	int rozmiar_planszy;
	gra(int=10, bool=0);
	~gra();
	void rozpocznij_gre_1vs1();
	void rozpocznij_gre_1vsAI();
	bool zapisz_gre();
	bool wczytaj_gre(std::ifstream* ptr);
};