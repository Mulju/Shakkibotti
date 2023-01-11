#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;

Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	// Ei tosiaan oo vihree
	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_BLUE);
	*/
	// Tällä shakkinappulat toimii
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == 0)
			{
				// Laittaa numeron laudan vasempaan reunaan valkoisella värillä
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8 - i << "  ";
			}
			
			if ((i % 2 == 0 &&
				(j % 2) - 1 == 0) ||
				((i % 2) - 1 == 0 &&
				 j % 2 == 0))
			{
				// Tuottaa parillisen rivin kuvioinnin laudalle vihreällä värillä
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0x0030);
			}
			else
			{
				// Resettaa värin valkoiseksi
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}

			if (_asema->_lauta[i][j] == NULL)
			{
				// Tulostaa välin nappuloiden väliin
				wcout << "  ";
			}
			else
			{
				// Tulostaa nappulan unicoden
				wcout << _asema->_lauta[i][j]->getUnicode() << " ";
			}
		}
		wcout << "\n";
	}

	wcout << "\n    a b c d e f g h\n\n";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
