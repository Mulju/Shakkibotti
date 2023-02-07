#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std; 

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	//Testausta varten
	std::list<Siirto> lista;
	Kayttoliittyma::getInstance()->piirraLauta();
	
	while (true)
	{
		lista.clear();
		asema.annaLaillisetSiirrot(lista);
		Kayttoliittyma::getInstance()->piirraLauta(lista, lista.size());
		Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(lista, lista.size());
		asema.paivitaAsema(&siirto);
	}
	//Testikoodi loppuu*/

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	//std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		lista.clear();
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Kayttoliittyma::getInstance()->piirraLauta(lista, lista.size());
		wcout << "\n";
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			/*MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(2);
			}
			else {
				paluu = asema.mini(2);
			}
			siirto = paluu._parasSiirto;*/

			int randomIndex = rand() % lista.size();
			auto siirtoTemp = lista.begin();
			advance(siirtoTemp, randomIndex);
			siirto = *siirtoTemp;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto(lista, lista.size());
		}
		asema.paivitaAsema(&siirto);
	}

	
	return 0;
}
