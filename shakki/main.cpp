#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"
#include <vector>
#include "Ajastin.h"
#include <unordered_map>
#include "vakiot.h"

using namespace std;
using namespace std::chrono;
using namespace vakiot;

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	system("cls");
	
	vector<Siirto> siirrot;
	siirrot.reserve(200);

	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		siirrot.clear();
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(siirrot);
		Kayttoliittyma::getInstance()->piirraLauta(siirrot);
		wcout << "\n";
		if (siirrot.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			
			// Ajastin debuggaukseen
			wstring nimi = L"Koneen siirtoaika";
			Ajastin ajastin(nimi);

			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.alphaBetaMaxi(-100000, 100000, PELISYVYYS);
			}
			else {
				paluu = asema.alphaBetaMini(-100000, 100000, PELISYVYYS);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto(siirrot, siirrot.size());
		}
		Kayttoliittyma::getInstance()->tulostaKoneenSiirto(siirto, peli);
		asema.paivitaAsema(&siirto);
	}

	return 0;
}
