#include "statek.h"

statek::statek(bool **tablica_wygladu, int tab_i, int tab_j):rozmiar_x(tab_i),rozmiar_y(tab_j)
{
	wyglad = new kratka*[tab_i];		//utworzenie tablicy wygl¹du
	for (int i = 0; i < tab_i; i++) {
		wyglad[i] = new kratka[tab_j];
	}
	for (int i = 0; i < tab_i*tab_j; i++) {
		if (tablica_wygladu[i / tab_i][i%tab_i])wyglad[i / tab_i][i%tab_i].zmiana_stanu(1);
		else wyglad[i / tab_i][i%tab_i].zmiana_stanu(0);
	}

}

statek::~statek()
{
	for (int i = 0; i < rozmiar_x; i++)delete [] wyglad[i];
	delete [] wyglad;
}

void statek::obroc()
{
	kratka **kopia;
	kopia = new kratka*[rozmiar_y];		//utworzenie tablicy wygl¹du
	for (int i = 0; i < rozmiar_y; i++) {
		kopia[i] = new kratka[rozmiar_x];
	}
	for (int i = 0; i < rozmiar_x; i++)
		for (int j = 0; j < rozmiar_y; j++) {
			// TODO zamiana tablicy
		}

}

int statek::zbij(kratka *)
{
	//TODO ZBIJ kratka
	return 0;
}
