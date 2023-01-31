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
	// T�ll� shakkinappulat toimii
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == 0)
			{
				// Laittaa numeron laudan vasempaan reunaan valkoisella v�rill�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8 - i << "  ";
			}
			
			if ((i % 2 == 0 &&
				(j % 2) - 1 == 0) ||
				((i % 2) - 1 == 0 &&
				 j % 2 == 0))
			{
				// Tuottaa parillisen rivin kuvioinnin laudalle vihre�ll� v�rill�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0x0030);
			}
			else
			{
				// Resettaa v�rin valkoiseksi
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}

			if (_asema->_lauta[i][j] == NULL)
			{
				// Tulostaa v�lin nappuloiden v�liin
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

void Kayttoliittyma::piirraLauta(list<Siirto> &lista, int size)
{
	bool aputaulukko[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			aputaulukko[i][j] = false;
		}
	}

	for (int i = 0; i < size; i++)
	{
		auto eka = lista.begin();
		advance(eka, i);
		Ruutu loppuruutu = eka->getLoppuruutu();
		if (!aputaulukko[loppuruutu.getRivi()][loppuruutu.getSarake()])
		{
			aputaulukko[loppuruutu.getRivi()][loppuruutu.getSarake()] = true;
		}
	}
	
	// T�ll� shakkinappulat toimii
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			
			if (j == 0)
			{
				// Laittaa numeron laudan vasempaan reunaan valkoisella v�rill�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8 - i << "  ";
			}

			if (aputaulukko[i][j])
			{
				// Tuottaa lailliset siirrot laudalle punaisella v�rill�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED);
			}
			else
			{
				if ((i % 2 == 0 &&
					(j % 2) - 1 == 0) ||
					((i % 2) - 1 == 0 &&
						j % 2 == 0))
				{
					// Tuottaa parillisen rivin kuvioinnin laudalle vihre�ll� v�rill�
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0x0030);
				}
				else
				{
					// Resettaa v�rin valkoiseksi
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
			}

			if (_asema->_lauta[i][j] == NULL)
			{
				// Tulostaa v�lin nappuloiden v�liin
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
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto(list<Siirto>& lista, int size)
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
			(syote[0] == 75 || syote[0] == 68 || syote[0] == 76 || syote[0] == 82 || syote[0] == 84) &&
			(syote[1] > 96 && syote[1] < 105) &&
			(syote[4] > 96 && syote[4] < 105) &&
			(syote[2] > 48 && syote[2] < 57) &&
			(syote[5] > 48 && syote[5] < 57))
		{
			bool validoitu = false;

			switch (syote[0])
			{
				case 84: // Tornin tarkistus
					if ((_asema->getSiirtovuoro() == 0 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == VT) ||
						(_asema->getSiirtovuoro() == 1 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == MT))
					{
						// Torni on alkuruudussa, haetaan tornin lailliset siirrot ja tarkistetaan
						for (int i = 0; i < size; i++)
						{
							auto siirto = lista.begin();
							advance(siirto, i);
							Ruutu alkuruutu = siirto->getAlkuruutu();
							// Haetaan saman alkuruudun lailliset siirrot
							if (alkuruutu.getRivi() == syote[2] - 49 && alkuruutu.getSarake() == syote[1] - 97) {
								Ruutu loppuruutu = siirto->getLoppuruutu();
								int rivi = loppuruutu.getRivi();
								int sarake = loppuruutu.getSarake();
								// Tarkistetaan, onko loppuruutu laillinen siirto kyseiselle alkuruudulle
								if (syote[2] - 49 == rivi && syote[1] - 97 == sarake)
								{
									alkuKirjain = syote[1] - 97;
									alkuNumero = syote[2] - 49;
									loppuKirjain = syote[4] - 97;
									loppuNumero = syote[5] - 49;
									validoitu = true;
								}
							}
						}
					}
					break;

				case 82: // Ratsun tarkistus
					if ((_asema->getSiirtovuoro() == 0 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == VR) ||
						(_asema->getSiirtovuoro() == 1 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == MR))
					{
						// Ratsu on alkuruudussa, haetaan ratsun lailliset siirrot ja tarkistetaan
						for (int i = 0; i < size; i++)
						{
							auto siirto = lista.begin();
							advance(siirto, i);
							Ruutu alkuruutu = siirto->getAlkuruutu();
							// Haetaan saman alkuruudun lailliset siirrot
							if (alkuruutu.getRivi() == syote[2] - 49 && alkuruutu.getSarake() == syote[1] - 97) {
								Ruutu loppuruutu = siirto->getLoppuruutu();
								int rivi = loppuruutu.getRivi();
								int sarake = loppuruutu.getSarake();
								// Tarkistetaan, onko loppuruutu laillinen siirto kyseiselle alkuruudulle
								if (syote[2] - 49 == rivi && syote[1] - 97 == sarake)
								{
									alkuKirjain = syote[1] - 97;
									alkuNumero = syote[2] - 49;
									loppuKirjain = syote[4] - 97;
									loppuNumero = syote[5] - 49;
									validoitu = true;
								}
							}
						}
					}
					break;

				case 76: // L�hetin tarkistus
					if ((_asema->getSiirtovuoro() == 0 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == VL) ||
						(_asema->getSiirtovuoro() == 1 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == ML))
					{
						// L�hetti on alkuruudussa
						alkuKirjain = syote[1] - 97;
						alkuNumero = syote[2] - 49;
						loppuKirjain = syote[4] - 97;
						loppuNumero = syote[5] - 49;
					}
					break;

				case 68: // Daamin tarkistus
					if ((_asema->getSiirtovuoro() == 0 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == VD) ||
						(_asema->getSiirtovuoro() == 1 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == MD))
					{
						// Daami on alkuruudussa
						alkuKirjain = syote[1] - 97;
						alkuNumero = syote[2] - 49;
						loppuKirjain = syote[4] - 97;
						loppuNumero = syote[5] - 49;
					}
					break;

				case 75: // Kuninkaan tarkistus
					if ((_asema->getSiirtovuoro() == 0 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == VK) ||
						(_asema->getSiirtovuoro() == 1 && _asema->_lauta[syote[2] - 49][syote[1] - 97]->getKoodi() == MK))
					{
						// Kuningas on alkuruudussa
						alkuKirjain = syote[1] - 97;
						alkuNumero = syote[2] - 49;
						loppuKirjain = syote[4] - 97;
						loppuNumero = syote[5] - 49;
					}
					break;
				default:
					break;
			}

			if (validoitu)
			{
				break;
			}
			else
			{
				wcout << "Laiton siirto! Kokeile uudelleen." << endl;
			}
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
				// Sotilas on p��ssyt toiseen p��h�n. Korotetaan!
			}
			
			break;
		}
		// Lyhyt linna
		else if (syote.length() == 3 && syote[0] == 48 && syote[2] == 48)
		{
			Siirto lyhytLinna(true, false);
			return lyhytLinna;
		}
		// Pitk� linna
		else if (syote.length() == 5 && syote[0] == 48 && syote[2] == 48 && syote[4] == 48)
		{
			Siirto pitkaLinna(false, true);
			return pitkaLinna;
		}
		else 
		{
			wcout << "Laiton siirto! Kokeile uudelleen." << endl;
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
