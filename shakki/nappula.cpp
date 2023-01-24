#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


// Funktiot
void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aS = ruutu->getSarake();
	int aR = ruutu->getRivi();

	for(int i = 0; i < 4; i++)
	{
		// for looppi 1-4, koska tornilla on nelj� vapausastetta
		switch (i)
		{
			// Switchi, jolla k�yd��n kaikki vapausasteet erikseen
		case 0:
			// Yl�sp�in
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st�, koska ei oteta samaa ruutua huomioon miss� jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua
				
				if (aR + j == 7)
				{
					// Jos menn��n ylilaudan niin poistutaan loopista
					break;
				}

				if (!(asema->_lauta[aR + j][aS] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula

				}
			}
			break;
		case 1:
			// Oikealle
			for (int j = 1; j < 8; j++)
			{
				

			}
			break;
		case 2:
			// Alasp�in
			for (int j = 1; j < 8; j++)
			{
				

			}
			break;
		case 3:
			// Vasemmalle
			for (int j = 1; j < 8; j++)
			{
				

			}
			break;
		default:
			break;
		}
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
