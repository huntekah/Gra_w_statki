#include "gra.h"
#define POKAZ_PLANSZE_KOMPUTERA 1
const int MAX_ILOSC_PUNKTOW = 10000;
const int CENA_STATKU = 367;
const int CENA_KRATKI = 401;
// da danej liczby punktow  liczymy odpowiednie równanie liniowe 

gra::~gra()
{
	al_destroy_bitmap(tlo_gry);
	al_destroy_bitmap(tlo_zmiana_tury);
	al_destroy_event_queue(kolejka_eventow);
	al_destroy_font(czcionka);
}

gra::gra(int _rozmiar_planszy, bool _AI):
	rozmiar_planszy(_rozmiar_planszy),
	AI(_AI), 
	odczyt(0),
	AGraczA(_rozmiar_planszy, wspolrzedna((al_get_display_width(ekran) * ((double)3/29)),
		(al_get_display_width(ekran) * ((double)3 / 29))),0),
	BGraczA(_rozmiar_planszy, wspolrzedna((al_get_display_width(ekran) * ((double)16 / 29)),
		(al_get_display_width(ekran) * ((double)3 / 29))),1),/*1*/
	BGraczB(_rozmiar_planszy, wspolrzedna((al_get_display_width(ekran) * ((double)3 / 29)),
		(al_get_display_width(ekran) * ((double)3 / 29))),0),
	AGraczB(_rozmiar_planszy, wspolrzedna((al_get_display_width(ekran) * ((double)16 / 29)),
		(al_get_display_width(ekran) * ((double)3 / 29))), 1),
	p_zapisu( (al_get_display_width(ekran) * ((double)20 / 29)),
		(al_get_display_width(ekran) * ((double)14 / 29)),static_cast<std::string>("zapisz_img.png"))
{
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();


	szer_okna = al_get_display_width(al_get_current_display());
	wys_okna = al_get_display_height(al_get_current_display());

	ROZMIAR_CZCIONKI = (70 * szer_okna) / 1280;
	czcionka = al_load_ttf_font("times.ttf", ROZMIAR_CZCIONKI, 0);

	al_set_target_backbuffer(ekran);

	tlo_gry = al_load_bitmap("tlo_gry.png");
	tlo_zmiana_tury = al_load_bitmap("zmiana_tury.png");
	al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
	

	kolejka_eventow = al_create_event_queue();
	if (!kolejka_eventow) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(ekran);
		exit(-1);
	}
	al_register_event_source(kolejka_eventow, al_get_display_event_source(ekran));
	al_register_event_source(kolejka_eventow, al_get_mouse_event_source());

	
	al_flip_display();
	tura = 0;
}

void gra::zmiana_tury(std::string nazwa)
{
	bool temp = 1;
	al_draw_scaled_bitmap(tlo_zmiana_tury, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
	al_draw_text(czcionka, al_map_rgb(200, 200, 200), szer_okna/2,wys_okna/2 , ALLEGRO_ALIGN_CENTRE, nazwa.data());
	al_flip_display();
	while(temp){
	al_init_timeout(&timeout, 0.05);
	bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
		if (get_event) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				temp = 0;
			}
		}
	}
	tura++;
}

void gra::rozpocznij_gre_1vs1()
{
	if (!odczyt) {
		edytuj(1);
		zmiana_tury("klinkij by ustawic statki gracza B");
		al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
		al_flip_display();
		edytuj(0);
		tura++;
	}
	bool koniec=0;
	while (!koniec) {
		al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
		if (tura % 2 == 0) {// ruch gracza A
			if (AGraczA.koncz_gre()) { koniec = 1; 
			zmiana_tury("wygral gracz B");
			}
			if (!koniec) {
				zmiana_tury("ruch gracz A");
				ruch_gracz_A();
			}
		}
		else {				// ruch gracza B
			if (BGraczB.koncz_gre()){ koniec = 1;
			zmiana_tury("wygral gracz A");
			}
			if (!koniec) {
				zmiana_tury("ruch gracz B");
				ruch_gracz_B();
			}
		}
		al_rest(1.0);
	}
}

void gra::rozpocznij_gre_1vsAI()
{
	if (!odczyt) {
		edytuj(1);
		zmiana_tury("Komputer ustawia swoje statki");
		al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
		al_flip_display();
		generuj_ai(); // generuje planszê dla naszego komputera
	}

	bool koniec = 0;
	while (!koniec) {
		al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
		//ruch gracza
			if (AGraczA.koncz_gre()) {
				koniec = 1;
				zmiana_tury("wygral komputer");
				break;
			}
			if (!koniec) {
				ruch_gracz_A();
			}

			//ruch komputera
			if (BGraczB.koncz_gre()) {
				koniec = 1;
				zmiana_tury("wygral gracz A");
				break;
			}
			if (!koniec) {
				ruch_AI();
			}
			al_rest(1.0);
	}
}

