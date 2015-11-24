#pragma once
// klasa bêd¹ca sk³adnikiem wielu innych, pojawiaj¹ca siê na ka¿dym kroku w tym projekcie.
class wspolrzedna {
	public:
		int x;
		int y;
		wspolrzedna(int = 0, int = 0); //konstruktor
		// OPERATORY dzia³añ na wspó³rzêdnych
		wspolrzedna& operator+(wspolrzedna &druga);
		wspolrzedna& operator-(wspolrzedna &druga);
		void operator+=(wspolrzedna& druga);
		void operator-=(wspolrzedna& druga);
		bool operator==(wspolrzedna& temp);
		wspolrzedna& operator=(const wspolrzedna&);
		wspolrzedna (wspolrzedna&);
};

/* EXAMPLE
wspolrzedna A,C,D,E;
wspolrzedna B(3, 5);
A = B;    
B += A;
C = D + B;
E = C - D + A;
*/