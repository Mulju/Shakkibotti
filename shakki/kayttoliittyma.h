#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"


// Shakkiohjelman käyttöliittymä, joka osaa visualisoida nykyisen aseman
// ja lukea käyttäjän syöttämät siirrot. Singleton.
class Kayttoliittyma
{
public:

	void aseta_asema(Asema* asema) { this->_asema = asema;  }
	void piirraLauta();
	void piirraLauta(std::vector<Siirto>& lista);
	Siirto annaVastustajanSiirto(std::vector<Siirto>& lista, int size);
	int kysyVastustajanVari();
	void tulostaKoneenSiirto(Siirto& siirto, Peli& peli);

	static Kayttoliittyma* getInstance();

private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).

	Kayttoliittyma() {}
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};
