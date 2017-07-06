#include "sasiedzi.h"



sasiedzi::sasiedzi ()
{
}

std::vector<pary> sasiedzi::wzajemni_najblizsi_sasiedzi ( obraz obraz1, obraz obraz2 )
{
	std::vector <pary> wzajemni_sasiedzi;
	double  ** maciez_odleglosci = new double *[obraz1.liczba_punktow_kluczowych];
	for ( int i = 0; i < obraz1.liczba_punktow_kluczowych; i++ )
	{
		maciez_odleglosci[i] = new double[obraz2.liczba_punktow_kluczowych] ();
		for ( int j = 0; j < obraz2.liczba_punktow_kluczowych; j++ )
		{
			maciez_odleglosci[i][j] = obraz1.punkty[i].odlegosc_cech ( obraz2.punkty[j] );
		}
	}

	for ( int i = 0; i < obraz1.liczba_punktow_kluczowych; i++ )
	{
		double najblizszy_b = maciez_odleglosci[i][0];
		int index_b = 0;
		for ( int j = 1; j < obraz2.liczba_punktow_kluczowych; j++ )
		{
			if ( najblizszy_b > maciez_odleglosci[i][j] )
			{
				najblizszy_b = maciez_odleglosci[i][j];
				index_b = j;
			}
		}
		/*
		double najblizszy_c = maciez_odleglosci[0][index_b];
		int index_c = 0;
		for ( int k = 0; k < obraz1.liczba_punktow_kluczowych; k++ )
		{
			if ( najblizszy_c > maciez_odleglosci[k][index_b] )
			{
				najblizszy_c = maciez_odleglosci[k][index_b];
				index_c = k;
			}
		}

		if ( index_c == i )
		{
			wzajemni_sasiedzi.push_back ( pary ( obraz1.punkty[i], obraz2.punkty[index_b] ) );
		}
		*/
		
		bool najbl = true;
		for ( int k = 0; k < obraz1.liczba_punktow_kluczowych && najbl; k++ )
		{
			if ( maciez_odleglosci[k][index_b] < najblizszy_b )
			{
				najbl = false;
			}
		}
		if ( najbl )
		{
			wzajemni_sasiedzi.push_back ( pary ( obraz1.punkty[i], obraz2.punkty[index_b] ) );
		}

	}
	return wzajemni_sasiedzi;
}


std::vector<pary> sasiedzi::spojnosc_sasiedztwa ( std::vector<pary> wzajemni_sasiedzi, int ilosc_sasiadow, double prog )
{
	std::cout << "spojni sasiedzi in progres\n";

	std::vector <pary> spojni_sasiedzi;



	for ( auto &element : wzajemni_sasiedzi )
	{
		pary para = element;
		double * odleglosci = new double[wzajemni_sasiedzi.size ()] ();

		ograniczona_posortowana_lista dziwna_lista ( ilosc_sasiadow );
		for ( int i = 0; i < wzajemni_sasiedzi.size (); i++ )
		{
			odleglosci[i] = element.pierwszy.odleglosc ( wzajemni_sasiedzi[i].pierwszy );
			dziwna_lista.dodaj ( odleglosci[i], i );
		}

		double * odleglosci2 = new double[wzajemni_sasiedzi.size ()] ();
		ograniczona_posortowana_lista dziwna_lista2 ( ilosc_sasiadow );
		for ( int i = 0; i < wzajemni_sasiedzi.size (); i++ )
		{
			odleglosci2[i] = element.drugi.odleglosc ( wzajemni_sasiedzi[i].drugi );
			dziwna_lista2.dodaj ( odleglosci2[i], i );
		}

		/*dziwna_lista.debug_print ();
		std::cout << '\n';
		dziwna_lista2.debug_print ();
		std::getchar ();
		*/
		if ( dziwna_lista.ilosc_indexow_wspolnych ( dziwna_lista2 ) > prog )
		{
			spojni_sasiedzi.push_back ( element );
		}
	}

	return spojni_sasiedzi;
}

//Moze zmieniac kolejnosc w vektorze wejsciowym, ale czy to wazne?
std::vector<pary> sasiedzi::kilka_losowych_punktow ( std::vector<pary> wzajemni_sasiedzi, int ilosc )
{
	random_unique ( wzajemni_sasiedzi.begin (), wzajemni_sasiedzi.end (), ilosc );

	std::vector<pary> punkty;

	for ( int i = 0; i < ilosc; i++ )
	{
		//std::cout << wzajemni_sasiedzi[i].pierwszy.wspolrzedna_x << " " << wzajemni_sasiedzi[i].pierwszy.wspolrzedna_y << " ";
		//std::cout << wzajemni_sasiedzi[i].drugi.wspolrzedna_x << " " << wzajemni_sasiedzi[i].drugi.wspolrzedna_y << "\n";
		punkty.push_back ( wzajemni_sasiedzi[i] );
	}

	return punkty;
}




sasiedzi::~sasiedzi ()
{
}
