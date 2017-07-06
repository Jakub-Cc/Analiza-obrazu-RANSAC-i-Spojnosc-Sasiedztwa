#include "punkt_kluczowy.h"



punkt_kluczowy::punkt_kluczowy ()
{
}

punkt_kluczowy::punkt_kluczowy ( double xx, double yy, double aa, double bb, double cc, double cechyy[] )
{
	wspolrzedna_x = xx;
	wspolrzedna_y = yy;
	a = aa;
	b = bb;
	c = cc;
	for ( int i = 0; i < n; i++ )
		cechy[i] = cechyy[i];
}

double punkt_kluczowy::odleglosc ( punkt_kluczowy punkt )
{
	double det_x = wspolrzedna_x - punkt.wspolrzedna_x;
	double det_y = wspolrzedna_y - punkt.wspolrzedna_y;
	return det_x*det_x + det_y*det_y;
}

double punkt_kluczowy::odlegosc_cech ( punkt_kluczowy punkt )
{
	double sum = 0;
	for ( int i = 0; i < n; i++ )
	{
		sum += ( cechy[i] - punkt.cechy[i] )*( cechy[i] - punkt.cechy[i] );
	}
	return sum;
}


punkt_kluczowy punkt_kluczowy::transformata ( Mat<double> model )
{
	Mat <double> enter ( 3, 1 );
	enter ( 0, 0 ) = wspolrzedna_x;
	enter ( 1, 0 ) = wspolrzedna_y;
	enter ( 2, 0 ) = 1;
	
	Mat <double> wynik = model * enter;

	return punkt_kluczowy (wynik(0,0),wynik(1,0),a,b,c, cechy );
}

void punkt_kluczowy::from_stream ( std::istream & StrmWe )
{
	StrmWe.ignore ( 5 );
	StrmWe >> wspolrzedna_x;
	StrmWe.ignore ( 5 );
	StrmWe >> wspolrzedna_y;
	StrmWe.ignore ( 5 );
	StrmWe >> a;
	StrmWe.ignore ( 5 );
	StrmWe >> b;
	StrmWe.ignore ( 5 );
	StrmWe >> c;
	StrmWe.ignore ( 13 );

	for ( int i = 0; i < n; i++ )
	{
		StrmWe >> cechy[i];
		StrmWe.ignore ( 1 );
	}
	StrmWe.ignore ( 2 );
}

std::string punkt_kluczowy::toString ()
{
	std::string str = "";
	str += std::to_string ( wspolrzedna_x ) + "	" + std::to_string (  wspolrzedna_y );

	return str;
}




punkt_kluczowy::~punkt_kluczowy ()
{
}

std::istream & operator >> ( std::istream & StrmWe, punkt_kluczowy & b )
{
	b.from_stream ( StrmWe );
	return StrmWe;
}
