#pragma once
#include "punkt_kluczowy.h"
class pary
{
public:
	punkt_kluczowy pierwszy;
	punkt_kluczowy drugi;
	pary ();
	pary (punkt_kluczowy punkt1, punkt_kluczowy punkt2);
	~pary ();
};

