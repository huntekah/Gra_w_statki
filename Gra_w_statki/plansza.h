#pragma once
//klasa ta przechowuje najwa�niejszy element ca�ej gry - plansz�. to tutaj statki wyp�ywaj� na bitw�
#include "wspolrzedna.h"
#include "kratka.h"
#include "zaloga_statku.h"
class plansza {
	int szerokosc_ekranu;
	int wysokosc_ekranu;
	int szerokosc_planszy;				// w pixelach
	int wysokosc_planszy;				// w pixelach

	int zbij(int, int);					// 0 (kratka zakazane/ poza plansz�), -1 pud�o, 1 trafiony
	//*** funkcje zwi�zane z za�ogami statk�w;
	void odkryj_pola_wokol_trupa(int);	// argumentem jest indeks za�ogi kt�r� chcemy obs�u�y�	
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
	plansza(int,wspolrzedna, bool=0);	// domy�lnie plansza jest odkryta
	~plansza(); 
	// GRAFICZNE / sterowanie polami
	void narysuj();
	void narysuj_i_wczytaj();
	void narysuj(int, int);				//rysuje konkretne pole, lecz nie flipuje
	void narysuj_flip(int, int);		// tak jak poprzednio, flipuje(od�wieza)
	void podswietl(int, int); 
	void ktore_to_pole(int*, int*);		//przyjmuje parametry myszy jako wej�cie i zwraca w nich indeksy pola 
										// -1,-1 jesli dana wspolrzedna nie nalezy do planszy
	int strzal(int*, int*);				//0 niepoprawny, 1 poprawny || argumenty to pozycja myszki
	int strzal_indeks(int, int);				//0 niepoprawny,-1, pud�o, 1 poprawny || argumenty to indeks
	//*** funkcje zwi�zane z za�ogami statk�w;
	int dodaj_statek(int*,int*);			/// ustawia statek na planszy. dodaje go do za�ogi. 
										///	w przypadku, gdy chcemy doda� statek na istniej�cym ju� statku, funkcja zwraca 0
										///1 gdy dodamy statek, dwa gdy dodamy te� za�og�;
										/// (wsp�rz�dne myszki)
	void dodaj_statek_bez_zakazow(int, int,bool); // argumentami s� indeksy kratki; funkjca nie zakazuje innych pol;
	void wpisz_kratke(int, int, int, int);	//wpisz kratce i,j stan _stan i przypisz j� do za�ogi _za�oga;
	bool koncz_gre();					// zwraca 1 kiedy niema wiecej statkow do zbicia;
	void oczysc_z_zakazow();			// usowa stan zakazu z planszy. u�ywane po udanej edycji (na�o�eniu) statk�w
	int stan_do_zapisu(int, int);		//// 0=puste, -(2n)=statek za�ogi n, 2=zakazane, -()=zbite, 4=zabite(drugi stan zakazania)
	int zlicz_trupy();
	int zlicz_zywych();
};