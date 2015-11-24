/*
Projekt stworzony na zajêcia z Programowania Obiektowo Orientowanego,
przez Mateusza Lewandowskiego (122599) i Krzysztofa Jurkiewicza (122546).
Gra jest grywalna dla ró¿nych rozdzielczoœci,lecz projektowana by³a domyœlnie pod rozdzielczoœæ 1280x720, 
i wtedy dzia³a najlepiej

Sztuczna inteligencja ustawia swoje statki na jednym, lub dwóch kratkach gdy¿ takie roz³o¿enie
zmusza gracza do wiêkszej losowoœci jego ruchów (os³abia przewagê cz³owieka, jak¹ jest intelekt).
Gracz dostaje fory w postaci 2-sekundowego udostêpnienia mapy przeciwnika. 
Wprowadza to element pamiêciowy do gry i nieznacznie zwiêksza szanse gracza(cz³owieka) na wygran¹.

Statki rysowane s¹ "kratka pp kratce" dziêki czemu mog¹ przyjmowaæ ró¿ne kszta³ty.
maxymalna iloœæ statków i wykorzystanych kratek ograniczona jest ich kosztem oraz iloœci¹ punktów 
jakie mo¿emy na nie wydaæ

*/
#include "driver.h"
const int szer_okna = 3*1280/10;
const int wys_okna = 3*720/10;
void zamknij_program();
void fgra_1_vs_1();
void fgra_1_vs_ai();
void fwczytaj();
#define ROZMIAR_PLANSZY_DEFINE 10

ALLEGRO_DISPLAY *ekran;
int main(int argc, char **argv)
{


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	al_set_app_name("Gra w statki");
	al_install_keyboard();
	al_install_mouse();

	silnik(szer_okna, wys_okna);

	return 0;
}

void zamknij_program()
{
	exit(0);
}

void fgra_1_vs_1() {
	gra moja_gra(ROZMIAR_PLANSZY_DEFINE, 0);
	moja_gra.rozpocznij_gre_1vs1();
	al_rest(0.5);
}
void fgra_1_vs_ai() {
	gra moja_gra(ROZMIAR_PLANSZY_DEFINE, 1);
	moja_gra.rozpocznij_gre_1vsAI();
	al_rest(0.5);
}
void fwczytaj() {
	int rozmiar;
	bool ai;
	std::ifstream odczyt;
	std::ifstream* ptr;
	std::ifstream test("plik_zapisu.txt");
	if (test.good()) {
		test.close();
		odczyt.open("plik_zapisu.txt", std::ios_base::in);
		odczyt >> rozmiar;
		odczyt >> ai;
		ptr = &odczyt;
		gra moja_gra(rozmiar, ai);
		moja_gra.odczyt = 1;
		moja_gra.wczytaj_gre(ptr);
		if (ai)moja_gra.rozpocznij_gre_1vsAI();
		else moja_gra.rozpocznij_gre_1vs1();
		al_rest(0.5);
	}
	test.close();
}