#include "plansza.h"

int plansza::zbij(int index_i, int index_j)
{
	return wyglad[index_i][index_j].zbij();
}
void plansza::odkryj_pola_wokol_trupa(int index_i)
{
	if (!zaloga[index_i].zywy()) { // dzia³am tylko na trupach
		for (int i = 0; i < zaloga[index_i].ile(); i++) {
			// granice planszy = 0,rozmiar_planszy
			wspolrzedna przetwarzany_indeks;

			przetwarzany_indeks = (zaloga[index_i].zwroc_kratke(i))->indeks;
			for (int j = 0; j < 8; j++) {
				if (j == 0) przetwarzany_indeks.y += 1;
				else if (j == 1) przetwarzany_indeks.x += 1;
				else if (j ==2 || j==3 ) przetwarzany_indeks.y -= 1;
				else if (j == 4 || j == 5) przetwarzany_indeks.x -= 1;
				else if (j == 6 || j == 7) 	przetwarzany_indeks.y += 1;

				if (czy_jest_w_planszy(przetwarzany_indeks))
					if (0 == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].jaki_stan()) { //sprawdzamy czy to jest puste pole x+1
						wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].zmiana_stanu(2);
						wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].odkryj_i_zabij();
					
					}

			}
		}
	}
}

void plansza::zakaz_pola_wokol_statku(int index_i) {
		for (int i = 0; i < zaloga[index_i].ile(); i++) {
			// granice planszy = 0,rozmiar_planszy
			wspolrzedna przetwarzany_indeks;

			przetwarzany_indeks = (zaloga[index_i].zwroc_kratke(i))->indeks;
			for (int j = 0; j < 8; j++) {
				if (j < 1) przetwarzany_indeks.y += 1;
				else if (j < 2) przetwarzany_indeks.x += 1;
				else if (j < 4) przetwarzany_indeks.y -= 1;
				else if (j < 6) przetwarzany_indeks.x -= 1;
				else if (j <8) 	przetwarzany_indeks.y += 1;

				if (czy_jest_w_planszy(przetwarzany_indeks))
					if (0 == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].jaki_stan()) { //sprawdzamy czy to jest puste pole x+1
						wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].zmiana_stanu(2);
						wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].odkryj();
				
					}

			}
		}
}

void plansza::zakaz_pola_wokol_statku_ukryty(int index_i)
{
		for (int i = 0; i < zaloga[index_i].ile(); i++) {
			// granice planszy = 0,rozmiar_planszy
			wspolrzedna przetwarzany_indeks;

			przetwarzany_indeks = (zaloga[index_i].zwroc_kratke(i))->indeks;
			for (int j = 0; j < 8; j++) {
				if (j < 1) przetwarzany_indeks.y += 1;
				else if (j < 2) przetwarzany_indeks.x += 1;
				else if (j < 4) przetwarzany_indeks.y -= 1;
				else if (j < 6) przetwarzany_indeks.x -= 1;
				else if (j <8) 	przetwarzany_indeks.y += 1;

				if (czy_jest_w_planszy(przetwarzany_indeks))
					if (0 == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].jaki_stan()) { //sprawdzamy czy to jest puste pole x+1
						wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y].zmiana_stanu(2);
			
					}

			}
		}
}

bool plansza::czy_jest_w_planszy(wspolrzedna indeks)
{
	if (((indeks.x) < 0 || (indeks.y < 0)) || ((indeks.x >= ilosc_pol) || (indeks.y >= ilosc_pol))) return false;
	return true;
}

int plansza::zwroc_indeks_statku(wspolrzedna indeks)
{
	if (czy_jest_w_planszy(indeks)) {
		int i = 0;
		for (; i < zaloga.size(); i++) {
			if (zaloga[i] == wyglad[indeks.x][indeks.y])break;
		}
		return i;
	}
	return -1;
}

plansza::plansza(int kilosc_pol,wspolrzedna _polozenie, bool zakryta):ilosc_pol(kilosc_pol),polozenie(_polozenie)
{
	al_set_target_backbuffer(ekran);
	wysokosc_ekranu = al_get_display_height(al_get_current_display());
	szerokosc_ekranu = al_get_display_width(al_get_current_display());
		
	wyglad = new kratka*[kilosc_pol];		//utworzenie tablicy wygl¹du
	for (int i = 0; i < kilosc_pol; i++) {
		wyglad[i] = new kratka[kilosc_pol];
	}

	//ZAKRYCIE lub odkrycie odpowiedniej planszy
	for (int i = 0; i < kilosc_pol; i++)
		for (int j = 0; j < kilosc_pol; j++) {
			wyglad[i][j].indeks = wspolrzedna(i, j);
			wyglad[i][j].odkryte = (!zakryta);
			wyglad[i][j].zmiana_stanu(0); 
			wyglad[i][j].ustal_polozenie(wspolrzedna(polozenie.x + j*wyglad[i][j].rozmiar_x, polozenie.y + i*wyglad[i][j].rozmiar_y));
		}
	szerokosc_planszy = ((wyglad[0][0]).rozmiar_x * ilosc_pol);
	wysokosc_planszy = ((wyglad[0][0]).rozmiar_y * ilosc_pol);
}

