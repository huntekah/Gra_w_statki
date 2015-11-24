
#pragma once
// klasa b�d�ca sk�adnikiem planszy. trzyma w sobie obrazki wy�wietlane na planszy i zarz�dza nimi
#include "wspolrzedna.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
extern ALLEGRO_DISPLAY* ekran;
class kratka {
	//statyczne obrazki oszcz�dz� nam pami�ci (duuuuu�o pami�ci)
	static ALLEGRO_BITMAP *nieznane;
	static ALLEGRO_BITMAP *statek;
	static ALLEGRO_BITMAP *zakazane;
	static ALLEGRO_BITMAP *zbite;
	static ALLEGRO_BITMAP *zatopione;
	static ALLEGRO_BITMAP *puste;
	static ALLEGRO_BITMAP *nieznane_podswietl;
	static ALLEGRO_BITMAP *statek_podswietl;
	static ALLEGRO_BITMAP *zakazane_podswietl;
	static ALLEGRO_BITMAP *zbite_podswietl;
	static ALLEGRO_BITMAP *zatopione_podswietl;
	static ALLEGRO_BITMAP *puste_podswietl;
	static int zainicjalizowane;
	int rozmiar_x_obrazka;
	int rozmiar_y_obrazka;
	int szer_ekranu;
	int wys_ekranu;
	int stan; // 0-puste, 1-statek, 2-zakazane 3-zbite, 4-zabite(drugi stan zakazania)
public:
	static void inicjalizuj();
	void zaladuj_obrazek();
	ALLEGRO_BITMAP *obrazek;
	bool odkryte;
	int rozmiar_x;
	int rozmiar_y;
	wspolrzedna polozenie;
	wspolrzedna indeks;
//************************************
	kratka(wspolrzedna=wspolrzedna(0,0),wspolrzedna=wspolrzedna(10,10),int=0,bool=0 );
	~kratka();
	void narysuj_sie();		//nie od�wie�a ekranu;
	void podswietl_sie();
	bool czy_kratka(int, int);
	void zmiana_stanu(int );
	int zbij(); // 0 zako�czone b��dem, 1 poprawnie zbite, -1 pud�o;
	void odkryj_i_zabij();
	void odkryj();
	void ustal_polozenie(wspolrzedna);
	int jaki_stan() { return stan; };
	bool operator==(kratka);
	kratka& operator=(kratka&);
	kratka(kratka&);
	// doda� operator przypisania;
	void zatop();		// drugi stan zatopienia - gdy ca�y statek jest zatopiony
};