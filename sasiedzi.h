#pragma once
#include "obraz.h"
#include "pary.h"
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "ograniczona_posortowana_lista.h"

class sasiedzi
{
public:
	sasiedzi ();
	std::vector <pary> wzajemni_najblizsi_sasiedzi ( obraz obraz1, obraz obraz2 );
	std::vector <pary> spojnosc_sasiedztwa ( std::vector <pary> wzajemni_sasiedzi, int ilosc_sasiadow, double prog );
	std::vector <pary> kilka_losowych_punktow ( std::vector <pary> wzajemni_sasiedzi, int ilosc );
	template<class bidiiter>
	bidiiter random_unique ( bidiiter begin, bidiiter end, size_t num_random );
	~sasiedzi ();
};

template<class bidiiter>
inline bidiiter sasiedzi::random_unique ( bidiiter begin, bidiiter end, size_t num_random )
{
	std::vector <pary> punkty;
	size_t left = std::distance ( begin, end );
	while ( num_random-- )
	{
		bidiiter r = begin;
		std::advance ( r, rand () % left );
		std::swap ( *begin, *r );
		++begin;
		--left;

	}
	return begin;
}
