#include "sasiedzi.h"
#include "ransac.h"
#include <iostream>
#include <fstream>

int main ()
{

	std::vector <pary> ransac_wynik;
	std::vector <pary> ransac_wynik2;

	obraz obraz1;
	obraz1.wczytaj ( "data/response71" );

	obraz obraz2;
	obraz2.wczytaj ( "data/response72" );

	sasiedzi sasiedz;
	ransac rans;
	srand ( (unsigned int) time ( NULL ) );

	std::vector <pary> wzajemni_sasiedzi = sasiedz.wzajemni_najblizsi_sasiedzi ( obraz1, obraz2 );
	if ( 0 )
	{
		std::ofstream MyFile;
		MyFile.open ( "punktyw.tsv" );
		MyFile << "x1	y1	x2	y2" << endl;
		for ( auto &element : wzajemni_sasiedzi )
		{
			MyFile << element.pierwszy.toString () << "	" << element.drugi.toString () << "\n";
		}
		MyFile.close ();
	}
	if ( 1 )
	{
		int ile_sasiadow = 20;
		double prog = 0.50;
		std::ofstream MyFile2;
		MyFile2.open ( "punktys.tsv" );
		MyFile2 << "x1	y1	x2	y2" << endl;
		std::vector <pary> spojni_sasiedzi = sasiedz.spojnosc_sasiedztwa ( wzajemni_sasiedzi, ile_sasiadow, prog );
		for ( auto &element : spojni_sasiedzi )
		{
			MyFile2 << element.pierwszy.toString () << "	" << element.drugi.toString () << "\n";
		}
		MyFile2.close ();
	}
	if ( 0 )
	{
		int max_error_afi = 20;
		Mat <double> maciez_afi = rans.ransac_metoda ( wzajemni_sasiedzi, 1000, max_error_afi, 0 );
		int max_error_per = 90;
		Mat <double> maciez_per = rans.ransac_metoda ( wzajemni_sasiedzi, 1000, max_error_per, 1 );

		std::ofstream MyFile3;
		MyFile3.open ( "punktya.tsv" );
		MyFile3 << "x1	y1	x2	y2" << endl;
		std::ofstream MyFile4;
		MyFile4.open ( "punktyp.tsv" );
		MyFile4 << "x1	y1	x2	y2" << endl;
		for ( auto &element : wzajemni_sasiedzi )
		{
			if ( rans.model_blad ( maciez_afi, element ) < max_error_afi )
			{
				MyFile3 << element.pierwszy.toString () << "	" << element.drugi.toString () << "\n";
			}
			if ( rans.model_blad ( maciez_per, element ) < max_error_per )
			{
				MyFile4 << element.pierwszy.toString () << "	" << element.drugi.toString () << "\n";
			}
		}
		MyFile3.close ();
		MyFile4.close ();
	}





	//std::cout << maciez << "\n";
	std::cout << "\nend\n";

	//std::getchar ();
}