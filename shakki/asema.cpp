#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = NULL;
		}
	}

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille

	_lauta[1][0] = ms;
	_lauta[1][1] = ms;
	_lauta[1][2] = ms;
	_lauta[1][3] = ms;
	_lauta[1][4] = ms;
	_lauta[1][5] = ms;
	_lauta[1][6] = ms;
	_lauta[1][7] = ms;

	_lauta[6][0] = vs;
	_lauta[6][1] = vs;
	_lauta[6][2] = vs;
	_lauta[6][3] = vs;
	_lauta[6][4] = vs;
	_lauta[6][5] = vs;
	_lauta[6][6] = vs;
	_lauta[6][7] = vs;

	_lauta[0][0] = mt;
	_lauta[0][1] = mr;
	_lauta[0][2] = ml;
	_lauta[0][3] = md;
	_lauta[0][4] = mk;
	_lauta[0][5] = ml;
	_lauta[0][6] = mr;
	_lauta[0][7] = mt;

	_lauta[7][0] = vt;
	_lauta[7][1] = vr;
	_lauta[7][2] = vl;
	_lauta[7][3] = vd;
	_lauta[7][4] = vk;
	_lauta[7][5] = vl;
	_lauta[7][6] = vr;
	_lauta[7][7] = vt;

	_siirtovuoro = 0;

	// Liikkumisflagit asetetaan falseksi
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
}


void Asema::paivitaAsema(Siirto *siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.
	//kaksoisaskelSarakkeella = -1;


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (_siirtovuoro == 0 )
		{
			_lauta[7][4] = NULL; // Kuninkaan paikalle tyhj‰
			_lauta[7][6] = vk; // Kuningas uudelle paikalle
			_lauta[7][7] = NULL; // Tornin paikalle tyhj‰
			_lauta[7][5] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1 )
		{
			_lauta[0][4] = NULL; // Kuninkaan paikalle tyhj‰
			_lauta[0][6] = mk; // Kuningas uudelle paikalle
			_lauta[0][7] = NULL; // Tornin paikalle tyhj‰
			_lauta[0][5] = mt; // Torni uudelle paikalle
		}
	}
	else if (siirto->onkoPitkaLinna()) // onko pitk‰ linna
	{
		if (_siirtovuoro == 0)
		{
			_lauta[7][4] = NULL; // Kuninkaan paikalle tyhj‰
			_lauta[7][2] = vk; // Kuningas uudelle paikalle
			_lauta[7][0] = NULL; // Tornin paikalle tyhj‰
			_lauta[7][3] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1 )
		{
			_lauta[0][4] = NULL; // Kuninkaan paikalle tyhj‰
			_lauta[0][2] = mk; // Kuningas uudelle paikalle
			_lauta[0][0] = NULL; // Tornin paikalle tyhj‰
			_lauta[0][3] = mt; // Torni uudelle paikalle
		}
	}
	else // Kaikki muut siirrot
	{
		//Ottaa siirron alkuruudussa olleen nappulan talteen
		Nappula* nappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		
		// Tarkistetaan, onko ohestalyˆnti. Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if (nappula == ms && siirto->getAlkuruutu().getRivi() == 4 && siirto->getLoppuruutu().getSarake() == kaksoisaskelSarakkeella)
		{
			_lauta[siirto->getLoppuruutu().getRivi() - 1][siirto->getLoppuruutu().getSarake()] = NULL;
		}
		if (nappula == vs && siirto->getAlkuruutu().getRivi() == 3 && siirto->getLoppuruutu().getSarake() == kaksoisaskelSarakkeella)
		{
			_lauta[siirto->getLoppuruutu().getRivi() + 1][siirto->getLoppuruutu().getSarake()] = NULL;
		}
		
		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if (nappula == ms && siirto->getLoppuruutu().getRivi() == 3 && siirto->getAlkuruutu().getRivi() == 1)
		{
			kaksoisaskelSarakkeella = siirto->getLoppuruutu().getSarake();
		}
		else if (nappula == vs && siirto->getLoppuruutu().getRivi() == 4 && siirto->getAlkuruutu().getRivi() == 6)
		{
			kaksoisaskelSarakkeella = siirto->getLoppuruutu().getSarake();
		}
		else
		{
			kaksoisaskelSarakkeella = -1;
		}

		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		
		// Maikan ylempi kommentti on h‰mment‰v‰. Luullakseni t‰m‰ korottaa sotilaan oikein
		if ((siirto->getLoppuruutu().getRivi() == 7 || siirto->getLoppuruutu().getRivi() == 0) &&
			(nappula == ms || nappula == vs))
		{
			// Siirron loppuruutu on laudan p‰‰ty, sek‰ nappula on sotilas. Siirrolla on korotus arvo
			// Asetetaan nappula osoitin osoittamaan korotusarvon omaiseen nappulaan
			nappula = siirto->_miksikorotetaan;
			// P‰ivitet‰‰n laudalle oikean tyyppinen nappula
			_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		}

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL;

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappula == mk) {
			_onkoMustaKuningasLiikkunut = true;
		}
		if (nappula == vk) {
			_onkoValkeaKuningasLiikkunut = true;
		}

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if (nappula == vt && _lauta[7][0]) {
			_onkoValkeaDTliikkunut = true;
		}
		if (nappula == vt && _lauta[7][7]) {
			_onkoValkeaKTliikkunut = true;
		}
		if (nappula == mt && _lauta[0][7]) {
			_onkoMustaDTliikkunut = true;
		}
		if (nappula == mt && _lauta[0][0]) {
			_onkoMustaKTliikkunut = true;
		}

	}

	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0)
	{
		_siirtovuoro = 1;
	}
	else
	{
		_siirtovuoro = 0;
	}

}


