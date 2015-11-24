#include "Artificial_Inteligence.h"
 int Artificial_inteligence::czy_zdefiniowano=0;
 int Artificial_inteligence::wymiar_x;
 int Artificial_inteligence::wymiar_y;
 int Artificial_inteligence::licznik;
 int Artificial_inteligence::ile;
 int Artificial_inteligence::ile_pustych;
 int** Artificial_inteligence::plansza_ai;

void Artificial_inteligence::inicjalizuj(int _wymiar_x)
{
	if (!czy_zdefiniowano) {
		wymiar_x = _wymiar_x;
		wymiar_y = _wymiar_x;
		licznik = 0;
		ile = ile_pustych = wymiar_x*wymiar_y;
		// Definicja tablicy i wyzerowanie (nie wiemy gdzie s¹ statki na pocz¹tku)
		plansza_ai = new int *[wymiar_y];
		for (int i = 0; i < wymiar_y; i++)
			plansza_ai[i] = new int[wymiar_x];

		//Zerowanie
		for (int i = 0; i < wymiar_y; i++)
			for (int j = 0; j < wymiar_x; j++)
				plansza_ai[i][j] = 0;
		// initialize random seed: 
		srand(time(NULL));
	}
	
}

wspolrzedna Artificial_inteligence::strzel_ai()
{
	int analiza = 0;    // Brak analizy na wstêpie
	int x_strzal;       // Wspó³rzêdne punktu wybranego do strza³u po analizie
	int y_strzal;

	// Szukamy pola, które jest s¹siadem pola trafionego ale nie zatopionego
	if (!analiza) {
		for (int y = 0; y < wymiar_y; y++)
			for (int x = 0; x < wymiar_x; x++)
				if (plansza_ai[x][y] == 1) {
					if (x - 1 >= 0 && x - 1 < wymiar_x &&
						plansza_ai[x - 1][y] == 0) {
						y_strzal = y;
						x_strzal = x - 1;
						analiza = 1;
					}
					else if (x + 1 >= 0 && x + 1 < wymiar_x &&
						plansza_ai[x + 1][y] == 0) {
						y_strzal = y;
						x_strzal = x + 1;
						analiza = 1;
					}
					else if (y + 1 >= 0 && y + 1 < wymiar_y &&
						plansza_ai[x][y + 1] == 0) {
						y_strzal = y + 1;
						x_strzal = x;
						analiza = 1;
					}
					else if (y - 1 >= 0 && y - 1 < wymiar_y &&
						plansza_ai[x][y - 1] == 0) {
						y_strzal = y - 1;
						x_strzal = x;
						analiza = 1;
					}

					if (analiza == 1) goto wyjscie1;
				}
	} wyjscie1:

	// Jeœli nie ma takiego statku to szukamy pustego pola losowego, na którym wykonamy dalsz¹ analizê
	int x_los = rand() % wymiar_x;
	int y_los = rand() % wymiar_y;
	for (int y = y_los; ; ) {
		for (int x = x_los; ; ) {
			if (plansza_ai[x][y] == 0) {
				x_los = x;
				y_los = y;
				goto wyjscie_z_petli;   // nie zaleca siê u¿ywania goto, ale przydaje siê przy wychodzeniu z zagnie¿d¿onych pêtli
			}

			x = (x + 1) % wymiar_x;
			if (x == x_los) break;
		}
		y = (y + 1) % wymiar_y;
		if (y == y_los) break;
	} wyjscie_z_petli:

	// Jeœli po³owa planszy zosta³a wystrzelona, sztuczna inteligencja zwiêksza prawdopodobieñstwo
	// strzelenia w pola, które maj¹ wiêcej pustych s¹siadów
	if (!analiza) {
		if (ile_pustych < ile) {
			bool taktyczny_strzal=false;  // zmienna okreœlaj¹ca czy strzelamy w pole strategiczne
			if ((rand() % 100) < 800) taktyczny_strzal = true;  // prawdopodobieñstwo jest równe 30/100 = 30%, jeœli algorytm siê sprawdzi, mo¿na zwiêkszyæ
			if (taktyczny_strzal) { // Szukamy pola z najwiêksz¹ liczb¹ s¹siadów
				int max_zm = -1;
				int x_max;
				int y_max;
				for (int y_zm = y_los; ;) {
					for (int x_zm = x_los; ;) {
						if (plansza_ai[x_zm][y_zm] != 0) { // Jeœli pole nie jest puste
							x_zm = (x_zm + 1) % wymiar_x;
							if (x_zm == x_los) break;
							continue;
						}
															 // Liczymy s¹siadów
						int sasiedzi = 0;
						
						if (x_zm - 1 >= 0 && x_zm - 1 < wymiar_x &&
							plansza_ai[x_zm - 1][y_zm] == 0)
							sasiedzi++;
						if (x_zm + 1 >= 0 && x_zm + 1 < wymiar_x &&
							plansza_ai[x_zm + 1][y_zm] == 0)
							sasiedzi++;
						if (y_zm + 1 >= 0 && y_zm + 1 < wymiar_y &&
							plansza_ai[x_zm][y_zm + 1] == 0)
							sasiedzi++;
						if (y_zm - 1 >= 0 && y_zm - 1 < wymiar_y &&
							plansza_ai[x_zm][y_zm - 1] == 0)
							sasiedzi++;
						// Jeœli to pole jest polem strategicznym to ustawiamy w odpowiednich zmiennych
						if (sasiedzi > max_zm) {
							max_zm = sasiedzi;
							x_max = x_zm;
							y_max = y_zm;
						}
						if (max_zm == 4)break;
						x_zm = (x_zm + 1) % wymiar_x;
						if (x_zm == x_los) break;
					}
					y_zm = (y_zm + 1) % wymiar_y;
					if (y_zm == y_los) break;
				}
				analiza = 2;
				x_strzal = x_max;
				y_strzal = y_max;
			}
		}


	}
	if (!analiza) {
		x_strzal = x_los;
		y_strzal = y_los;
		analiza = 3;
	}
	ile_pustych = 0;
	return wspolrzedna(x_strzal, y_strzal);
}
void Artificial_inteligence::wpisz_do_planszy_ai(wspolrzedna wsp, int _stan)
{
	//_stan 0-puste, 1-statek, 2-zakazane 3-zbite, 4-zabite(drugi stan zakazania)
	if (wsp.x >= 0 && wsp.x < wymiar_x && wsp.y >= 0 && wsp.y < wymiar_y) {
		if (_stan == 0)_stan = 0;
		else if (_stan == 1)_stan = 0;
		else if (_stan == 2)_stan = 2;
		else if (_stan == 3)_stan = 1;
		else if (_stan == 4)_stan = 2;
		if (_stan == 0)ile_pustych++;
		plansza_ai[wsp.x][wsp.y] = _stan;
	}
}
