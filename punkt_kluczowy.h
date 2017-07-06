#pragma once
#include <string>
#include <armadillo>
using namespace arma;

class punkt_kluczowy
{
public:
	double wspolrzedna_x;
	double wspolrzedna_y;
	double a;
	double b;
	double c;
	static const int n = 128;
	double cechy[n];
	punkt_kluczowy ();
	punkt_kluczowy ( double xx, double yy, double aa, double bb, double cc, double cechyy[] );
	double odleglosc ( punkt_kluczowy punkt );
	double odlegosc_cech ( punkt_kluczowy punkt );
	punkt_kluczowy transformata ( Mat<double> model );
	void from_stream ( std::istream & StrmWe );
	std::string toString ();
	~punkt_kluczowy ();
	friend std::istream & operator >> ( std::istream & StrmWe, punkt_kluczowy & b );
};

