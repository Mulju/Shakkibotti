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

using namespace std;
using namespace std::chrono;

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	/*//Testausta varten
	std::list<Siirto> lista;
	Kayttoliittyma::getInstance()->piirraLauta();
	
	while (true)
	{
		lista.clear();
		asema.annaLaillisetSiirrot(lista);
		Kayttoliittyma::getInstance()->piirraLauta(lista);
		Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(lista, lista.size());
		asema.paivitaAsema(&siirto);
	}
	Testikoodi loppuu*/

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	system("cls");
	
	vector<Siirto> siirrot;
	siirrot.reserve(200);
	
	// Killermove hashmap
	unordered_map<int, vector<Siirto>> umap;

	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		siirrot.clear();
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(siirrot);
		if (siirrot.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Kayttoliittyma::getInstance()->piirraLauta(siirrot);
		wcout << "\n";
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			
			// Ajastin debuggaukseen
			wstring nimi = L"Koneen siirto";
			Ajastin ajastin(nimi);
			
			// Tyhjennetään killer movet
			umap.clear();

			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.alphaBetaMaxi(-100000, 100000, 4, umap);
			}
			else {
				paluu = asema.alphaBetaMini(-100000, 100000, 4, umap);
			}
			siirto = paluu._parasSiirto;

			/*
			// Random siirto testausta varten
			int randomIndex = rand() % lista.size();
			auto siirtoTemp = lista.begin();
			advance(siirtoTemp, randomIndex);
			siirto = *siirtoTemp;
			*/
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto(siirrot, siirrot.size());
		}
		asema.paivitaAsema(&siirto);
	}

	
	return 0;
}