int plansza::strzal(int * mysz_x, int *mysz_y)
{
	if ((*mysz_y >= polozenie.y && *mysz_y <= polozenie.y + wysokosc_planszy)
		&& (*mysz_x >= polozenie.x && *mysz_x <= polozenie.x + szerokosc_planszy)) {
		//wysy³amy do funkcji pozycjê myszki
			ktore_to_pole(mysz_x, mysz_y);	// a dziêki referencji otrzymujemy indeks pola;
			int index_i = *mysz_x;	
			int index_j = *mysz_y;
			if (czy_jest_w_planszy(wspolrzedna(index_i, index_j))) {
				int wynik_zbicia = zbij(index_i, index_j);
				if (wynik_zbicia == 0)return false;
				else if (wynik_zbicia == 1) {
					int indeks_statku = zwroc_indeks_statku(wspolrzedna(index_i, index_j));
					zaloga[indeks_statku].sprawdz_zniszczenia();
					odkryj_pola_wokol_trupa(indeks_statku); // jeœli zniszczyliœmy ca³y statek		
				}
				return  wynik_zbicia;
			}
	}

	return false;
}

int plansza::strzal_indeks(int index_i, int index_j)
{

		if (czy_jest_w_planszy(wspolrzedna(index_i, index_j))) {
			int wynik_zbicia = zbij(index_i, index_j);
			if (wynik_zbicia == 0)return false;
			else if (wynik_zbicia == 1) {
				int indeks_statku = zwroc_indeks_statku(wspolrzedna(index_i, index_j));
				zaloga[indeks_statku].sprawdz_zniszczenia();
				odkryj_pola_wokol_trupa(indeks_statku); // jeœli zniszczyliœmy ca³y statek
				//if (CA£y statek jest zniszczony) to return 3;										
			}
			return  wynik_zbicia;
		}
	

	return false;
}

void plansza::dodaj_zaloge()
{
	zaloga_statku temp;
	zaloga.push_back(temp);
}

bool plansza::czy_sasiaduje(int index_j, int index_k)
{
	int index_i = zaloga.size() - 1;
	for (int i = 0; i < zaloga[index_i].ile(); i++) {
		// granice planszy = 0,rozmiar_planszy
		wspolrzedna przetwarzany_indeks;

		przetwarzany_indeks = (zaloga[index_i].zwroc_kratke(i))->indeks;
		// sprawdzenie, czy miesci sie w planszy;
		przetwarzany_indeks.x += 1;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.x -= 2;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.x += 1;
		przetwarzany_indeks.y += 1;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.y -= 2;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;

	}
	return false;

}

bool plansza::czy_sasiaduje_skos(int index_j, int index_k)
{
	int index_i = zaloga.size() - 1;
	for (int i = 0; i < zaloga[index_i].ile(); i++) {
		// granice planszy = 0,rozmiar_planszy
		wspolrzedna przetwarzany_indeks;

		przetwarzany_indeks = (zaloga[index_i].zwroc_kratke(i))->indeks;
		// sprawdzenie, czy miesci sie w planszy;
		przetwarzany_indeks.x += 1;
		przetwarzany_indeks.y += 1;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.x -= 2;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.y -= 2;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;
		przetwarzany_indeks.x += 2;
		if (czy_jest_w_planszy(przetwarzany_indeks))
			if (wyglad[index_j][index_k] == wyglad[przetwarzany_indeks.x][przetwarzany_indeks.y])return true;

	}
	return false;
}

int plansza::dodaj_statek(int *wsp_x, int *wsp_y)
{
	bool nowa_zaloga=1;
	ktore_to_pole(wsp_x, wsp_y);		// zamieniamy wspó³rzêdne myszy na wspó³rzêdne kratki
	if (*wsp_x == -1 || *wsp_y == -1)return false;
	if (wyglad[*wsp_x][*wsp_y].jaki_stan() == 1 || wyglad[*wsp_x][*wsp_y].jaki_stan() == 2) return 0;
	// czy modu³ statku s¹siaduje z ostatnio dodan¹ za³og¹;
	if (zaloga.empty()) { 
		wyglad[*wsp_x][*wsp_y].zmiana_stanu(1);
		dodaj_zaloge(); 
		zaloga[zaloga.size() - 1] += &(wyglad[*wsp_x][*wsp_y]);
		return 2;
	}
	else	nowa_zaloga=!czy_sasiaduje(*wsp_x, *wsp_y);
	if (nowa_zaloga) { 
		// czy nie sasiaduje po skosie?
		if (czy_sasiaduje_skos(*wsp_x,*wsp_y))return 0;
		zakaz_pola_wokol_statku_ukryty(zaloga.size() - 1);
		dodaj_zaloge(); 
	}
	wyglad[*wsp_x][*wsp_y].zmiana_stanu(1);
	zaloga[zaloga.size() - 1] += &(wyglad[*wsp_x][*wsp_y]);
	return (1+nowa_zaloga);
}