void gra::edytuj(bool tura_A)
{
	statystyka moja_statystyka(wspolrzedna(szer_okna / 2, wys_okna / 20), "Pozostalo punktow:", szer_okna/64);
	statystyka cena_nowego(wspolrzedna(szer_okna / 2, 2*wys_okna / 20), "Cena nowego statku", szer_okna/85);
	statystyka cena_dobudowy(wspolrzedna(szer_okna / 2, 3*wys_okna / 20), "Cena dobudowy:", szer_okna/85);
	int ilosc_punktow = MAX_ILOSC_PUNKTOW;
	int zmien_podswietlenie = 0;
	int index_i;
	int index_j;
	if (tura_A) {
		while (ilosc_punktow>0) {

			moja_statystyka.wyswietl(ilosc_punktow);
			cena_nowego.wyswietl(CENA_KRATKI + CENA_STATKU);
			cena_dobudowy.wyswietl(CENA_KRATKI);

			zmien_podswietlenie=0;
			AGraczA.narysuj();
			BGraczA.narysuj();
			al_init_timeout(&timeout, 0.02);

			bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
			if (get_event) {
				index_i = event.mouse.x;	// zczytujemy wspó³rzêdne myszy
				index_j = event.mouse.y;
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
				else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					int result=AGraczA.dodaj_statek(&index_i, &index_j);
					if(result) AGraczB.dodaj_statek_bez_zakazow(index_i, index_j,result-1);
					if (result >= 1)ilosc_punktow-=CENA_KRATKI;
					if (result == 2)ilosc_punktow-=CENA_STATKU;

				}
				else  {
					zmien_podswietlenie = 1;
					AGraczA.ktore_to_pole(&index_i, &index_j);	// przez referencjê dostajemy indeks pola, nad którym jesteœmy
					if ((index_i + 1) && (index_j + 1)) { 
						AGraczA.podswietl(index_i, index_j); 
						zmien_podswietlenie = 2;
					}
				}
			}
			al_flush_event_queue(kolejka_eventow);
			if (zmien_podswietlenie !=0) {
				al_flip_display();
				if ((index_i + 1) && (index_j + 1)) {
					AGraczA.narysuj(index_i, index_j);
					zmien_podswietlenie--;
				}
			}
		}

		AGraczA.oczysc_z_zakazow();
		AGraczA.narysuj();
		AGraczB.narysuj_i_wczytaj();
		al_flip_display();
	}
	else {
		while (ilosc_punktow>0) {

			moja_statystyka.wyswietl(ilosc_punktow);
			cena_nowego.wyswietl(CENA_KRATKI+CENA_STATKU);
			cena_dobudowy.wyswietl(CENA_KRATKI);

			zmien_podswietlenie = 0;
			BGraczB.narysuj();
			AGraczB.narysuj();
			al_init_timeout(&timeout, 0.02);
			bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
			if (get_event) {
				index_i = event.mouse.x;	// zczytujemy wspó³rzêdne myszy
				index_j = event.mouse.y;
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
				else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					int result = BGraczB.dodaj_statek(&index_i, &index_j);
					if (result) BGraczA.dodaj_statek_bez_zakazow(index_i, index_j, result - 1);
					if (result >= 1)ilosc_punktow-=CENA_KRATKI;
					if (result == 2)ilosc_punktow-=CENA_STATKU;

				}
				else {
					zmien_podswietlenie = 1;
					BGraczB.ktore_to_pole(&index_i, &index_j);	// przez referencjê dostajemy indeks pola, nad którym jesteœmy
					if ((index_i + 1) && (index_j + 1)) {
						BGraczB.podswietl(index_i, index_j);
						zmien_podswietlenie = 2;
					}
				}
			}
			al_flush_event_queue(kolejka_eventow);
			if (zmien_podswietlenie != 0) {
				al_flip_display();
				if ((index_i + 1) && (index_j + 1)) {
					BGraczB.narysuj(index_i, index_j);
					zmien_podswietlenie--;
				}
			}
		}

		BGraczB.oczysc_z_zakazow();
		BGraczB.narysuj();
		BGraczA.narysuj();
		al_flip_display();
	}
}

