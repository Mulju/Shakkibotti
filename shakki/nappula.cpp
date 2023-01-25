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
				
				if (aR - j < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}

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
			}
			break;

		case 1:
			// Oikealle
			for (int j = 1; j < 8; j++)
			{
				if (aS + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
				
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
			}
			break;

		case 2:
			// Alasp‰in
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua

				if (aR + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}

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

			}
			break;
		case 3:
			// Vasemmalle
			for (int j = 1; j < 8; j++)
			{
				if (aS - j < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
				
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

			}
			break;
		default:
			break;
		}
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aS = ruutu->getSarake();
	int aR = ruutu->getRivi();

	for (int i = 0; i < 8; i++)
	{
		// for looppi 1-8, koska ratsulla on 8 vapausastetta
		switch (i)
		{
			// Switchi, jolla k‰yd‰‰n kaikki vapausasteet erikseen
		case 0:
			// Ylˆsp‰in oikealle
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua


				if (!(asema->_lauta[aR - 2+j][aS + j] == NULL))
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
			// Oikealle vasen
			for (int j = 1; j < 8; j++)
			{
				if (!(asema->_lauta[aR - j][aS + 2+j] == NULL))
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
		case 4:
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
		case 5:
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
		case 6:
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
		case 7:
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

				if (aR - j < 0 || aS + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}

				if (asema->_lauta[aR - j][aS + j] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR - j][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR - j);
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

			}
			break;

		case 1:
			// Oikea alas
			for (int j = 1; j < 8; j++)
			{
				if (aR + j > 7 || aS + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
				
				if (!(asema->_lauta[aR + j][aS + j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR + j][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR + j);
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
					Ruutu loppuRuutu(aS + j, aR + j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

			}
			break;

		case 2:
			// Vasen alas
			for (int j = 1; j < 8; j++)
			{
				// for looppi alkaa 1:st‰, koska ei oteta samaa ruutua huomioon miss‰ jo ollaan
				// for looppi 1-8, koska laudassa on maksimissaan 8 ruutua

				if (aR + j > 7 || aS - j < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}

				if (!(asema->_lauta[aR + j][aS - j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR + j][aS - j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS - j, aR + j);
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
					Ruutu loppuRuutu(aS - j, aR + j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

			}
			break;
		case 3:
			// Vasen ylˆs
			for (int j = 1; j < 8; j++)
			{
				if (aR - j < 0 || aS - j < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					break;
				}
				
				if (!(asema->_lauta[aR - j][aS - j] == NULL))
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR - j][aS - j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS - j, aR - j);
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
					Ruutu loppuRuutu(aS - j, aR - j);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
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
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett‰ kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l‰hetill‰,
	oman nappulan p‰‰lle ei voi menn‰ ja vastustajan nappulan voi syˆd‰.

	Kaikki muu kuninkaaseen liittyv‰ tarkistus tehd‰‰n eri paikassa*/
	int aS = ruutu->getSarake();
	int aR = ruutu->getRivi();

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			// Ylˆsp‰in, sek‰ ylˆs viistoon
			for (int j = -1; j < 2; j++)
			{
				if (aR - 1 < 0 || aS + j < 0 || aS + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}
				
				if (asema->_lauta[aR - 1][aS + j] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR - 1][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR - 1);
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
					Ruutu loppuRuutu(aS + j, aR - 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

			}

			break;

		case 1:
			// Oikealle
			
			if (aS + 1 > 7)
			{
				// Jos menn‰‰n ylilaudan niin ei tehd‰ mit‰‰n
			}
			else
			{
				if (asema->_lauta[aR][aS + 1] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS + 1]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + 1, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + 1, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}
			}

			break;

		case 2:
			// Alasp‰in ja alas viistoon
			for (int j = -1; j < 2; j++)
			{
				if (aR + 1 > 7 || aS + j < 0 || aS + j > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}

				if (asema->_lauta[aR + 1][aS + j] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR + 1][aS + j]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS + j, aR + 1);
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
					Ruutu loppuRuutu(aS + j, aR + 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}

			}

			break;

		case 3:
			// Vasemmalle

			if (aS - 1 < 0)
			{
				// Jos menn‰‰n ylilaudan niin ei tehd‰ mit‰‰n
			}
			else
			{
				if (asema->_lauta[aR][aS - 1] != NULL)
				{
					// Jos vastaan tulee ruutu, jossa on nappula
					if (vari != asema->_lauta[aR][aS - 1]->getVari())
					{
						// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
						// Laillinen siirto on nappulan p‰‰lle
						Ruutu loppuRuutu(aS - 1, aR);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS - 1, aR);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
				}
			}

			break;

		default:
			break;
		}
	}
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
