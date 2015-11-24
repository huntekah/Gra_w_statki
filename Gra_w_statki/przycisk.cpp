#include "przycisk.h"

przycisk::przycisk(int p_x,int p_y):
	polozenie(p_x,p_y){}


void przycisk::przycisniecie()
{
	wsk_fun();
}

void przycisk::ustaw_funkcje(void(*wskf)())
{
	wsk_fun = wskf;
}
