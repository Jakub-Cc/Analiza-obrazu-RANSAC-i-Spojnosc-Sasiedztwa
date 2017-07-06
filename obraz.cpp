#include "obraz.h"



obraz::obraz ()
{
}

obraz::obraz ( int liczba_punktow_kluczowychh, punkt_kluczowy * punktyy )
{
	liczba_punktow_kluczowych = liczba_punktow_kluczowychh;
	punkty = new punkt_kluczowy[liczba_punktow_kluczowych];
	for ( int i = 0; i < liczba_punktow_kluczowych; i++ )
		punkty[i] = punktyy[i];
}

bool obraz::resize ( int liczba_punktow_kluczowychh )
{
	liczba_punktow_kluczowych = liczba_punktow_kluczowychh;
	punkty = new punkt_kluczowy[liczba_punktow_kluczowych];
	return true;
}

//TO DO zrobic aby serio wczytywalo
bool obraz::wczytaj ( std::string adres )
{
	std::cout << "loading... \n";
	std::string s;
	std::ifstream file;
	file.open ( adres.c_str () );
	std::stringstream st;
	if ( file.is_open () )
	{
		{
			st << file.rdbuf ();
			from_stream ( st );
		}
	}
	file.close ();
	return true;
}

void obraz::from_stream ( std::istream & StrmWe )
{
	int ilosc_cech;
	int ilosc_punktow;
	StrmWe.ignore ( 12 );
	StrmWe >> ilosc_cech;
	StrmWe.ignore ( 10 );
	StrmWe >> ilosc_punktow;
	StrmWe.ignore ( 9 );
	resize ( ilosc_punktow );

	for ( int i = 0; i < ilosc_punktow; i++ )
	{
		punkt_kluczowy ptk;
		StrmWe >> ptk;
		punkty[i] = ptk;
	}
}


obraz::~obraz ()
{
}

