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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
			
			if (aR - 2 < 0 || aS + 1 > 7)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}


			if (!(asema->_lauta[aR - 2][aS + 1] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR - 2][aS + 1]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS + 1, aR - 2);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS + 1, aR - 2);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}
		
			break;

		case 1:
			// Oikealle ylˆs

			if (aS + 2 > 7 || aR - 1 < 0)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR - 1][aS + 2] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR - 1][aS + 2]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS + 2, aR - 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS + 2, aR - 1);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}

				
			
			break;

		case 2:
			// Oikealle alas
							
			if (aS + 2 > 7 || aR + 1 > 7)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}

			if (!(asema->_lauta[aR + 1][aS + 2] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR + 1][aS + 2]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS + 2, aR + 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}
				
			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS + 2, aR + 1);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}

				
			
			break;
		case 3:
			// Alas oikealle

			if (aR + 2 > 7 || aS + 1 > 7)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR + 2][aS + 1] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR + 2][aS + 1]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS + 1, aR + 2);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS + 1, aR + 2);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}
			break;

		case 4:
			// Alas vasen

			if (aR + 2 > 7 || aS - 1 < 0)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR + 2][aS - 1] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR + 2][aS - 1]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS - 1, aR + 2);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS - 1, aR + 2);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}
			break;

		case 5:
			// Vasemmalle alas

			if (aS - 2 < 0 || aR + 1 > 7)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR + 1][aS - 2] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR + 1][aS - 2]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS - 2, aR + 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS - 2, aR + 1);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}
			break;

		case 6:
			// Vasemmalle ylˆs

			if (aS - 2 < 0 || aR - 1 < 0)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR - 1][aS - 2] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR - 1][aS - 2]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS - 2, aR - 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}

			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS - 2, aR - 1);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
			}

				
			
			break;
		case 7:
			// ylˆs vasen

			if (aR - 2 < 0 || aS - 1 < 0)
			{
				// Jos menn‰‰n ylilaudan niin poistutaan loopista
				continue;
			}
			
			if (!(asema->_lauta[aR - 2][aS - 1] == NULL))
			{
				// Jos vastaan tulee ruutu, jossa on nappula
				if (vari != asema->_lauta[aR - 2][aS - 1]->getVari())
				{
					// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
					// Laillinen siirto on nappulan p‰‰lle
					Ruutu loppuRuutu(aS - 1, aR - 2);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
				}
				else
				{
					// Nappula tuli vastaan, mutta se on samaa v‰ri‰
				}
			}
			else
			{
				// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
				Ruutu loppuRuutu(aS - 1, aR - 2);
				Siirto uusiSiirto(*ruutu, loppuRuutu);
				lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + j, aR - 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
					}
					else
					{
						// Nappula tuli vastaan, mutta se on samaa v‰ri‰
					}
				}
				else
				{
					// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
					Ruutu loppuRuutu(aS + j, aR + 1);
					Siirto uusiSiirto(*ruutu, loppuRuutu);
					lista.push_back(uusiSiirto);
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
						lista.push_back(uusiSiirto);
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
					lista.push_back(uusiSiirto);
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

	int aS = ruutu->getSarake();
	int aR = ruutu->getRivi();
	// Ohestalyˆnti
    
	if (vari == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
				// Normaalisiirto
			case 0:
				// Ylˆsp‰in

				if (aR - 1 < 0)
				{
					// Jos menn‰‰n ylilaudan niin ei tehd‰ mit‰‰n
					continue;
				}
				else
				{
					if (asema->_lauta[aR - 1][aS] != NULL)
					{
						// Vastaan tuli ruutu jossa on nappula, ei voida liikkua
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
						Ruutu loppuRuutu(aS, aR - 1);
						Siirto uusiSiirto(*ruutu, loppuRuutu);

						if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
						{
							// Sotilas olisi korottumassa
							lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
						}
						else
						{
							lista.push_back(uusiSiirto);
						}
					}
				}
				break;
			case 1:
				//ylˆs oikealle syˆnti
				if (aR - 1 < 0 || aS + 1 > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}

				else
				{
					if (asema->_lauta[aR - 1][aS + 1] != NULL)
					{
						// Jos vastaan tulee ruutu, jossa on nappula
						if (vari != asema->_lauta[aR - 1][aS + 1]->getVari())
						{
							// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
							Ruutu loppuRuutu(aS + 1, aR - 1);
							Siirto uusiSiirto(*ruutu, loppuRuutu);
							
							if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
							{
								// Sotilas olisi korottumassa
								lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
							}
							else
							{
								lista.push_back(uusiSiirto);
							}

						}
						else
						{
							// Nappula tuli vastaan, mutta se on samaa v‰ri‰
						}
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n

					}
				}
				break;

			case 2:
				//ylˆs vasemmalle syˆnti
				if (aR - 1 < 0 || aS - 1 < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}

				else
				{
					if (asema->_lauta[aR - 1][aS - 1] != NULL)
					{
						// Jos vastaan tulee ruutu, jossa on nappula
						if (vari != asema->_lauta[aR - 1][aS - 1]->getVari())
						{
							// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
							Ruutu loppuRuutu(aS - 1, aR - 1);
							Siirto uusiSiirto(*ruutu, loppuRuutu);
							
							if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
							{
								// Sotilas olisi korottumassa
								lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
							}
							else
							{
								lista.push_back(uusiSiirto);
							}

						}
						else
						{
							// Nappula tuli vastaan, mutta se on samaa v‰ri‰
						}
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n

					}
				}
				break;

			default:
				break;
			}
		
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
				// Normaalisiirto
			case 0:
				// Alasp‰in

				if (aR + 1 > 7)
				{
					// Jos menn‰‰n ylilaudan niin ei tehd‰ mit‰‰n
					continue;
				}
				else
				{
					if (asema->_lauta[aR + 1][aS] != NULL)
					{
						// Vastaan tuli ruutu jossa on nappula, ei voida liikkua
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n, lis‰t‰‰n se laillisten siirtojen listaan
						Ruutu loppuRuutu(aS, aR + 1);
						Siirto uusiSiirto(*ruutu, loppuRuutu);
						
						if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
						{
							// Sotilas olisi korottumassa
							lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
						}
						else
						{
							lista.push_back(uusiSiirto);
						}
					}
				}
				break;
			case 1:
				//Alas oikealle syˆnti
				if (aR + 1 > 7 || aS + 1 > 7)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}

				else
				{
					if (asema->_lauta[aR + 1][aS + 1] != NULL)
					{
						// Jos vastaan tulee ruutu, jossa on nappula
						if (vari != asema->_lauta[aR + 1][aS + 1]->getVari())
						{
							// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
							Ruutu loppuRuutu(aS + 1, aR + 1);
							Siirto uusiSiirto(*ruutu, loppuRuutu);

							if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
							{
								// Sotilas olisi korottumassa
								lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
							}
							else
							{
								lista.push_back(uusiSiirto);
							}

						}
						else
						{
							// Nappula tuli vastaan, mutta se on samaa v‰ri‰
						}
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n

					}
				}
				break;

			case 2:
				//Alas vasemmalle syˆnti
				if (aR + 1 > 7 || aS - 1 < 0)
				{
					// Jos menn‰‰n ylilaudan niin poistutaan loopista
					continue;
				}

				else
				{
					if (asema->_lauta[aR + 1][aS - 1] != NULL)
					{
						// Jos vastaan tulee ruutu, jossa on nappula
						if (vari != asema->_lauta[aR + 1][aS - 1]->getVari())
						{
							// Nappula tuli vastaan ja se on eri v‰ri‰ kuin liikkuva nappula
							Ruutu loppuRuutu(aS - 1, aR + 1);
							Siirto uusiSiirto(*ruutu, loppuRuutu);

							if (loppuRuutu.getRivi() == 7 || loppuRuutu.getRivi() == 0)
							{
								// Sotilas olisi korottumassa
								lisaaSotilaanKorotukset(&uusiSiirto, lista, asema);
							}
							else
							{
								lista.push_back(uusiSiirto);
							}

						}
						else
						{
							// Nappula tuli vastaan, mutta se on samaa v‰ri‰
						}
					}
					else
					{
						// Ruudussa ei ollut mit‰‰n

					}
				}
				break;

			default:
				break;
			}
		}
	}
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) 
{
	Siirto korotus = *siirto;
	//Valkea korottaa
	if (korotus.getLoppuruutu().getRivi() == 0)
	{
		korotus._miksikorotetaan = asema->vd;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->vt;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->vl;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->vr;
		lista.push_back(korotus);
	}

	// Musta korottaa
	if (korotus.getLoppuruutu().getRivi() == 7)
	{
		korotus._miksikorotetaan = asema->md;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->mt;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->ml;
		lista.push_back(korotus);

		korotus._miksikorotetaan = asema->mr;
		lista.push_back(korotus);
	}
}
