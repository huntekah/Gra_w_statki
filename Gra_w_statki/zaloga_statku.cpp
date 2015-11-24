#include "zaloga_statku.h"

zaloga_statku::zaloga_statku(void) :hp(0){}

zaloga_statku::~zaloga_statku()
{
	zaloga.clear();
}

void zaloga_statku::operator+=(kratka * modul_statku)
{
	zaloga.push_back(modul_statku);
	if((*modul_statku).jaki_stan()==1)hp++; // zwiêkszamy iloœæ kratek w za³odze
}

bool zaloga_statku::operator==(kratka wzor)
{
	for (int i = 0; i < zaloga.size(); i++)if (*zaloga[i] == wzor)return true;
	return false;
}

bool zaloga_statku::operator==(kratka *wzor)
{
	for (int i = 0; i < zaloga.size(); i++)if (zaloga[i] == wzor)return true;
	return false;
}

void zaloga_statku::operator-=(kratka *wzor)
{
	int i = 0;
	for (; i < zaloga.size(); i++) 
		if (zaloga[i] == wzor) {
		zaloga.erase(zaloga.begin() + i);
		hp--;
		break;
		}
}

bool zaloga_statku::sprawdz_zniszczenia()
{
	int temp_hp=0;
	for (int i = 0; i < zaloga.size(); i++)
		if (zaloga[i]->jaki_stan() == 1)temp_hp++; // zliczamy statki
	if (temp_hp == hp)return true;
	hp = temp_hp;
	if (hp == 0)zatop();
	return false;
}

bool zaloga_statku::operator!()
{
	return sprawdz_zniszczenia();
}

void zaloga_statku::zatop()
{
	for (int i = 0; i < zaloga.size(); i++) {
		zaloga[i]->zatop();
	}
}

int zaloga_statku::ile()
{
	return zaloga.size();
}

kratka * zaloga_statku::zwroc_kratke(int index_i)
{
	if (index_i < ile())return zaloga[index_i];
	return nullptr;
}

bool zaloga_statku::zywy()
{
	if (hp)return true;
	return false;
}