void gra::ruch_gracz_A()
{
	statystyka statystyka_zywych(wspolrzedna(szer_okna / 5, 2 * wys_okna / 20), "Jednostek wroga:", szer_okna / 64);
	statystyka statystyka_trupow(wspolrzedna(szer_okna / 5, 3 * wys_okna / 20), "Pokonales juz:", szer_okna / 64);
	al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
	AGraczA.narysuj();
	BGraczA.narysuj();
	p_zapisu.narysuj_sie(ekran);
	al_flip_display();

	bool strzal = 1;
	int index_i;
	int index_j;
	int zmien_podswietlenie=0;
	bool rysuj_cala=0;

	while (strzal) {
		statystyka_zywych.wyswietl(BGraczB.zlicz_zywych());
		statystyka_trupow.wyswietl(BGraczB.zlicz_trupy());
		zmien_podswietlenie = 0;
		al_init_timeout(&timeout, 0.02);
		index_i = event.mouse.x;	// zczytujemy wspó³rzêdne myszy
		index_j = event.mouse.y;
		bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
		if (get_event) {

			if(event.type== ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (p_zapisu.czy_to_przycisk(index_i, index_j)) zapisz_gre(); // przycisk wciœniêty, nale¿y zareagowaæ!
				int result = BGraczA.strzal(&index_i, &index_j);
				BGraczB.strzal_indeks(index_i,index_j);
				if (result == -1)strzal = 0; // jeœli pud³o, to ruch przypada drugiemu graczowi
				else if (strzal == 1) {		// jeœli natomiast trafiliœmy, sprawdzamy czy jest sens dalej strzelaæ;
					if (BGraczB.koncz_gre())
					strzal = 0;
				}
				if(result) rysuj_cala = 1;
			}
			else {
				//podœwietlenie przycisku zapisu
				if (p_zapisu.czy_to_przycisk(index_i, index_j))p_zapisu.podswietl(al_map_rgb(255,255,255));
				else p_zapisu.podswietl(al_map_rgb(0, 0, 0));
				//podœwietlenie pola planszy
				zmien_podswietlenie = 1;
				int temp_index_i = index_i;					// poniewa¿ indeksy otrzymujemy w referencji, nie chcemy zgubiæ po³o¿enia myszy;
				int temp_index_j = index_j;
				BGraczA.ktore_to_pole(&index_i, &index_j);	// przez referencjê dostajemy indeks pola, nad którym jesteœmy
				if ((index_i + 1) && (index_j + 1)) {
					BGraczA.podswietl(index_i, index_j);
					zmien_podswietlenie = 2;
				}
				else {
					index_i = temp_index_i;
					index_j = temp_index_j;
					AGraczA.ktore_to_pole(&index_i, &index_j);
					if ((index_i + 1) && (index_j + 1)) {
						AGraczA.podswietl(index_i, index_j);
						zmien_podswietlenie = 2;
					}
				}
			}
		}
		al_flush_event_queue(kolejka_eventow);
		if (rysuj_cala) {
			rysuj_cala = 0;
			BGraczA.narysuj();
			al_flip_display();
		}
		else if (zmien_podswietlenie != 0) {
			al_flip_display();
			if ((index_i + 1) && (index_j + 1)) {
				AGraczA.narysuj(index_i, index_j);
				BGraczA.narysuj(index_i, index_j);
				zmien_podswietlenie--;
			}
		}
	}
	al_flip_display();
	al_rest(0.5);

}

