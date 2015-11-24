#pragma once
//klasa odpowiadaj¹ca za organizacjê przycisków
#include "przycisk.h"
#include "przycisk_txt.h"
#include "przycisk_img.h"
#include <vector>
#include <typeinfo>
class menu {
	int ile_przyciskow;
public:
	wspolrzedna gdzie;
	std::vector < przycisk* > przyciski;
	ALLEGRO_COLOR kolor_tla, kolor_podswietlenia;
	menu(int = 0, int = 0);
	~menu();
	void dodaj_przycisk(przycisk*);
	void usun_przycisk(przycisk*);
	void justuj();
	int jaki_przycisk(int,int);
	void kliknij_przycisk(int);
	void operator+=(przycisk*);
	void operator-=(przycisk*);
	void narysuj_menu();
	void podswietl(int);
	void wymaz_podswietlenia();
private:
	int ile();

};