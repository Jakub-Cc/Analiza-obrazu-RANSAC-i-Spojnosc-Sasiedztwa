#include "ransac.h"



ransac::ransac ()
{
}

Mat<double> ransac::ransac_metoda ( std::vector<pary> zbior_punktow_kluczowych, int ile_krokow, double max_error, int jaka_transformacja )
{
	std::cout << "ransac in progres "<<jaka_transformacja<< "\n";
	Mat<double> best_model;
	double best_score = 0;
	for ( int i = 0; i < ile_krokow; i++ )
	{
		//std::cout << i;
		Mat <double> model;
		do
		{
			if ( jaka_transformacja == 0 )
			{
				std::vector<pary> wybrane_ptk = sasiad.kilka_losowych_punktow ( zbior_punktow_kluczowych, 3);
				model = oblicz_model_afiniczny ( wybrane_ptk );
			}
			else
			{
				std::vector<pary> wybrane_ptk = sasiad.kilka_losowych_punktow ( zbior_punktow_kluczowych, 4 );
				model = oblicz_model_perspektywistyczny ( wybrane_ptk );
			}
		} while ( model.empty () );

		double wynik = 0;
		for ( auto &element : zbior_punktow_kluczowych )
		{
			double blad = model_blad ( model, element );
			if ( blad < max_error )
				wynik++;
		}
		if ( wynik > best_score )
		{
			best_score = wynik;
			best_model = model;
			std::cout << "model zmiana\n";
		}

	}
	return best_model;
}

double ransac::model_blad ( Mat<double> model, pary para )
{
	double wynik = para.pierwszy.transformata ( model ).odleglosc ( para.drugi );
	return wynik;
}


