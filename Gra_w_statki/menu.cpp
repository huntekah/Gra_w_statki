#include "menu.h"

menu::menu(int wsp_x, int wsp_y) : gdzie(wsp_x,wsp_y){
	kolor_tla = al_map_rgb(0, 0, 0);
	kolor_podswietlenia = al_map_rgb(6, 16, 90);
}

menu::~menu()
{
	przyciski.clear();
}

void menu::dodaj_przycisk(przycisk* temp)
{
	przyciski.push_back(temp);
}

void menu::usun_przycisk(przycisk* temp)
{
	int i = 0;
	for (; i < ile(); i++) {
		if ((typeid(przyciski[i]).hash_code()) == (typeid(temp).hash_code()))	// sprawdzamy czy przyciski s¹ tych samcyh typów.
			if (przyciski[i]->polozenie == temp->polozenie)break;				// tylko wtedy mo¿na je ze sob¹ porównaæ								
	}
	przyciski.erase(przyciski.begin()+i);
}

void menu::justuj()
{
	wspolrzedna p(gdzie);
	for (int i = 0; i < ile(); i++) {
		przyciski[i]->ustaw_na_srodku(p.x, p.y);
		p.y += przyciski[i]->rozmiar_y;
	}
}

int menu::jaki_przycisk(int wsp_x, int wsp_y)
{
	for (int i = 0; i < ile(); i++)if (przyciski[i]->czy_to_przycisk(wsp_x,wsp_y))return i;
	return -1;
}

void menu::kliknij_przycisk(int ktory)
{
	if(ktory+1) przyciski[ktory]->przycisniecie();
}

void menu::operator+=(przycisk* temp)
{
	dodaj_przycisk(temp);
}

void menu::operator-=(przycisk* temp)
{
	usun_przycisk(temp);
}

void menu::narysuj_menu()
{
	for (int i = 0; i < ile(); i++) {
		przyciski[i]->podswietl(kolor_tla);
		(przyciski[i])->narysuj_sie();
	}
	al_flip_display();
}

void menu::podswietl(int ktory)
{
	if (ktory + 1) przyciski[ktory]->podswietl(kolor_podswietlenia);
	al_flip_display();
}

void menu::wymaz_podswietlenia()
{

	for (int i = 0; i < ile(); i++)
		przyciski[i]->podswietl(kolor_tla);
	al_flip_display();
}

int menu::ile()
{
	return przyciski.size();
}
