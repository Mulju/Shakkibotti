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
		// for looppi 1-4, koska tornilla on nelj‰ vapausastetta
		switch (i)
		{
			// Switchi, jolla k‰yd‰‰n kaikki vapausasteet erikseen
		case 0:
			// Ylˆsp‰in
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua
				

				if (!(asema->_lauta[aR - j][aS] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR - j][aS]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS, aR - j);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS, aR - j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}
				
				if (aR - j == 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;

		case 1:
			// Oikealle
			for (int j = 1; j < 8; j++)
			{
				if (!(asema->_lauta[aR][aS + j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + j, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aS + j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;

		case 2:
			// Alasp‰in
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua


				if (!(asema->_lauta[aR + j][aS] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR + j][aS]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS, aR + j);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS, aR + j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aR + j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;
		case 3:
			// Vasemmalle
			for (int j = 1; j < 8; j++)
			{
				if (!(asema->_lauta[aR][aS - j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS - j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS - j, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS - j, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aS - j == 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
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
	int aS = ruutu->getSarake();
	int aR = ruutu->getRivi();

	for (int i = 0; i < 4; i++)
	{
		// for looppi 1-4, koska tornilla on nelj‰ vapausastetta
		switch (i)
		{
			// Switchi, jolla k‰yd‰‰n kaikki vapausasteet erikseen
		case 0:
			// Oikea ylˆs
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua


				if (asema->_lauta[aR - j][aS + j] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR - j][aS]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS, aR - j);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + j, aR - j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aR - j == 7 || aS + j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;

		case 1:
			// Oikealle
			for (int j = 1; j < 8; j++)
			{
				if (!(asema->_lauta[aR][aS + j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + j, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aS + j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;

		case 2:
			// Alasp‰in
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua


				if (!(asema->_lauta[aR + j][aS] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR + j][aS]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS, aR + j);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS, aR + j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aR + j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;
		case 3:
			// Vasemmalle
			for (int j = 1; j < 8; j++)
			{
				if (!(asema->_lauta[aR][aS - j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS - j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS - j, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}

					// Poistutaan loopista, koska ei voida jatkaa nappulan yli
					break;
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS - j, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

				if (aS - j == 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett‰ kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l‰hetill‰,
	oman nappulan p‰‰lle ei voi menn‰ ja vastustajan nappulan voi syˆd‰.

	Kaikki muu kuninkaaseen liittyv‰ tarkistus tehd‰‰n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
