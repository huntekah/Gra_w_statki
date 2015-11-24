#pragma once
#include "kratka.h"
#include <vector>
class zaloga_statku {
	//za³oga opiekuje siê statkiem
	// grupuje kratki w statek i informuje nas kiedy statek ginie;
	// niema sensu pamiêtaæ jak dok³adnie wygl¹da statek - od tego jest plansza!
	int hp;
	std::vector <kratka*> zaloga;
	void zatop();				// zmieñ wygl¹d ca³ego statku na w pe³ni zatopiony
public:
	zaloga_statku(void);
	~zaloga_statku();
	void operator+=(kratka*);
	bool operator==(kratka);
	bool operator==(kratka*);
	void operator-=(kratka*);
	bool sprawdz_zniszczenia(); // true - niema zniszczeñ. false - oberwaliœmy
	bool operator!();			// inny sposób sprawdzania zniszczeñ
	int zwroc_hp() { return hp; };//hp zalogi
	int ile();					//rozmiar za³ogi
	kratka* zwroc_kratke(int);	//oddaje i-t¹ kratkê z kontenera
	bool zywy();				// sprawdzamy czy jakikakolwiek czesc statku jeszcze plywa; // 1 zywy 0 trup
};