Mat<double> ransac::oblicz_model_afiniczny ( std::vector<pary> zbior_punktow_kluczowych )
{
	Mat <double> maciez ( 6, 6, fill::zeros );

	maciez ( 0, 0 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x;
	maciez ( 0, 1 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y;
	maciez ( 0, 2 ) = 1;
	maciez ( 1, 0 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x;
	maciez ( 1, 1 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y;
	maciez ( 1, 2 ) = 1;
	maciez ( 2, 0 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x;
	maciez ( 2, 1 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y;
	maciez ( 2, 2 ) = 1;

	maciez ( 3, 3 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x;
	maciez ( 3, 4 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y;
	maciez ( 3, 5 ) = 1;
	maciez ( 4, 3 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x;
	maciez ( 4, 4 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y;
	maciez ( 4, 5 ) = 1;
	maciez ( 5, 3 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x;
	maciez ( 5, 4 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y;
	maciez ( 5, 5 ) = 1;

	Mat <double> maciez_uv ( 6, 1 );
	maciez_uv ( 0, 0 ) = zbior_punktow_kluczowych[0].drugi.wspolrzedna_x;
	maciez_uv ( 1, 0 ) = zbior_punktow_kluczowych[1].drugi.wspolrzedna_x;
	maciez_uv ( 2, 0 ) = zbior_punktow_kluczowych[2].drugi.wspolrzedna_x;
	maciez_uv ( 3, 0 ) = zbior_punktow_kluczowych[0].drugi.wspolrzedna_y;
	maciez_uv ( 4, 0 ) = zbior_punktow_kluczowych[1].drugi.wspolrzedna_y;
	maciez_uv ( 5, 0 ) = zbior_punktow_kluczowych[2].drugi.wspolrzedna_y;

	Mat <double> wynik;
	Mat <double> mac_I ( 6, 6, fill::eye );

	try
	{
		Mat <double> inversed = solve ( maciez, mac_I );
		wynik = inversed * maciez_uv;
	}
	catch ( const std::exception& e )
	{
		std::cout << "\n";
		std::cout << e.what ();
	}
	

	Mat <double> wynik2 ( 3, 3, fill::zeros );

	wynik2 ( 0, 0 ) = wynik ( 0, 0 );
	wynik2 ( 0, 1 ) = wynik ( 1, 0 );
	wynik2 ( 0, 2 ) = wynik ( 2, 0 );
	wynik2 ( 1, 0 ) = wynik ( 3, 0 );
	wynik2 ( 1, 1 ) = wynik ( 4, 0 );
	wynik2 ( 1, 2 ) = wynik ( 5, 0 );
	wynik2 ( 2, 2 ) = 1;

	return wynik2;
}

Mat<double> ransac::oblicz_model_perspektywistyczny ( std::vector<pary> zbior_punktow_kluczowych )
{
	Mat <double> maciez ( 8, 8, fill::zeros );
	maciez ( 0, 0 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x;
	maciez ( 0, 1 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y;
	maciez ( 0, 2 ) = 1;

	maciez ( 1, 0 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x;
	maciez ( 1, 1 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y;
	maciez ( 1, 2 ) = 1;

	maciez ( 2, 0 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x;
	maciez ( 2, 1 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y;
	maciez ( 2, 2 ) = 1;

	maciez ( 3, 0 ) = zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_x;
	maciez ( 3, 1 ) = zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_y;
	maciez ( 3, 2 ) = 1;

	maciez ( 4, 3 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x;
	maciez ( 4, 4 ) = zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y;
	maciez ( 4, 5 ) = 1;

	maciez ( 5, 3 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x;
	maciez ( 5, 4 ) = zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y;
	maciez ( 5, 5 ) = 1;

	maciez ( 6, 3 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x;
	maciez ( 6, 4 ) = zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y;
	maciez ( 6, 5 ) = 1;

	maciez ( 7, 3 ) = zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_x;
	maciez ( 7, 4 ) = zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_y;
	maciez ( 7, 5 ) = 1;

	maciez ( 0, 6 ) = -zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[0].drugi.wspolrzedna_x;
	maciez ( 0, 7 ) = -zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[0].drugi.wspolrzedna_x;

	maciez ( 1, 6 ) = -zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[1].drugi.wspolrzedna_x;
	maciez ( 1, 7 ) = -zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[1].drugi.wspolrzedna_x;

	maciez ( 2, 6 ) = -zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[2].drugi.wspolrzedna_x;
	maciez ( 2, 7 ) = -zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[2].drugi.wspolrzedna_x;

	maciez ( 3, 6 ) = -zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[3].drugi.wspolrzedna_x;
	maciez ( 3, 7 ) = -zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[3].drugi.wspolrzedna_x;

	maciez ( 4, 6 ) = -zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[0].drugi.wspolrzedna_y;
	maciez ( 4, 7 ) = -zbior_punktow_kluczowych[0].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[0].drugi.wspolrzedna_y;

	maciez ( 5, 6 ) = -zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[1].drugi.wspolrzedna_y;
	maciez ( 5, 7 ) = -zbior_punktow_kluczowych[1].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[1].drugi.wspolrzedna_y;

	maciez ( 6, 6 ) = -zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[2].drugi.wspolrzedna_y;
	maciez ( 6, 7 ) = -zbior_punktow_kluczowych[2].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[2].drugi.wspolrzedna_y;

	maciez ( 7, 6 ) = -zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_x*zbior_punktow_kluczowych[3].drugi.wspolrzedna_y;
	maciez ( 7, 7 ) = -zbior_punktow_kluczowych[3].pierwszy.wspolrzedna_y*zbior_punktow_kluczowych[3].drugi.wspolrzedna_y;

	Mat <double> maciez_uv ( 8, 1 );
	maciez_uv ( 0, 0 ) = zbior_punktow_kluczowych[0].drugi.wspolrzedna_x;
	maciez_uv ( 1, 0 ) = zbior_punktow_kluczowych[1].drugi.wspolrzedna_x;
	maciez_uv ( 2, 0 ) = zbior_punktow_kluczowych[2].drugi.wspolrzedna_x;
	maciez_uv ( 3, 0 ) = zbior_punktow_kluczowych[3].drugi.wspolrzedna_x;
	maciez_uv ( 4, 0 ) = zbior_punktow_kluczowych[0].drugi.wspolrzedna_y;
	maciez_uv ( 5, 0 ) = zbior_punktow_kluczowych[1].drugi.wspolrzedna_y;
	maciez_uv ( 6, 0 ) = zbior_punktow_kluczowych[2].drugi.wspolrzedna_y;
	maciez_uv ( 7, 0 ) = zbior_punktow_kluczowych[3].drugi.wspolrzedna_y;

	// std::cout << maciez << "\n";
	//std::cout << det ( maciez );
	//std::getchar ();
	
	Mat <double> wynik(8,1, fill::zeros);
	Mat <double> mac_I ( 8, 8, fill::eye );

	try
	{
		Mat <double> inversed = solve ( maciez, mac_I );
		wynik = inversed * maciez_uv;
	}
	catch ( const std::exception& e )
	{
		std::cout << "\n";
		std::cout << e.what ();
	}
	

	Mat <double> wynik2 ( 3, 3, fill::zeros );
	wynik2 ( 0, 0 ) = wynik ( 0, 0 );
	wynik2 ( 0, 1 ) = wynik ( 1, 0 );
	wynik2 ( 0, 2 ) = wynik ( 2, 0 );
	wynik2 ( 1, 0 ) = wynik ( 3, 0 );
	wynik2 ( 1, 1 ) = wynik ( 4, 0 );
	wynik2 ( 1, 2 ) = wynik ( 5, 0 );
	wynik2 ( 2, 0 ) = wynik ( 6, 0 );
	wynik2 ( 2, 1 ) = wynik ( 7, 0 );
	wynik2 ( 2, 2 ) = 1;

	return wynik2;
}


ransac::~ransac ()
{
}