void gra::ruch_gracz_B()
{
	statystyka statystyka_zywych(wspolrzedna(szer_okna / 5, 2 * wys_okna / 20), "Jednostek wroga:", szer_okna / 64);
	statystyka statystyka_trupow(wspolrzedna(szer_okna / 5, 3 * wys_okna / 20), "Pokonales juz:", szer_okna / 64);
	al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
	BGraczB.narysuj();
	AGraczB.narysuj();
	p_zapisu.narysuj_sie(ekran);
	al_flip_display();

	bool strzal = 1;
	int index_i;
	int index_j;
	int zmien_podswietlenie = 0;
	bool rysuj_cala = 0;

	while (strzal) {
		statystyka_zywych.wyswietl(AGraczA.zlicz_zywych());
		statystyka_trupow.wyswietl(AGraczA.zlicz_trupy());
		zmien_podswietlenie = 0;
		al_init_timeout(&timeout, 0.02);
		index_i = event.mouse.x;	// zczytujemy wspó³rzêdne myszy
		index_j = event.mouse.y;
		bool get_event = al_wait_for_event_until(kolejka_eventow, &event, &timeout);
		if (get_event) {

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(0);
			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (p_zapisu.czy_to_przycisk(index_i, index_j)) zapisz_gre(); // przycisk wciœniêty, nale¿y zareagowaæ!
				int result = AGraczB.strzal(&index_i, &index_j);
				AGraczA.strzal_indeks(index_i, index_j);
				if (result == -1)strzal = 0; // jeœli pud³o, to ruch przypada drugiemu graczowi
				else if (strzal == 1) {		// jeœli natomiast trafiliœmy, sprawdzamy czy jest sens dalej strzelaæ;
					if (AGraczA.koncz_gre())
						strzal = 0;
				}
				if (result) rysuj_cala = 1;
			}
			else {
				if (p_zapisu.czy_to_przycisk(index_i, index_j))p_zapisu.podswietl(al_map_rgb(255, 255, 255));
				else p_zapisu.podswietl(al_map_rgb(0, 0, 0));
				zmien_podswietlenie = 1;
				int temp_index_i = index_i;					// poniewa¿ indeksy otrzymujemy w referencji, nie chcemy zgubiæ po³o¿enia myszy;
				int temp_index_j = index_j;
				AGraczB.ktore_to_pole(&index_i, &index_j);	// przez referencjê dostajemy indeks pola, nad którym jesteœmy
				if ((index_i + 1) && (index_j + 1)) {
					AGraczB.podswietl(index_i, index_j);
					zmien_podswietlenie = 2;
				}
				else {
					index_i = temp_index_i;
					index_j = temp_index_j;
					BGraczB.ktore_to_pole(&index_i, &index_j);
					if ((index_i + 1) && (index_j + 1)) {
						BGraczB.podswietl(index_i, index_j);
						zmien_podswietlenie = 2;
					}
				}
			}
		}
		al_flush_event_queue(kolejka_eventow);
		if (rysuj_cala) {
			rysuj_cala = 0;
			AGraczB.narysuj();
			al_flip_display();
		}
		else if (zmien_podswietlenie != 0) {
			al_flip_display();
			if ((index_i + 1) && (index_j + 1)) {
				BGraczB.narysuj(index_i, index_j);
				AGraczB.narysuj(index_i, index_j);
				zmien_podswietlenie--;
			}
		}
	}
	al_flip_display();
	al_rest(0.5);
}

void gra::ruch_AI()
{
	statystyka statystyka_zywych(wspolrzedna(szer_okna / 5, 2 * wys_okna / 20), "Zostalo do zabicia:", szer_okna / 64);
	statystyka statystyka_trupow(wspolrzedna(szer_okna / 5, 3 * wys_okna / 20), "Pokonalem juz:", szer_okna / 64);
	inicjalizuj(rozmiar_planszy);
	int strzal = 1;
	wspolrzedna result;
	while (strzal) {
		al_draw_scaled_bitmap(tlo_gry, 0, 0, al_get_bitmap_width(tlo_gry), al_get_bitmap_height(tlo_gry), 0, 0, szer_okna, wys_okna, 0);
		statystyka_zywych.wyswietl(AGraczA.zlicz_zywych());
		statystyka_trupow.wyswietl(AGraczA.zlicz_trupy());
		AGraczA.narysuj();
		BGraczA.narysuj();
		p_zapisu.narysuj_sie(ekran);
		al_flip_display();
		al_rest(0.1);

		wpisz_plansze_do_ai();
		result = strzel_ai();
		strzal = AGraczA.strzal_indeks(result.x, result.y);
		AGraczB.strzal_indeks(result.x, result.y);
		if (AGraczA.koncz_gre()){
			strzal = -1;
	}
		if (strzal == 0 || strzal == 1)strzal = 1;
		else strzal = 0;
	}
}

void gra::wpisz_plansze_do_ai()
{	// jest sens przepisywaæ tylko planszê A widzian¹ przez gracza B (AI)
	int _stan;
	for (int i = 0; i < rozmiar_planszy; i++) {
		for (int j = 0; j < rozmiar_planszy; j++) {
			_stan = AGraczB.wyglad[i][j].jaki_stan();
			wpisz_do_planszy_ai(wspolrzedna(i, j), _stan);
		}
	}
}