void plansza::dodaj_statek_bez_zakazow(int wsp_x, int wsp_y, bool nowa_zaloga)
{
	if (wsp_x == -1 || wsp_y == -1)return;
	if (wyglad[wsp_x][wsp_y].jaki_stan() == 1 || wyglad[wsp_x][wsp_y].jaki_stan() == 2) return;
	wyglad[wsp_x][wsp_y].zmiana_stanu(1);
	if (zaloga.empty()) {
		dodaj_zaloge();
		zaloga[zaloga.size() - 1] += &(wyglad[wsp_x][wsp_y]);
		return;
	}
	if (nowa_zaloga) {
		dodaj_zaloge();
	}

	zaloga[zaloga.size() - 1] += &(wyglad[wsp_x][wsp_y]);
	return;
}

void plansza::wpisz_kratke(int indeks_i, int indeks_j, int _stan, int temp_zaloga)
{
	wyglad[indeks_i][indeks_j].zmiana_stanu(_stan);
	if (temp_zaloga + 1) {
		//rzutowanie jest niezbêdne, ze wzglêdu na typ zwracany przez .size() [unsigned]
		while (temp_zaloga > ((int)zaloga.size() - 1)) { dodaj_zaloge(); }
		int a = 5;
		zaloga[temp_zaloga] += &wyglad[indeks_i][indeks_j];
	}
}

bool plansza::koncz_gre()
{
	for (int i = 0; i < zaloga.size(); i++) {
		zaloga[i].sprawdz_zniszczenia();
		if (zaloga[i].zywy())return false;
	}
	return true;
}

void plansza::oczysc_z_zakazow()
{
	for (int i = 0; i < ilosc_pol; i++)
		for (int j = 0; j < ilosc_pol; j++) {
			if (wyglad[i][j].jaki_stan() == 2)wyglad[i][j].zmiana_stanu(0);
		}
}

int plansza::stan_do_zapisu(int indeks_i, int indeks_j)
{
	int temp = wyglad[indeks_i][indeks_j].jaki_stan();
	if (temp == 0 || temp == 2 || temp == 4)return temp;
	if (temp == 3)temp = -1;
	else temp = -2;// ustawiamy temp na -1 gdy stan=3 i na -2 gdy stan =1
	temp = temp - (2 * zwroc_indeks_statku(wspolrzedna(indeks_i, indeks_j)));
	return temp;
}

int plansza::zlicz_trupy()
{
	int trupy=0;
	for (int i = 0; i < zaloga.size(); i++) {
		!zaloga[i]; //uaktualnia stan za³ogi;
		trupy += (zaloga[i].ile() - zaloga[i].zwroc_hp());
	}
	return trupy;
}

int plansza::zlicz_zywych()
{
	int zywi = 0;
	for (int i = 0; i < zaloga.size(); i++) {
		!zaloga[i]; //uaktualnia stan za³ogi;
		zywi += (zaloga[i].zwroc_hp());
	}
	return zywi;
}

plansza::~plansza()
{
	for (int i = 0; i < ilosc_pol; i++)delete[] wyglad[i];
	delete[] wyglad;
	zaloga.clear();
}

void plansza::narysuj()
{
	for (int i = 0; i < ilosc_pol; i++)
		for (int j = 0; j < ilosc_pol; j++) {
			wyglad[i][j].narysuj_sie();
		}
}

void plansza::narysuj_i_wczytaj()
{
	for (int i = 0; i < ilosc_pol; i++)
		for (int j = 0; j < ilosc_pol; j++) {
			wyglad[i][j].zaladuj_obrazek();
			wyglad[i][j].narysuj_sie();
		}
}

void plansza::narysuj(int index_i, int index_j)
{
	if (index_i >= 0 && index_j >= 0 && index_i < ilosc_pol && index_j < ilosc_pol) {
		wyglad[index_i][index_j].zaladuj_obrazek();
		wyglad[index_i][index_j].narysuj_sie();
	}
}

void plansza::narysuj_flip(int index_i, int index_j)
{
	if (czy_jest_w_planszy(wspolrzedna(index_i, index_j))) {
		wyglad[index_i][index_j].narysuj_sie();
		al_flip_display();
	}
}

void plansza::podswietl(int index_i, int index_j)
{ 
	if (czy_jest_w_planszy(wspolrzedna(index_i, index_j))) {
		wyglad[index_i][index_j].podswietl_sie();
	}
}

void plansza::ktore_to_pole(int *_index_i, int * _index_j)
{
	*_index_i -= polozenie.x;
	*_index_j -= polozenie.y;
	*_index_i = *_index_i / wyglad[0][0].rozmiar_x;
	*_index_j = *_index_j / wyglad[0][0].rozmiar_x;
	std::swap(*_index_i, *_index_j);
	if (*_index_i < 0 || *_index_j < 0) {

		*_index_i = -1;
		*_index_j = -1;
	}
	if (*_index_i >= ilosc_pol || *_index_j >= ilosc_pol) {

		*_index_i = -1;
		*_index_j = -1;
	}
}
