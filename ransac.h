#pragma once
#include <armadillo>
#include "sasiedzi.h"

using namespace arma;

class ransac
{
public:
	sasiedzi sasiad;
	ransac ();
	Mat<double> ransac_metoda ( std::vector <pary> zbior_punktow_kluczowych, int ile_krokow, double max_error, int jaka_transformacja );
	double model_blad ( Mat<double> model, pary para );
	Mat <double> oblicz_model_afiniczny ( std::vector <pary> zbior_punktow_kluczowych );
	Mat <double> oblicz_model_perspektywistyczny ( std::vector <pary> zbior_punktow_kluczowych );
	~ransac ();
};

