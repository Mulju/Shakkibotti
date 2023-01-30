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
	void piirraLauta(std::list<Siirto>& lista, int size);
	Siirto annaVastustajanSiirto();
	int kysyVastustajanVari();

	static Kayttoliittyma* getInstance();

private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).

	Kayttoliittyma() {}
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};