int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return _onkoMustaKTliikkunut;
}






/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi() 
{
	double laudanArvo = 0;
	// Heinin kommentti: kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

	//1. Nappuloiden arvo
	laudanArvo += laskeNappuloidenArvo(getSiirtovuoro());
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	laudanArvo += 0.01 * nappuloitaKeskella(getSiirtovuoro());

	// 4. Arvosta linjoja
	
	return laudanArvo;
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	double nappuloidenArvo = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Loopataan koko lauta
			
			if (_lauta[i][j] != nullptr)
			{
				// Jos ruudussa on nappula..
				switch (_lauta[i][j]->getKoodi())
				{
				case 0:
					// VT
					nappuloidenArvo += 5;
					break;
				case 1:
					// VR
					nappuloidenArvo += 3;
					break;
				case 2:
					// VL
					nappuloidenArvo += 3.25;
					break;
				case 3:
					// VD
					nappuloidenArvo += 9;
					break;
				case 4:
					// VK
					nappuloidenArvo += 0;
					break;
				case 5:
					// VS
					nappuloidenArvo += 1;
					break;
				case 6:
					// MT
					nappuloidenArvo -= 5;
					break;
				case 7:
					// MR
					nappuloidenArvo -= 3;
					break;
				case 8:
					// ML
					nappuloidenArvo -= 3.25;
					break;
				case 9:
					// MD
					nappuloidenArvo -= 9;
					break;
				case 10:
					// MK
					nappuloidenArvo -= 0;
					break;
				case 11:
					// MS
					nappuloidenArvo -= 1;
					break;
				default:
					break;
				}
			}
		}
	}

	return nappuloidenArvo;
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	int keskipelisotilasV[64] = {
	  0,   0,   0,   0,   0,   0,  0,   0,
	 98, 134,  61,  95,  68, 126, 34, -11,
	 -6,   7,  26,  31,  65,  56, 25, -20,
	-14,  13,   6,  21,  23,  12, 17, -23,
	-27,  -2,  -5,  12,  17,   6, 10, -25,
	-26,  -4,  -4, -10,   3,   3, 33, -12,
	-35,  -1, -20, -23, -15,  24, 38, -22,
	  0,   0,   0,   0,   0,   0,  0,   0,
	};


	int loppupelisotilasV[64] = {
		  0,   0,   0,   0,   0,   0,   0,   0,
		178, 173, 158, 134, 147, 132, 165, 187,
		 94, 100,  85,  67,  56,  53,  82,  84,
		 32,  24,  13,   5,  -2,   4,  17,  17,
		 13,   9,  -3,  -7,  -7,  -8,   3,  -1,
		  4,   7,  -6,   1,   0,  -5,  -1,  -8,
		 13,   8,   8,  10,  13,   0,   2,  -7,
		  0,   0,   0,   0,   0,   0,   0,   0,
	};

	int keskipeliratsuV[64] = {
		-167, -89, -34, -49,  61, -97, -15, -107,
		 -73, -41,  72,  36,  23,  62,   7,  -17,
		 -47,  60,  37,  65,  84, 129,  73,   44,
		  -9,  17,  19,  53,  37,  69,  18,   22,
		 -13,   4,  16,  13,  28,  19,  21,   -8,
		 -23,  -9,  12,  10,  19,  17,  25,  -16,
		 -29, -53, -12,  -3,  -1,  18, -14,  -19,
		-105, -21, -58, -33, -17, -28, -19,  -23,
	};

	int loppupeliratsuV[64] = {
		-58, -38, -13, -28, -31, -27, -63, -99,
		-25,  -8, -25,  -2,  -9, -25, -24, -52,
		-24, -20,  10,   9,  -1,  -9, -19, -41,
		-17,   3,  22,  22,  22,  11,   8, -18,
		-18,  -6,  16,  25,  16,  17,   4, -18,
		-23,  -3,  -1,  15,  10,  -3, -20, -22,
		-42, -20, -10,  -5,  -2, -20, -23, -44,
		-29, -51, -23, -15, -22, -18, -50, -64,
	};

	int keskipelil‰hettiV[64] = {
		-29,   4, -82, -37, -25, -42,   7,  -8,
		-26,  16, -18, -13,  30,  59,  18, -47,
		-16,  37,  43,  40,  35,  50,  37,  -2,
		 -4,   5,  19,  50,  37,  37,   7,  -2,
		 -6,  13,  13,  26,  34,  12,  10,   4,
		  0,  15,  15,  15,  14,  27,  18,  10,
		  4,  15,  16,   0,   7,  21,  33,   1,
		-33,  -3, -14, -21, -13, -12, -39, -21,
	};

	int loppupelil‰hettiV[64] = {
		-14, -21, -11,  -8, -7,  -9, -17, -24,
		 -8,  -4,   7, -12, -3, -13,  -4, -14,
		  2,  -8,   0,  -1, -2,   6,   0,   4,
		 -3,   9,  12,   9, 14,  10,   3,   2,
		 -6,   3,  13,  19,  7,  10,  -3,  -9,
		-12,  -3,   8,  10, 13,   3,  -7, -15,
		-14, -18,  -7,  -1,  4,  -9, -15, -27,
		-23,  -9, -23,  -5, -9, -16,  -5, -17,
	};

	int keskipelitorniV[64] = {
		 32,  42,  32,  51, 63,  9,  31,  43,
		 27,  32,  58,  62, 80, 67,  26,  44,
		 -5,  19,  26,  36, 17, 45,  61,  16,
		-24, -11,   7,  26, 24, 35,  -8, -20,
		-36, -26, -12,  -1,  9, -7,   6, -23,
		-45, -25, -16, -17,  3,  0,  -5, -33,
		-44, -16, -20,  -9, -1, 11,  -6, -71,
		-19, -13,   1,  17, 16,  7, -37, -26,
	};

	int loppupelitorniV[64] = {
		13, 10, 18, 15, 12,  12,   8,   5,
		11, 13, 13, 11, -3,   3,   8,   3,
		 7,  7,  7,  5,  4,  -3,  -5,  -3,
		 4,  3, 13,  1,  2,   1,  -1,   2,
		 3,  5,  8,  4, -5,  -6,  -8, -11,
		-4,  0, -5, -1, -7, -12,  -8, -16,
		-6, -6,  0,  2, -9,  -9, -11,  -3,
		-9,  2,  3, -1, -5, -13,   4, -20,
	};

	int keskipelidaamiV[64] = {
		-28,   0,  29,  12,  59,  44,  43,  45,
		-24, -39,  -5,   1, -16,  57,  28,  54,
		-13, -17,   7,   8,  29,  56,  47,  57,
		-27, -27, -16, -16,  -1,  17,  -2,   1,
		 -9, -26,  -9, -10,  -2,  -4,   3,  -3,
		-14,   2, -11,  -2,  -5,   2,  14,   5,
		-35,  -8,  11,   2,   8,  15,  -3,   1,
		 -1, -18,  -9,  10, -15, -25, -31, -50,
	};

	int loppupelidaamiV[64] = {
		 -9,  22,  22,  27,  27,  19,  10,  20,
		-17,  20,  32,  41,  58,  25,  30,   0,
		-20,   6,   9,  49,  47,  35,  19,   9,
		  3,  22,  24,  45,  57,  40,  57,  36,
		-18,  28,  19,  47,  31,  34,  39,  23,
		-16, -27,  15,   6,   9,  17,  10,   5,
		-22, -23, -30, -16, -16, -23, -36, -32,
		-33, -28, -22, -43,  -5, -32, -20, -41,
	};

	int keskipelikuningasV[64] = {
		-65,  23,  16, -15, -56, -34,   2,  13,
		 29,  -1, -20,  -7,  -8,  -4, -38, -29,
		 -9,  24,   2, -16, -20,   6,  22, -22,
		-17, -20, -12, -27, -30, -25, -14, -36,
		-49,  -1, -27, -39, -46, -44, -33, -51,
		-14, -14, -22, -46, -44, -30, -15, -27,
		  1,   7,  -8, -64, -43, -16,   9,   8,
		-15,  36,  12, -54,   8, -28,  24,  14,
	};

	int loppupelikuningasV[64] = {
		-74, -35, -18, -18, -11,  15,   4, -17,
		-12,  17,  14,  17,  17,  38,  23,  11,
		 10,  17,  23,  15,  20,  45,  44,  13,
		 -8,  22,  24,  27,  26,  33,  26,   3,
		-18,  -4,  21,  24,  27,  23,   9, -11,
		-19,  -3,  11,  21,  23,  16,   7,  -9,
		-27, -11,   4,  13,  14,   4,  -5, -17,
		-53, -34, -21, -11, -28, -14, -24, -43
	};

	
	int keskipelisotilasM[64] = {
	  0,   0,   0,   0,   0,   0,  0,   0,
	-35,  -1, -20, -23, -15,  24, 38, -22,
	-26,  -4,  -4, -10,   3,   3, 33, -12,
	-27,  -2,  -5,  12,  17,   6, 10, -25,
	-14,  13,   6,  21,  23,  12, 17, -23,
	 -6,   7,  26,  31,  65,  56, 25, -20,
	 98, 134,  61,  95,  68, 126, 34, -11,
	  0,   0,   0,   0,   0,   0,  0,   0,
	};


	int loppupelisotilasM[64] = {
		  0,   0,   0,   0,   0,   0,   0,   0,
		 13,   8,   8,  10,  13,   0,   2,  -7,
		  4,   7,  -6,   1,   0,  -5,  -1,  -8,
		 13,   9,  -3,  -7,  -7,  -8,   3,  -1,
		 32,  24,  13,   5,  -2,   4,  17,  17,
		 94, 100,  85,  67,  56,  53,  82,  84,
		178, 173, 158, 134, 147, 132, 165, 187,
		  0,   0,   0,   0,   0,   0,   0,   0,
	};

	int keskipeliratsuM[64] = {
		-105, -21, -58, -33, -17, -28, -19,  -23,
		 -29, -53, -12,  -3,  -1,  18, -14,  -19,
		 -23,  -9,  12,  10,  19,  17,  25,  -16,
		 -13,   4,  16,  13,  28,  19,  21,   -8,
		  -9,  17,  19,  53,  37,  69,  18,   22,
		 -47,  60,  37,  65,  84, 129,  73,   44,
		 -73, -41,  72,  36,  23,  62,   7,  -17,
		-167, -89, -34, -49,  61, -97, -15, -107,
	};

	int loppupeliratsuM[64] = {
		-29, -51, -23, -15, -22, -18, -50, -64,
		-42, -20, -10,  -5,  -2, -20, -23, -44,
		-23,  -3,  -1,  15,  10,  -3, -20, -22,
		-18,  -6,  16,  25,  16,  17,   4, -18,
		-17,   3,  22,  22,  22,  11,   8, -18,
		-24, -20,  10,   9,  -1,  -9, -19, -41,
		-25,  -8, -25,  -2,  -9, -25, -24, -52,
		-58, -38, -13, -28, -31, -27, -63, -99,
	};

	int keskipelil‰hettiM[64] = {
		-33,  -3, -14, -21, -13, -12, -39, -21,
		  4,  15,  16,   0,   7,  21,  33,   1,
		  0,  15,  15,  15,  14,  27,  18,  10,
		 -6,  13,  13,  26,  34,  12,  10,   4,
		 -4,   5,  19,  50,  37,  37,   7,  -2,
		-16,  37,  43,  40,  35,  50,  37,  -2,
		-26,  16, -18, -13,  30,  59,  18, -47,
		-29,   4, -82, -37, -25, -42,   7,  -8,
	};

	int loppupelil‰hettiM[64] = {
		-23,  -9, -23,  -5, -9, -16,  -5, -17,
		-14, -18,  -7,  -1,  4,  -9, -15, -27,
		-12,  -3,   8,  10, 13,   3,  -7, -15,
		 -6,   3,  13,  19,  7,  10,  -3,  -9,
		 -3,   9,  12,   9, 14,  10,   3,   2,
		  2,  -8,   0,  -1, -2,   6,   0,   4,
		 -8,  -4,   7, -12, -3, -13,  -4, -14,
		-14, -21, -11,  -8, -7,  -9, -17, -24,
	};

	int keskipelitorniM[64] = {
		-19, -13,   1,  17, 16,  7, -37, -26,
		-44, -16, -20,  -9, -1, 11,  -6, -71,
		-45, -25, -16, -17,  3,  0,  -5, -33,
		-36, -26, -12,  -1,  9, -7,   6, -23,
		-24, -11,   7,  26, 24, 35,  -8, -20,
		 -5,  19,  26,  36, 17, 45,  61,  16,
		 27,  32,  58,  62, 80, 67,  26,  44,
		 32,  42,  32,  51, 63,  9,  31,  43,
	};

	int loppupelitorniM[64] = {
		-9,  2,  3, -1, -5, -13,   4, -20,
		-6, -6,  0,  2, -9,  -9, -11,  -3,
		-4,  0, -5, -1, -7, -12,  -8, -16,
		 3,  5,  8,  4, -5,  -6,  -8, -11,
		 4,  3, 13,  1,  2,   1,  -1,   2,
		 7,  7,  7,  5,  4,  -3,  -5,  -3,
		11, 13, 13, 11, -3,   3,   8,   3,
		13, 10, 18, 15, 12,  12,   8,   5,
	};

	int keskipelidaamiM[64] = {
		 -1, -18,  -9,  10, -15, -25, -31, -50,
		-35,  -8,  11,   2,   8,  15,  -3,   1,
		-14,   2, -11,  -2,  -5,   2,  14,   5,
		 -9, -26,  -9, -10,  -2,  -4,   3,  -3,
		-27, -27, -16, -16,  -1,  17,  -2,   1,
		-13, -17,   7,   8,  29,  56,  47,  57,
		-24, -39,  -5,   1, -16,  57,  28,  54,
		-28,   0,  29,  12,  59,  44,  43,  45,
	};

	int loppupelidaamiM[64] = {
		-33, -28, -22, -43,  -5, -32, -20, -41,
		-22, -23, -30, -16, -16, -23, -36, -32,
		-16, -27,  15,   6,   9,  17,  10,   5,
		-18,  28,  19,  47,  31,  34,  39,  23,
		  3,  22,  24,  45,  57,  40,  57,  36,
		-20,   6,   9,  49,  47,  35,  19,   9,
		-17,  20,  32,  41,  58,  25,  30,   0,
		 -9,  22,  22,  27,  27,  19,  10,  20,
	};

	int keskipelikuningasM[64] = {
		-15,  36,  12, -54,   8, -28,  24,  14,
		  1,   7,  -8, -64, -43, -16,   9,   8,
		-14, -14, -22, -46, -44, -30, -15, -27,
		-49,  -1, -27, -39, -46, -44, -33, -51,
		-17, -20, -12, -27, -30, -25, -14, -36,
		 -9,  24,   2, -16, -20,   6,  22, -22,
		 29,  -1, -20,  -7,  -8,  -4, -38, -29,
		-65,  23,  16, -15, -56, -34,   2,  13,
	};

	int loppupelikuningasM[64] = {
		-53, -34, -21, -11, -28, -14, -24, -43
		-27, -11,   4,  13,  14,   4,  -5, -17,
		-19,  -3,  11,  21,  23,  16,   7,  -9,
		-18,  -4,  21,  24,  27,  23,   9, -11,
		 -8,  22,  24,  27,  26,  33,  26,   3,
		 10,  17,  23,  15,  20,  45,  44,  13,
		-12,  17,  14,  17,  17,  38,  23,  11,
		-74, -35, -18, -18, -11,  15,   4, -17,
	};



	double summa = 0;

	if (vari == 0) {
		for (int i = 0; i < 64; i++) {
			int ruutu = floor((float)i / 8), sarake = i % 8;
			Nappula* nappula = this->_lauta[ruutu][sarake];

			if (nappula == vs) {
				summa += keskipelisotilasV[i];
			}
			else if (nappula == vr) {
				summa += keskipeliratsuV[i];
			}
			else if (nappula == vl) {
				summa += keskipelil‰hettiV[i];
			}
			else if (nappula == vt) {
				summa += keskipelitorniV[i];
			}			
			else if (nappula == vk) {
				summa += keskipelikuningasV[i];
			}			
			else if (nappula == vd) {
				summa += keskipelidaamiV[i];
			}
		
		
		}

	}
	else 
	{
		for (int i = 0; i < 64; i++) {
			int ruutu = floor((float)i / 8), sarake = i % 8;
			Nappula* nappula = this->_lauta[ruutu][sarake];

			if (nappula == ms) {
				summa += -1 * keskipelisotilasM[i];
			}
			else if (nappula == mr) {
				summa += -1 * keskipeliratsuM[i];
			}
			else if (nappula == ml) {
				summa += -1 * keskipelil‰hettiM[i];
			}
			else if (nappula == mt) {
				summa += -1 * keskipelitorniM[i];
			}			
			else if (nappula == mk) {
				summa += -1 * keskipelikuningasM[i];
			}			
			else if (nappula == md) {
				summa += -1 * keskipelidaamiM[i];
			}
		}

	}
	
	return summa;


	

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::alphaBetaMaxi(int alpha, int beta, int syvyys) 
{
	MinMaxPaluu paluu;
	double laudanArvo = -10000;
	Siirto parasSiirto;
	std::list<Siirto> siirtoLista;
	Asema uusiAsema = *this;

	annaLaillisetSiirrot(siirtoLista);
	Ruutu kuninkaanRuutu;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (getSiirtovuoro())
			{
				// Valkoisen vuoro
				
				if (_lauta[i][j] == vk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
				}
			}
			else
			{
				// Mustan vuoro

				if (_lauta[i][j] == mk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
				}
			}
		}
	}

	// Otetaan negaatio siirtovuorosta. Tarvitaan onkoRuutuUhattu funktiolle
	int vastustajanSiirtoVuoro = getSiirtovuoro();
	if (vastustajanSiirtoVuoro == 0)
	{
		vastustajanSiirtoVuoro = 1;
	}
	else
	{
		vastustajanSiirtoVuoro = 0;
	}

	if (siirtoLista.empty())
	{
		// Siirtolista on tyhj‰, tilanne on joko matti tai patti
		if (onkoRuutuUhattu(&kuninkaanRuutu, &uusiAsema, vastustajanSiirtoVuoro))
		{
			// Matti
			laudanArvo = -10000;
		}
		else
		{
			// Patti
			laudanArvo = 0;
		}

		// return tarkalla arvolla
		paluu._evaluointiArvo = laudanArvo;
		// paluu._parasSiirto on alustamaton tarkoituksella
		return paluu;
	}
	else
	{
		if (syvyys == 0)
		{
			// Laskenta syvyys saavutettu, kutsutaan evaluointi funktiota ja palautetaan sen antama arvo
			paluu._evaluointiArvo = evaluoi();
			// paluu._parasSiirto on alustamaton tarkoituksella

			return paluu;
		}
		
		MinMaxPaluu miniPaluu;

		// Siirtoja on, k‰yd‰‰n kaikki l‰pi
		for (auto &siirto : siirtoLista)
		{
			// T‰ytyy luoda for loopissa aina uusi asema, joka syˆtet‰‰n syvemm‰lle rekursiossa
			Asema rekursioAsema(*this);

			rekursioAsema.paivitaAsema(&siirto);
			miniPaluu = rekursioAsema.alphaBetaMini(alpha, beta, syvyys - 1);

			// Beta leikkaus
			// Tulee ehk‰ ongelma ettei palauta siirtoa..?
			if (miniPaluu._evaluointiArvo >= beta)
			{
				miniPaluu._evaluointiArvo = beta;
				return miniPaluu;
			}

			if (miniPaluu._evaluointiArvo > laudanArvo)
			{
				// Voisi kirjoittaa myˆs kopiokonstruktorin MinMaxPaluulle
				// ja sijoittaa suoraan paluu = miniPaluu
				laudanArvo = miniPaluu._evaluointiArvo;
				parasSiirto = siirto;
			}
		}
	}

	paluu._evaluointiArvo = laudanArvo;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}


