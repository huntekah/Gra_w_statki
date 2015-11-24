#include "odszyfrowywanie.h"

int odszyfrowywanie::odszyfruj_stan(int dana)
{
	if (dana >= 0)return dana;
	else {
		if (dana % 2 == 0)return 1;
		else return 3;
	}
}

int odszyfrowywanie::odszyfruj_zaloge(int dana)
{
	if (dana >= 0)return -1;
	else {
		if (dana % 2 == 0)dana += 2;
		else dana += 1;
		return -(dana / 2);
	}

}
