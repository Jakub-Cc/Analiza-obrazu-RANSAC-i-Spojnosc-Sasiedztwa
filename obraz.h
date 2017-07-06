#pragma once
#include "punkt_kluczowy.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <streambuf>
#include <sstream>  

class obraz
{
public:
	int liczba_punktow_kluczowych;
	punkt_kluczowy * punkty;
	obraz ();
	obraz (int liczba_punktow_kluczowychh, punkt_kluczowy * punktyy );
	bool resize ( int liczba_punktow_kluczowychh );
	bool wczytaj ( std::string adres );
	void from_stream ( std::istream & StrmWe );
	
	~obraz ();
};

