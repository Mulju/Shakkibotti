#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"
#include "stdlib.h"

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
	string syote;
	int alkuKirjain;
	int alkuNumero;
	int loppuKirjain;
	int loppuNumero;
	
	while (true)
	{
		wcout << "Anna siirto:" << "\n";
		cin >> syote;
		system("cls");

		// Upseerisiirto
		if (syote.length() == 6 &&
			(syote[0] == (75 || 68 || 76 || 82 || 84)) &&
			(syote[1] > 96 && syote[1] < 105) &&
			(syote[4] > 96 && syote[4] < 105) &&
			(syote[2] > 48 && syote[2] < 57) &&
			(syote[5] > 48 && syote[5] < 57))
		{
			alkuKirjain = syote[1] - 97;
			alkuNumero =  syote[2] - 49;
			loppuKirjain = syote[4] - 97;
			loppuNumero = syote[5] - 49;

			break;
		}
		// Sotilassiirto
		else if (syote.length() == 5 &&
			(syote[0] > 96 && syote[0] < 105) &&
			(syote[3] > 96 && syote[3] < 105) &&
			(syote[1] > 48 && syote[1] < 57) &&
			(syote[4] > 48 && syote[4] < 57))
		{
			alkuKirjain = syote[0] - 97;
			alkuNumero = 7 - (syote[1] - 49);
			loppuKirjain = syote[3] - 97;
			loppuNumero = 7 - (syote[4] - 49);

			if (loppuNumero == 0 || loppuNumero == 7)
			{
				// Sotilas on päässyt toiseen päähän. Korotetaan!
			}
			
			break;
		}
		// Lyhyt linna
		else if (syote.length() == 3 && syote[0] == 48 && syote[2] == 48)
		{
			Siirto lyhytLinna(true, false);
			return lyhytLinna;
		}
		// Pitkä linna
		else if (syote.length() == 5 && syote[0] == 48 && syote[2] == 48 && syote[4] == 48)
		{
			Siirto pitkaLinna(false, true);
			return pitkaLinna;
		}
		else 
		{
			wcout << "Väärä syöte! Kokeile uudelleen." << endl;
		}
	}

	Ruutu alkuruutu(alkuKirjain, alkuNumero);
	Ruutu loppuruutu(loppuKirjain, loppuNumero);
	
	Siirto siirto(alkuruutu, loppuruutu);
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
