#pragma once
#include "kratka.h"
#include <vector>
class zaloga_statku {
	//za�oga opiekuje si� statkiem
	// grupuje kratki w statek i informuje nas kiedy statek ginie;
	// niema sensu pami�ta� jak dok�adnie wygl�da statek - od tego jest plansza!
	int hp;
	std::vector <kratka*> zaloga;
	void zatop();				// zmie� wygl�d ca�ego statku na w pe�ni zatopiony
public:
	zaloga_statku(void);
	~zaloga_statku();
	void operator+=(kratka*);
	bool operator==(kratka);
	bool operator==(kratka*);
	void operator-=(kratka*);
	bool sprawdz_zniszczenia(); // true - niema zniszcze�. false - oberwali�my
	bool operator!();			// inny spos�b sprawdzania zniszcze�
	int zwroc_hp() { return hp; };//hp zalogi
	int ile();					//rozmiar za�ogi
	kratka* zwroc_kratke(int);	//oddaje i-t� kratk� z kontenera
	bool zywy();				// sprawdzamy czy jakikakolwiek czesc statku jeszcze plywa; // 1 zywy 0 trup
};