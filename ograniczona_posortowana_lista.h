#pragma once
#include <list>
#include <utility>
#include <iostream>
class ograniczona_posortowana_lista
{
public:
	int ilosc_miejsc;
	std::list < std::pair<double, int>> lista;
	ograniczona_posortowana_lista ();
	ograniczona_posortowana_lista (int ile);
	bool dodaj (  double odleglosc, int index );
	double ilosc_indexow_wspolnych ( ograniczona_posortowana_lista ogr_lista2 );
	void debug_print ();
	~ograniczona_posortowana_lista ();
};

