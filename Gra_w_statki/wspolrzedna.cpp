#include "wspolrzedna.h"

wspolrzedna::wspolrzedna(int wsp_x, int wsp_y) :x(wsp_x), y(wsp_y) {}

wspolrzedna & wspolrzedna::operator+(wspolrzedna & druga)
{
	wspolrzedna robocza;
	robocza.x = x + druga.x;
	robocza.y = y + druga.y;
	return robocza;
}

wspolrzedna & wspolrzedna::operator-(wspolrzedna & druga)
{
	wspolrzedna robocza;
	robocza.x = x - druga.x;
	robocza.y = y - druga.y;
	return robocza; 
}

void wspolrzedna::operator+=(wspolrzedna & druga)
{
	x += druga.x;
	y += druga.y;
}

void wspolrzedna::operator-=(wspolrzedna & druga)
{
	x -= druga.x;
	y -= druga.y;
}

bool wspolrzedna::operator==(wspolrzedna & temp)
{
	if ((x == temp.x) && (y == temp.y)) return true;
	return false;
}

wspolrzedna & wspolrzedna::operator=(const wspolrzedna &wzor)
{
	x = wzor.x;
	y = wzor.y;
	return *this;
}

wspolrzedna::wspolrzedna(wspolrzedna &wzor)
{
	x = wzor.x;
	y = wzor.y;

}