MinMaxPaluu Asema::alphaBetaMini(int alpha, int beta, int syvyys) 
{
	MinMaxPaluu paluu;
	double laudanArvo = 10000;
	Siirto parasSiirto;
	std::list<Siirto> siirtoLista;
	Asema uusiAsema = *this;

	annaLaillisetSiirrot(siirtoLista);
	Ruutu kuninkaanRuutu;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (getSiirtovuoro())
			{
				// Valkoisen vuoro

				if (_lauta[i][j] == vk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
				}
			}
			else
			{
				// Mustan vuoro

				if (_lauta[i][j] == mk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
				}
			}
		}
	}

	// Otetaan negaatio siirtovuorosta. Tarvitaan onkoRuutuUhattu funktiolle
	int vastustajanSiirtoVuoro = getSiirtovuoro();
	if (vastustajanSiirtoVuoro == 0)
	{
		vastustajanSiirtoVuoro = 1;
	}
	else
	{
		vastustajanSiirtoVuoro = 0;
	}

	if (siirtoLista.empty())
	{
		// Siirtolista on tyhj‰, tilanne on joko matti tai patti
		if (onkoRuutuUhattu(&kuninkaanRuutu, &uusiAsema, vastustajanSiirtoVuoro))
		{
			// Matti
			laudanArvo = 10000;
		}
		else
		{
			// Patti
			laudanArvo = 0;
		}

		// return tarkalla arvolla
		paluu._evaluointiArvo = laudanArvo;
		// paluu._parasSiirto on alustamaton tarkoituksella
		return paluu;
	}
	else
	{
		if (syvyys == 0)
		{
			// Laskenta syvyys saavutettu, kutsutaan evaluointi funktiota ja palautetaan sen antama arvo
			paluu._evaluointiArvo = evaluoi();
			// paluu._parasSiirto on alustamaton tarkoituksella

			return paluu;
		}

		MinMaxPaluu maxiPaluu;

		// Siirtoja on, k‰yd‰‰n kaikki l‰pi
		for (auto& siirto : siirtoLista)
		{
			// T‰ytyy luoda for loopissa aina uusi asema, joka syˆtet‰‰n syvemm‰lle rekursiossa
			Asema rekursioAsema(*this);

			rekursioAsema.paivitaAsema(&siirto);
			maxiPaluu = rekursioAsema.alphaBetaMaxi(alpha, beta, syvyys - 1);

			// Alpha leikkaus, sama ongelma kuin Maxissa (ehk‰)
			if (maxiPaluu._evaluointiArvo <= alpha)
			{
				maxiPaluu._evaluointiArvo = alpha;
				return maxiPaluu;
			}

			if (maxiPaluu._evaluointiArvo < laudanArvo)
			{
				// Voisi kirjoittaa myˆs kopiokonstruktorin MinMaxPaluulle
				// ja sijoittaa suoraan paluu = miniPaluu
				laudanArvo = maxiPaluu._evaluointiArvo;
				parasSiirto = siirto;
			}
		}
	}

	paluu._evaluointiArvo = laudanArvo;
	paluu._parasSiirto = parasSiirto;
	return paluu;
}

