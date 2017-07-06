#include "ograniczona_posortowana_lista.h"



ograniczona_posortowana_lista::ograniczona_posortowana_lista ()
{
}

ograniczona_posortowana_lista::ograniczona_posortowana_lista ( int ile )
{
	ilosc_miejsc = ile;
}

bool ograniczona_posortowana_lista::dodaj ( double odleglosc, int index )
{
	if ( odleglosc != 0 )
	{
		lista.push_back ( std::make_pair ( odleglosc, index ) );
		if ( lista.size () > ilosc_miejsc )
		{
			lista.sort ();
			lista.pop_back ();
		}
		return true;
	}
	return false;
}

double ograniczona_posortowana_lista::ilosc_indexow_wspolnych ( ograniczona_posortowana_lista ogr_lista2 )
{
	double ile = 0;
	for ( auto &element : lista )
	{
		for ( auto &element2 : ogr_lista2.lista )
		{
			if ( element.second == element2.second )
			{
				ile++;
			}
		}
	}
	//std::cout << ile <<" " <<ilosc_miejsc <<'\n';
	return ( ile / (double) ilosc_miejsc );
}

void ograniczona_posortowana_lista::debug_print ()
{
	for ( auto &element : lista )
	{
		std::cout << element.first << " " << element.second << '\n';
	}
}


ograniczona_posortowana_lista::~ograniczona_posortowana_lista ()
{
}
