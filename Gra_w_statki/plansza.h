#pragma once
//klasa ta przechowuje najwa¿niejszy element ca³ej gry - planszê. to tutaj statki wyp³ywaj¹ na bitwê
#include "wspolrzedna.h"
#include "kratka.h"
#include "zaloga_statku.h"
class plansza {
	int szerokosc_ekranu;
	int wysokosc_ekranu;
	int szerokosc_planszy;				// w pixelach
	int wysokosc_planszy;				// w pixelach

	int zbij(int, int);					// 0 (kratka zakazane/ poza plansz¹), -1 pud³o, 1 trafiony
	//*** funkcje zwi¹zane z za³ogami statków;
	void odkryj_pola_wokol_trupa(int);	// argumentem jest indeks za³ogi któr¹ chcemy obs³u¿yæ	
	void zakaz_pola_wokol_statku(int);
	bool czy_jest_w_planszy(wspolrzedna); // czy indeks nalezy do planszy;
	int zwroc_indeks_statku(wspolrzedna);	// argumentem jest indeks kratki.
	void dodaj_zaloge();
	bool czy_sasiaduje(int, int);
	bool czy_sasiaduje_skos(int, int);
public:
	void zakaz_pola_wokol_statku_ukryty(int);// zakazuje pola, lecz nie ujawnia(odkrywa) ich.
	wspolrzedna polozenie;
	std::vector <zaloga_statku> zaloga;
	int ilosc_pol;
	kratka **wyglad;
	plansza(int,wspolrzedna, bool=0);	// domyœlnie plansza jest odkryta
	~plansza(); 
	// GRAFICZNE / sterowanie polami
	void narysuj();
	void narysuj_i_wczytaj();
	void narysuj(int, int);				//rysuje konkretne pole, lecz nie flipuje
	void narysuj_flip(int, int);		// tak jak poprzednio, flipuje(odœwieza)
	void podswietl(int, int); 
	void ktore_to_pole(int*, int*);		//przyjmuje parametry myszy jako wejœcie i zwraca w nich indeksy pola 
										// -1,-1 jesli dana wspolrzedna nie nalezy do planszy
	int strzal(int*, int*);				//0 niepoprawny, 1 poprawny || argumenty to pozycja myszki
	int strzal_indeks(int, int);				//0 niepoprawny,-1, pud³o, 1 poprawny || argumenty to indeks
	//*** funkcje zwi¹zane z za³ogami statków;
	int dodaj_statek(int*,int*);			/// ustawia statek na planszy. dodaje go do za³ogi. 
										///	w przypadku, gdy chcemy dodaæ statek na istniej¹cym ju¿ statku, funkcja zwraca 0
										///1 gdy dodamy statek, dwa gdy dodamy te¿ za³ogê;
										/// (wspó³rzêdne myszki)
	void dodaj_statek_bez_zakazow(int, int,bool); // argumentami s¹ indeksy kratki; funkjca nie zakazuje innych pol;
	void wpisz_kratke(int, int, int, int);	//wpisz kratce i,j stan _stan i przypisz j¹ do za³ogi _za³oga;
	bool koncz_gre();					// zwraca 1 kiedy niema wiecej statkow do zbicia;
	void oczysc_z_zakazow();			// usowa stan zakazu z planszy. u¿ywane po udanej edycji (na³o¿eniu) statków
	int stan_do_zapisu(int, int);		//// 0=puste, -(2n)=statek za³ogi n, 2=zakazane, -()=zbite, 4=zabite(drugi stan zakazania)
	int zlicz_trupy();
	int zlicz_zywych();
};