// Tarkistaa, onko uudessa asemassa kuningas uhattuna, kun vastustaja pelaa vuoronsa
bool Asema::onkoRuutuUhattu(Ruutu* kuninkaanRuutu, Asema* uusiAsema, int vastustajanVari)
{
	std::list<Siirto> vastustajanSiirtolista;
	Ruutu ruutu;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Siirrot valkoisille nappuloille
			if (vastustajanVari == 0)
			{
				if (uusiAsema->_lauta[i][j] == vs || uusiAsema->_lauta[i][j] == vt || uusiAsema->_lauta[i][j] == vr 
					|| uusiAsema->_lauta[i][j] == vl || uusiAsema->_lauta[i][j] == vd || uusiAsema->_lauta[i][j] == vk)
				{
					ruutu.setRivi(i);
					ruutu.setSarake(j);
					uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
				}
			}
			else // Siirrot mustille nappuloille
			{
				if (uusiAsema->_lauta[i][j] == ms || uusiAsema->_lauta[i][j] == mt || uusiAsema->_lauta[i][j] == mr
					|| uusiAsema->_lauta[i][j] == ml || uusiAsema->_lauta[i][j] == md || uusiAsema->_lauta[i][j] == mk)
				{
					ruutu.setRivi(i);
					ruutu.setSarake(j);
					uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
				}
			}
		}
	}
	
	// K‰yd‰‰n vastustajan siirtolista l‰pi ja tarkistetaan, lˆytyykˆ kuninkaan ruutu
	bool ruutuUhattu = false;
	for (int i = 0; i < vastustajanSiirtolista.size(); i++)
	{
		auto siirto = vastustajanSiirtolista.begin();
		advance(siirto, i);

		if (kuninkaanRuutu->getSarake() == siirto->getLoppuruutu().getSarake() && kuninkaanRuutu->getRivi() == siirto->getLoppuruutu().getRivi()) {
			ruutuUhattu = true;
		}
	}

	return ruutuUhattu;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) // Tarvitaanko lista.size() parametrina???
{ 
	
	// Teht‰isiinkˆ t‰m‰ annaLaillisetSiirrot-funkkarissa?
	Ruutu kuninkaanRuutu;

	// Haetaan kuninkaan sijainti
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Valkoinen kuningas
			if (vari == 0)
			{
				if (_lauta[i][j] == vk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
					break;
				}
			}
			else // Musta kuningas
			{
				if (_lauta[i][j] == mk)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
					break;
				}
			}
		}
	}

	// Tehd‰‰n kopioasema, jota voidaan muokata sekoittamatta oikeaa nykyist‰ asemaa
	Asema uusiAsema;
	std::list<Siirto> siivottuSiirtolista;
	Ruutu ruutu;
	
	// K‰yd‰‰n l‰pi siirtolistan siirrot ja poistetaan sielt‰ kuninkaan shakkiin johtavat siirrot
	for (int i = 0; i < lista.size(); i++)
	{
		auto siirto = lista.begin(); // auto tekee siirrosta iteraattorin
		advance(siirto, i);

		uusiAsema = *this;
		uusiAsema.paivitaAsema(&*siirto); // * dereferoi iteraattorin takaa olion ja & hakee muistipaikan

		// Onko kuninkaan siirto?
		if (siirto->onkoLyhytLinna())
		{
			ruutu.setSarake(6);
			if (vari == 0) {
				ruutu.setRivi(7);
			}
			else
			{
				ruutu.setRivi(0);
			}
		}
		else if(siirto->onkoPitkaLinna())
		{
			ruutu.setSarake(2);
			if (vari == 0) {
				ruutu.setRivi(7);
			}
			else
			{
				ruutu.setRivi(0);
			}
		}
		else
		{
			// Voi optimoida laittamalla funktiokutsut muuttujiin
			Nappula* siirtyvaNappula = (*this)._lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];
			if (siirtyvaNappula->getKoodi() == VK || siirtyvaNappula->getKoodi() == MK)
			{
				ruutu.setSarake(siirto->getLoppuruutu().getSarake());
				ruutu.setRivi(siirto->getLoppuruutu().getRivi());
			}
			else
			{
				// Ei ole kuninkaan siirto, jolloin kuninkaan koordinaatit on samat kuin aiemmin
				ruutu = kuninkaanRuutu;
			}
		}

		int vastustajanVari;
		if (vari == 0)
		{
			vastustajanVari = 1;
		}
		else
		{
			vastustajanVari = 0;
		}

		// Jos siirtoruutu ei aiheuta kuninkaalle uhkaa vastustajan vuorolla, se lis‰t‰‰n uuteen siirtolistaan
		if (!onkoRuutuUhattu(&ruutu, &uusiAsema, vastustajanVari))
		{
			siivottuSiirtolista.push_back(*siirto);
		}
	}

	lista = siivottuSiirtolista; // !!!T‰ytyy tarkistaa, toimiiko n‰in vai antaako tyhj‰n listan eteenp‰in!!!
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	Ruutu ruutu;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Siirrot valkoisille nappuloille
			if (_siirtovuoro == 0)
			{
				if (_lauta[i][j] == vs || _lauta[i][j] == vt || _lauta[i][j] == vr || _lauta[i][j] == vl || _lauta[i][j] == vd || _lauta[i][j] == vk)
				{
					ruutu.setRivi(i);
					ruutu.setSarake(j);
					_lauta[i][j]->annaSiirrot(lista, &ruutu, this, _siirtovuoro);
				}
			}
			else // Siirrot mustille nappuloille
			{
				if (_lauta[i][j] == ms || _lauta[i][j] == mt || _lauta[i][j] == mr || _lauta[i][j] == ml || _lauta[i][j] == md || _lauta[i][j] == mk)
				{
					ruutu.setRivi(i);
					ruutu.setSarake(j);
					_lauta[i][j]->annaSiirrot(lista, &ruutu, this, _siirtovuoro);
				}
			}
		}
	}
	annaLinnoitusSiirrot(lista, _siirtovuoro);
	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari)
{
		Asema uusiAsema = *this;

		//pitk‰n valkoisen linnotuksen lis‰‰minen lailliseksi siirroksi
		if (vari == 0  
			&& !getOnkoValkeaDTliikkunut() 
			&& !getOnkoValkeaKuningasLiikkunut() 
			&& !onkoRuutuUhattu(&Ruutu(2, 7), &uusiAsema , 1)
			&& !onkoRuutuUhattu(&Ruutu(3, 7), &uusiAsema , 1)
			&& !onkoRuutuUhattu(&Ruutu(4, 7), &uusiAsema, 1)
			&& _lauta[7][1] == NULL 
			&& _lauta [7][2] == NULL 
			&& _lauta [7][3]== NULL)
		{
			Siirto uusiSiirto(false, true);
			lista.push_back(uusiSiirto);
		}

		//lyhyt valkoisen linnotuksen lis‰‰minen lailliseksi siirroksi
		if (vari == 0 
			&& !getOnkoValkeaKTliikkunut() 
			&& !getOnkoValkeaKuningasLiikkunut() 
			&& !onkoRuutuUhattu(&Ruutu(4, 7), &uusiAsema, 1)
			&& !onkoRuutuUhattu(&Ruutu(5, 7), &uusiAsema, 1)
			&& !onkoRuutuUhattu(&Ruutu(6, 7), &uusiAsema, 1)
			&& _lauta[7][6] == NULL 
			&& _lauta[7][5] == NULL)
		{
			//Debuggausta
			bool valkeaKT = getOnkoValkeaKTliikkunut();
			bool valkeaK = getOnkoValkeaKuningasLiikkunut();
			bool ruutu47uhattu = onkoRuutuUhattu(&Ruutu(4, 7), &uusiAsema, 1);
			bool ruutu57uhattu = onkoRuutuUhattu(&Ruutu(5, 7), &uusiAsema, 1);
			bool ruutu67uhattu = onkoRuutuUhattu(&Ruutu(6, 7), &uusiAsema, 1);
			
			
			Siirto uusiSiirto(true, false);
			lista.push_back(uusiSiirto);
		}

		//pitk‰n musta linnotuksen lis‰‰minen lailliseksi siirroksi
		if (vari == 1 
			&& !getOnkoMustaDTliikkunut() 
			&& !getOnkoMustaKuningasLiikkunut() 
			&& !onkoRuutuUhattu(&Ruutu(2, 0), &uusiAsema, 0)
			&& !onkoRuutuUhattu(&Ruutu(3, 0), &uusiAsema, 0)
			&& !onkoRuutuUhattu(&Ruutu(4, 0), &uusiAsema, 0)
			&& _lauta[0][1] == NULL 
			&& _lauta[0][2] == NULL 
			&& _lauta[0][3] == NULL)
		{
			Siirto uusiSiirto(false, true);
			lista.push_back(uusiSiirto);
		}

		//lyhyt musta linnotuksen lis‰‰minen lailliseksi siirroksi
		if (vari == 1 
			&& !getOnkoMustaKTliikkunut() 
			&& !getOnkoMustaKuningasLiikkunut() 
			&& !onkoRuutuUhattu(&Ruutu(4, 0), &uusiAsema, 0)
			&& !onkoRuutuUhattu(&Ruutu(5, 0), &uusiAsema, 0)
			&& !onkoRuutuUhattu(&Ruutu(6, 0), &uusiAsema, 0)
			&& _lauta[0][6] == NULL 
			&& _lauta[0][5] == NULL)
		{
			Siirto uusiSiirto(true, false);
			lista.push_back(uusiSiirto);
		}
}