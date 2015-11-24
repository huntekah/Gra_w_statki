#pragma once
// silnik gry. to on uruchamia grê i odpowiednie trybiki
#include "menu.h"
extern void zamknij_program();
extern ALLEGRO_DISPLAY* ekran;
extern void fgra_1_vs_1();
extern void fgra_1_vs_ai();
extern void fwczytaj();
class silnik {
	ALLEGRO_BITMAP *tlo;
	przycisk_txt pt_dwoch_graczy;
	przycisk_txt pt_z_komputerem;
	przycisk_txt pt_zapisz;
	przycisk_txt pt_wczytaj;
	przycisk_txt pt_wyjscie;
	ALLEGRO_MOUSE_STATE myszka;
	ALLEGRO_EVENT_QUEUE *kolejka_eventow;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;
	double timer;
public:
	menu menu_gry;
	int szer_okna;
	int wys_okna;
	przycisk *p_dwoch_graczy, *p_z_komputerem, *p_zapisz, *p_wczytaj, *p_wyjscie;
	silnik(int, int);
	~silnik();
};