void gra::generuj_ai()
{
	srand(time(NULL));
	int ilosc_punktow = MAX_ILOSC_PUNKTOW;
	while (ilosc_punktow > 0) {
		//~~
#if (POKAZ_PLANSZE_KOMPUTERA==1)
		BGraczB.narysuj();
		BGraczA.narysuj();
		al_flip_display();
		//~~
#endif
		int temp_x = rand() % szer_okna;
		int temp_y = rand() % wys_okna;
		int result = BGraczB.dodaj_statek(&temp_x, &temp_y);
		if (result) BGraczA.dodaj_statek_bez_zakazow(temp_x, temp_y, result - 1);
		if (result >= 1)ilosc_punktow -= CENA_KRATKI;
		if (result == 2)ilosc_punktow -= CENA_STATKU;
	}
#if (POKAZ_PLANSZE_KOMPUTERA==1)
	al_rest(2);
#endif
}

bool gra::zapisz_gre()
{
	std::ofstream zapis;
	zapis.open("plik_zapisu.txt",(std::ios::in|std::ios::trunc)); //otwieramy plik w trybie do zapisu i czyœcimy jego poprzedni¹ zawartoœæ;
	zapis << rozmiar_planszy<<"\n";
	zapis << AI << "\n";
	zapis << tura<<"\n";
	zapis << "\n";
	for (int i = 0; i < rozmiar_planszy; i++) {
		for (int j = 0; j < rozmiar_planszy; j++) {
			zapis << AGraczA.stan_do_zapisu(i, j);
			zapis << "\t";
		}
		zapis << "\n";
	}
	zapis << "\n";
	for (int i = 0; i < rozmiar_planszy; i++) {
		for (int j = 0; j < rozmiar_planszy; j++) {
			zapis << AGraczB.stan_do_zapisu(i, j);
			zapis << " " << AGraczB.wyglad[i][j].odkryte;
			zapis << "\t";
		}
		zapis << "\n";
	}
	zapis << "\n";
	for (int i = 0; i < rozmiar_planszy; i++) {
		for (int j = 0; j < rozmiar_planszy; j++) {
			zapis << BGraczB.stan_do_zapisu(i, j);
			zapis << "\t";
		}
		zapis << "\n";
	}
	zapis << "\n";
	for (int i = 0; i < rozmiar_planszy; i++) {
		for (int j = 0; j < rozmiar_planszy; j++) {
			zapis << BGraczA.stan_do_zapisu(i, j);
			zapis << " " << BGraczA.wyglad[i][j].odkryte;
			zapis << "\t";
		}
		zapis << "\n";
	}
	zapis.close();
	return false;
}

bool gra::wczytaj_gre(std::ifstream* ptr)
{
	int dana;
	int zaloga;
	int stan;
	bool odkryte;
	//kolejnosæ plansz AA, AB 0/1, BB, BA 0/1
	*ptr >> tura;
	tura--;
	for (int i = 0; i < rozmiar_planszy; i++)
		for (int j = 0; j < rozmiar_planszy; j++) {
			*ptr >> dana;
			zaloga = odszyfruj_zaloge(dana);
			stan = odszyfruj_stan(dana);
			AGraczA.wpisz_kratke(i, j, stan, zaloga); //wpisz kratce i,j stan 'stan' i przypisz j¹ do za³ogi 'zaloga';
		}
	for (int i = 0; i < rozmiar_planszy; i++)
		for (int j = 0; j < rozmiar_planszy; j++) {
			*ptr >> dana;
			zaloga = odszyfruj_zaloge(dana);
			stan = odszyfruj_stan(dana);
			AGraczB.wpisz_kratke(i, j, stan, zaloga); //wpisz kratce i,j stan 'stan' i przypisz j¹ do za³ogi 'zaloga';
			*ptr >> odkryte;
			if (odkryte)AGraczB.wyglad[i][j].odkryj();
		}
	for (int i = 0; i < rozmiar_planszy; i++)
		for (int j = 0; j < rozmiar_planszy; j++) {
			*ptr >> dana;
			zaloga = odszyfruj_zaloge(dana);
			stan = odszyfruj_stan(dana);
			BGraczB.wpisz_kratke(i, j, stan, zaloga); //wpisz kratce i,j stan 'stan' i przypisz j¹ do za³ogi 'zaloga';
		}
	for (int i = 0; i < rozmiar_planszy; i++)
		for (int j = 0; j < rozmiar_planszy; j++) {
			*ptr >> dana;
			zaloga = odszyfruj_zaloge(dana);
			stan = odszyfruj_stan(dana);
			BGraczA.wpisz_kratke(i, j, stan, zaloga); //wpisz kratce i,j stan 'stan' i przypisz j¹ do za³ogi 'zaloga';
			*ptr >> odkryte;
			if (odkryte)BGraczA.wyglad[i][j].odkryj();
		}
	(*ptr).close();
	return false;
}
