#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include <array>
#include <chrono>
#include <vector>
#include "Ajastin.h"
#include <unordered_map>
#include <algorithm>

const int keskipelisotilasV[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	98, 134, 61, 95, 68, 126, 34, -11,
	-6, 7, 26, 31, 65, 56, 25, -20,
	-14, 13, 6, 21, 23, 12, 17, -23,
	-27, -2, -5, 12, 17, 6, 10, -25,
	-26, -4, -4, -10, 3, 3, 33, -12,
	-35, -1, -20, -23, -15, 24, 38, -22,
	0, 0, 0, 0, 0, 0, 0, 0,
};

const int loppupelisotilasV[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	178, 173, 158, 134, 147, 132, 165, 187,
	94, 100,  85,  67,  56,  53,  82,  84,
	32,  24,  13,   5,  -2,   4,  17,  17,
	13,   9,  -3,  -7,  -7,  -8,   3,  -1,
	4,   7,  -6,   1,   0,  -5,  -1,  -8,
	13,   8,   8,  10,  13,   0,   2,  -7,
	0,   0,   0,   0,   0,   0,   0,   0,
};

const int keskipeliratsuV[64] = {
	-167, -89, -34, -49,  61, -97, -15, -107,
	-73, -41,  72,  36,  23,  62,   7,  -17,
	-47,  60,  37,  65,  84, 129,  73,   44,
	-9,  17,  19,  53,  37,  69,  18,   22,
	-13,   4,  16,  13,  28,  19,  21,   -8,
	-23,  -9,  12,  10,  19,  17,  25,  -16,
	-29, -53, -12,  -3,  -1,  18, -14,  -19,
	-105, -21, -58, -33, -17, -28, -19,  -23,
};

const int loppupeliratsuV[64] = {
	-58, -38, -13, -28, -31, -27, -63, -99,
	-25,  -8, -25,  -2,  -9, -25, -24, -52,
	-24, -20,  10,   9,  -1,  -9, -19, -41,
	-17,   3,  22,  22,  22,  11,   8, -18,
	-18,  -6,  16,  25,  16,  17,   4, -18,
	-23,  -3,  -1,  15,  10,  -3, -20, -22,
	-42, -20, -10,  -5,  -2, -20, -23, -44,
	-29, -51, -23, -15, -22, -18, -50, -64,
};

const int keskipelilahettiV[64] = {
	-29,   4, -82, -37, -25, -42,   7,  -8,
	-26,  16, -18, -13,  30,  59,  18, -47,
	-16,  37,  43,  40,  35,  50,  37,  -2,
	-4,   5,  19,  50,  37,  37,   7,  -2,
	-6,  13,  13,  26,  34,  12,  10,   4,
	0,  15,  15,  15,  14,  27,  18,  10,
	4,  15,  16,   0,   7,  21,  33,   1,
	-33,  -3, -14, -21, -13, -12, -39, -21,
};

const int loppupelilahettiV[64] = {
	-14, -21, -11,  -8, -7,  -9, -17, -24,
	-8,  -4,   7, -12, -3, -13,  -4, -14,
	2,  -8,   0,  -1, -2,   6,   0,   4,
	-3,   9,  12,   9, 14,  10,   3,   2,
	-6,   3,  13,  19,  7,  10,  -3,  -9,
	-12,  -3,   8,  10, 13,   3,  -7, -15,
	-14, -18,  -7,  -1,  4,  -9, -15, -27,
	-23,  -9, -23,  -5, -9, -16,  -5, -17,
};

const int keskipelitorniV[64] = {
	32,  42,  32,  51, 63,  9,  31,  43,
	27,  32,  58,  62, 80, 67,  26,  44,
	-5,  19,  26,  36, 17, 45,  61,  16,
	-24, -11,   7,  26, 24, 35,  -8, -20,
	-36, -26, -12,  -1,  9, -7,   6, -23,
	-45, -25, -16, -17,  3,  0,  -5, -33,
	-44, -16, -20,  -9, -1, 11,  -6, -71,
	-19, -13,   1,  17, 16,  7, -37, -26,
};

const int loppupelitorniV[64] = {
	13, 10, 18, 15, 12,  12,   8,   5,
	11, 13, 13, 11, -3,   3,   8,   3,
	7,  7,  7,  5,  4,  -3,  -5,  -3,
	4,  3, 13,  1,  2,   1,  -1,   2,
	3,  5,  8,  4, -5,  -6,  -8, -11,
	-4,  0, -5, -1, -7, -12,  -8, -16,
	-6, -6,  0,  2, -9,  -9, -11,  -3,
	-9,  2,  3, -1, -5, -13,   4, -20,
};

const int keskipelidaamiV[64] = {
	-28,   0,  29,  12,  59,  44,  43,  45,
	-24, -39,  -5,   1, -16,  57,  28,  54,
	-13, -17,   7,   8,  29,  56,  47,  57,
	-27, -27, -16, -16,  -1,  17,  -2,   1,
	-9, -26,  -9, -10,  -2,  -4,   3,  -3,
	-14,   2, -11,  -2,  -5,   2,  14,   5,
	-35,  -8,  11,   2,   8,  15,  -3,   1,
	-1, -18,  -9,  10, -15, -25, -31, -50,
};

const int loppupelidaamiV[64] = {
	-9,  22,  22,  27,  27,  19,  10,  20,
	-17,  20,  32,  41,  58,  25,  30,   0,
	-20,   6,   9,  49,  47,  35,  19,   9,
	3,  22,  24,  45,  57,  40,  57,  36,
	-18,  28,  19,  47,  31,  34,  39,  23,
	-16, -27,  15,   6,   9,  17,  10,   5,
	-22, -23, -30, -16, -16, -23, -36, -32,
	-33, -28, -22, -43,  -5, -32, -20, -41,
};

const int keskipelikuningasV[64] = {
	-65,  23,  16, -15, -56, -34,   2,  13,
	29,  -1, -20,  -7,  -8,  -4, -38, -29,
	-9,  24,   2, -16, -20,   6,  22, -22,
	-17, -20, -12, -27, -30, -25, -14, -36,
	-49,  -1, -27, -39, -46, -44, -33, -51,
	-14, -14, -22, -46, -44, -30, -15, -27,
	1,   7,  -8, -64, -43, -16,   9,   8,
	-15,  36,  12, -54,   8, -28,  24,  14,
};

const int loppupelikuningasV[64] = {
	-74, -35, -18, -18, -11,  15,   4, -17,
	-12,  17,  14,  17,  17,  38,  23,  11,
	10,  17,  23,  15,  20,  45,  44,  13,
	-8,  22,  24,  27,  26,  33,  26,   3,
	-18,  -4,  21,  24,  27,  23,   9, -11,
	-19,  -3,  11,  21,  23,  16,   7,  -9,
	-27, -11,   4,  13,  14,   4,  -5, -17,
	-53, -34, -21, -11, -28, -14, -24, -43
};


const int keskipelisotilasM[64] = {
	0,   0,   0,   0,   0,   0,  0,   0,
	-35,  -1, -20, -23, -15,  24, 38, -22,
	-26,  -4,  -4, -10,   3,   3, 33, -12,
	-27,  -2,  -5,  12,  17,   6, 10, -25,
	-14,  13,   6,  21,  23,  12, 17, -23,
	-6,   7,  26,  31,  65,  56, 25, -20,
	98, 134,  61,  95,  68, 126, 34, -11,
	0,   0,   0,   0,   0,   0,  0,   0,
};


const int loppupelisotilasM[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	13,   8,   8,  10,  13,   0,   2,  -7,
	4,   7,  -6,   1,   0,  -5,  -1,  -8,
	13,   9,  -3,  -7,  -7,  -8,   3,  -1,
	32,  24,  13,   5,  -2,   4,  17,  17,
	94, 100,  85,  67,  56,  53,  82,  84,
	178, 173, 158, 134, 147, 132, 165, 187,
	0,   0,   0,   0,   0,   0,   0,   0,
};

const int keskipeliratsuM[64] = {
	-105, -21, -58, -33, -17, -28, -19,  -23,
	-29, -53, -12,  -3,  -1,  18, -14,  -19,
	-23,  -9,  12,  10,  19,  17,  25,  -16,
	-13,   4,  16,  13,  28,  19,  21,   -8,
	-9,  17,  19,  53,  37,  69,  18,   22,
	-47,  60,  37,  65,  84, 129,  73,   44,
	-73, -41,  72,  36,  23,  62,   7,  -17,
	-167, -89, -34, -49,  61, -97, -15, -107,
};

const int loppupeliratsuM[64] = {
	-29, -51, -23, -15, -22, -18, -50, -64,
	-42, -20, -10,  -5,  -2, -20, -23, -44,
	-23,  -3,  -1,  15,  10,  -3, -20, -22,
	-18,  -6,  16,  25,  16,  17,   4, -18,
	-17,   3,  22,  22,  22,  11,   8, -18,
	-24, -20,  10,   9,  -1,  -9, -19, -41,
	-25,  -8, -25,  -2,  -9, -25, -24, -52,
	-58, -38, -13, -28, -31, -27, -63, -99,
};

const int keskipelilahettiM[64] = {
	-33,  -3, -14, -21, -13, -12, -39, -21,
	4,  15,  16,   0,   7,  21,  33,   1,
	0,  15,  15,  15,  14,  27,  18,  10,
	-6,  13,  13,  26,  34,  12,  10,   4,
	-4,   5,  19,  50,  37,  37,   7,  -2,
	-16,  37,  43,  40,  35,  50,  37,  -2,
	-26,  16, -18, -13,  30,  59,  18, -47,
	-29,   4, -82, -37, -25, -42,   7,  -8,
};

const int loppupelilahettiM[64] = {
	-23,  -9, -23,  -5, -9, -16,  -5, -17,
	-14, -18,  -7,  -1,  4,  -9, -15, -27,
	-12,  -3,   8,  10, 13,   3,  -7, -15,
	-6,   3,  13,  19,  7,  10,  -3,  -9,
	-3,   9,  12,   9, 14,  10,   3,   2,
	2,  -8,   0,  -1, -2,   6,   0,   4,
	-8,  -4,   7, -12, -3, -13,  -4, -14,
	-14, -21, -11,  -8, -7,  -9, -17, -24,
};

const int keskipelitorniM[64] = {
	-19, -13,   1,  17, 16,  7, -37, -26,
	-44, -16, -20,  -9, -1, 11,  -6, -71,
	-45, -25, -16, -17,  3,  0,  -5, -33,
	-36, -26, -12,  -1,  9, -7,   6, -23,
	-24, -11,   7,  26, 24, 35,  -8, -20,
	-5,  19,  26,  36, 17, 45,  61,  16,
	27,  32,  58,  62, 80, 67,  26,  44,
	32,  42,  32,  51, 63,  9,  31,  43,
};

const int loppupelitorniM[64] = {
	-9,  2,  3, -1, -5, -13,   4, -20,
	-6, -6,  0,  2, -9,  -9, -11,  -3,
	-4,  0, -5, -1, -7, -12,  -8, -16,
	3,  5,  8,  4, -5,  -6,  -8, -11,
	4,  3, 13,  1,  2,   1,  -1,   2,
	7,  7,  7,  5,  4,  -3,  -5,  -3,
	11, 13, 13, 11, -3,   3,   8,   3,
	13, 10, 18, 15, 12,  12,   8,   5,
};

const int keskipelidaamiM[64] = {
	-1, -18,  -9,  10, -15, -25, -31, -50,
	-35,  -8,  11,   2,   8,  15,  -3,   1,
	-14,   2, -11,  -2,  -5,   2,  14,   5,
	-9, -26,  -9, -10,  -2,  -4,   3,  -3,
	-27, -27, -16, -16,  -1,  17,  -2,   1,
	-13, -17,   7,   8,  29,  56,  47,  57,
	-24, -39,  -5,   1, -16,  57,  28,  54,
	-28,   0,  29,  12,  59,  44,  43,  45,
};

const int loppupelidaamiM[64] = {
	-33, -28, -22, -43,  -5, -32, -20, -41,
	-22, -23, -30, -16, -16, -23, -36, -32,
	-16, -27,  15,   6,   9,  17,  10,   5,
	-18,  28,  19,  47,  31,  34,  39,  23,
	3,  22,  24,  45,  57,  40,  57,  36,
	-20,   6,   9,  49,  47,  35,  19,   9,
	-17,  20,  32,  41,  58,  25,  30,   0,
	-9,  22,  22,  27,  27,  19,  10,  20,
};

const int keskipelikuningasM[64] = {
	-15,  36,  12, -54,   8, -28,  24,  14,
	1,   7,  -8, -64, -43, -16,   9,   8,
	-14, -14, -22, -46, -44, -30, -15, -27,
	-49,  -1, -27, -39, -46, -44, -33, -51,
	-17, -20, -12, -27, -30, -25, -14, -36,
	-9,  24,   2, -16, -20,   6,  22, -22,
	29,  -1, -20,  -7,  -8,  -4, -38, -29,
	-65,  23,  16, -15, -56, -34,   2,  13,
};

const int loppupelikuningasM[64] = {
	-53, -34, -21, -11, -28, -14, -24, -43
	-27, -11,   4,  13,  14,   4,  -5, -17,
	-19,  -3,  11,  21,  23,  16,   7,  -9,
	-18,  -4,  21,  24,  27,  23,   9, -11,
	-8,  22,  24,  27,  26,  33,  26,   3,
	10,  17,  23,  15,  20,  45,  44,  13,
	-12,  17,  14,  17,  17,  38,  23,  11,
	-74, -35, -18, -18, -11,  15,   4, -17,
};

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
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
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

	// Liikkumisflagit asetetaan falseksi ja asetetaan upseerien m‰‰r‰ ja onko daamit laudalla
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
	_valkoisetUpseerit = 8;
	_mustatUpseerit = 8;
	_onkoValkeaDLaudalla = true;
	_onkoMustaDLaudalla = true;
}

void Asema::paivitaAsema(Siirto *siirto)
{
	int alkurivi = siirto->getAlkuruutu().getRivi();
	int alkusarake = siirto->getAlkuruutu().getSarake();
	int loppurivi = siirto->getLoppuruutu().getRivi();
	int loppusarake = siirto->getLoppuruutu().getSarake();

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
		Nappula* nappula = _lauta[alkurivi][alkusarake];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[loppurivi][loppusarake] = nappula;
		
		// Tarkistetaan, onko ohestalyˆnti. Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if (nappula->getKoodi() == MS && alkurivi == 4 && loppusarake == kaksoisaskelSarakkeella)
		{
			_lauta[loppurivi - 1][loppusarake] = NULL;
		}
		if (nappula->getKoodi() == VS && alkurivi == 3 && loppusarake == kaksoisaskelSarakkeella)
		{
			_lauta[loppurivi + 1][loppusarake] = NULL;
		}
		
		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if (nappula->getKoodi() == MS && loppurivi == 3 && alkurivi == 1)
		{
			kaksoisaskelSarakkeella = loppusarake;
		}
		else if (nappula->getKoodi() == VS && loppurivi == 4 && alkurivi == 6)
		{
			kaksoisaskelSarakkeella = loppusarake;
		}
		else
		{
			kaksoisaskelSarakkeella = -1;
		}

		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		
		// Maikan ylempi kommentti on h‰mment‰v‰. Luullakseni t‰m‰ korottaa sotilaan oikein
		if ((loppurivi == 7 || loppurivi == 0) &&
			(nappula->getKoodi() == MS || nappula->getKoodi() == VS))
		{
			// Siirron loppuruutu on laudan p‰‰ty, sek‰ nappula on sotilas. Siirrolla on korotus arvo
			// Asetetaan nappula osoitin osoittamaan korotusarvon omaiseen nappulaan
			nappula = siirto->_miksikorotetaan;
			// P‰ivitet‰‰n laudalle oikean tyyppinen nappula
			_lauta[loppurivi][loppusarake] = nappula;
		}

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
		_lauta[alkurivi][alkusarake] = NULL;

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if (nappula->getKoodi() == MK) {
			_onkoMustaKuningasLiikkunut = true;
		}
		if (nappula->getKoodi() == VK) {
			_onkoValkeaKuningasLiikkunut = true;
		}

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if (nappula->getKoodi() == VT && _lauta[7][0]) {
			_onkoValkeaDTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && _lauta[7][7]) {
			_onkoValkeaKTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && _lauta[0][7]) {
			_onkoMustaDTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && _lauta[0][0]) {
			_onkoMustaKTliikkunut = true;
		}
	}

	//Tarkistetaan, onko daamit laudalla ja lasketaan upseerit (keski- ja loppupeli‰ varten)
	_onkoValkeaDLaudalla = false;
	_onkoMustaDLaudalla = false;
	_valkoisetUpseerit = 0;
	_mustatUpseerit = 0;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j) 
		{
			if (_lauta[i][j] != NULL)
			{
				if (_lauta[i][j]->getKoodi() == VD)
				{
					_onkoValkeaDLaudalla = true;
				}
				if (_lauta[i][j]->getKoodi() == MD)
				{
					_onkoMustaDLaudalla = true;
				}
				if (_lauta[i][j]->getKoodi() == VT || _lauta[i][j]->getKoodi() == VR|| _lauta[i][j]->getKoodi() == VL || _lauta[i][j]->getKoodi() == VK || _lauta[i][j]->getKoodi() == VD)
				{
					_valkoisetUpseerit++;
				}
				if (_lauta[i][j]->getKoodi() == MT || _lauta[i][j]->getKoodi() == MR || _lauta[i][j]->getKoodi() == ML || _lauta[i][j]->getKoodi() == MK || _lauta[i][j]->getKoodi() == MD)
				{
					_mustatUpseerit++;
				}
			}
		}
	}

	//P‰ivitet‰‰n _siirtovuoro
	_siirtovuoro = getVastustajanSiirtovuoro();
}

int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}

int Asema::getVastustajanSiirtovuoro()
{
	if (_siirtovuoro == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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

Ruutu Asema::getKuninkaanRuutu(int vari)
{
	Ruutu kuninkaanRuutu;

	// Haetaan kuninkaan sijainti
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// Valkoinen kuningas
			if (vari == 0)
			{
				if (_lauta[i][j] != NULL && _lauta[i][j]->getKoodi() == VK)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
					break;
				}
			}
			else // Musta kuningas
			{
				if (_lauta[i][j] != NULL && _lauta[i][j]->getKoodi() == MK)
				{
					kuninkaanRuutu.setRivi(i);
					kuninkaanRuutu.setSarake(j);
					break;
				}
			}
		}
	}

	return kuninkaanRuutu;
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

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
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

bool Asema::onkoKeskiVaiLoppupeli(int vari) 
{
	bool keskipeli = true;

	if (vari == 0) 
	{
		if (_onkoValkeaDLaudalla == false && _valkoisetUpseerit <= 3) 
		{
			keskipeli = false;
		}
		else if (_onkoValkeaDLaudalla == true && _valkoisetUpseerit == 1)
		{
			keskipeli = false;
		}
	}
	else 
	{
		if (_onkoMustaDLaudalla == false && _mustatUpseerit <= 3)
		{
			keskipeli = false;
		}
		else if (_onkoMustaDLaudalla == true && _mustatUpseerit == 1)
		{
			keskipeli = false;
		}
	}

	return keskipeli;

	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
}


double Asema::nappuloitaKeskella(int vari) 
{
	double summa = 0;
	int ruutu, sarake;
	Nappula* nappula;

	if (vari == 0) 
	{
		if (onkoKeskiVaiLoppupeli(vari))
		{
			for (int i = 0; i < 64; ++i) {
				ruutu = floor((float)i / 8), sarake = i % 8;
				nappula = this->_lauta[ruutu][sarake];

				if (nappula != nullptr)
				{
					if (nappula->getKoodi() == VS) {
						summa += keskipelisotilasV[i];
					}
					else if (nappula->getKoodi() == VR) {
						summa += keskipeliratsuV[i];
					}
					else if (nappula->getKoodi() == VL) {
						summa += keskipelilahettiV[i];
					}
					else if (nappula->getKoodi() == VT) {
						summa += keskipelitorniV[i];
					}
					else if (nappula->getKoodi() == VK) {
						summa += keskipelikuningasV[i];
					}
					else if (nappula->getKoodi() == VD) {
						summa += keskipelidaamiV[i];
					}
				}
			}
		}
		else 
		{
			for (int i = 0; i < 64; ++i) {
				ruutu = floor((float)i / 8), sarake = i % 8;
				nappula = this->_lauta[ruutu][sarake];

				if (nappula != nullptr)
				{
					if (nappula->getKoodi() == VS) {
						summa += loppupelisotilasV[i];
					}
					else if (nappula->getKoodi() == VR) {
						summa += loppupeliratsuV[i];
					}
					else if (nappula->getKoodi() == VL) {
						summa += loppupelilahettiV[i];
					}
					else if (nappula->getKoodi() == VT) {
						summa += loppupelitorniV[i];
					}
					else if (nappula->getKoodi() == VK) {
						summa += loppupelikuningasV[i];
					}
					else if (nappula->getKoodi() == VD) {
						summa += loppupelidaamiV[i];
					}
				}
			}
		}
	}
	else 
	{
		if (onkoKeskiVaiLoppupeli(vari))
		{
			for (int i = 0; i < 64; ++i) {
				ruutu = floor((float)i / 8), sarake = i % 8;
				nappula = this->_lauta[ruutu][sarake];

				if (nappula != nullptr)
				{
					if (nappula->getKoodi() == MS) {
						summa += -1 * keskipelisotilasM[i];
					}
					else if (nappula->getKoodi() == MR) {
						summa += -1 * keskipeliratsuM[i];
					}
					else if (nappula->getKoodi() == ML) {
						summa += -1 * keskipelilahettiM[i];
					}
					else if (nappula->getKoodi() == MT) {
						summa += -1 * keskipelitorniM[i];
					}
					else if (nappula->getKoodi() == MK) {
						summa += -1 * keskipelikuningasM[i];
					}
					else if (nappula->getKoodi() == MD) {
						summa += -1 * keskipelidaamiM[i];
					}
				}
			}
		}
		else 
		{
			for (int i = 0; i < 64; ++i) {
				ruutu = floor((float)i / 8), sarake = i % 8;
				nappula = this->_lauta[ruutu][sarake];

				if (nappula != nullptr)
				{
					if (nappula->getKoodi() == MS) {
						summa += -1 * loppupelisotilasM[i];
					}
					else if (nappula->getKoodi() == MR) {
						summa += -1 * loppupeliratsuM[i];
					}
					else if (nappula->getKoodi() == ML) {
						summa += -1 * loppupelilahettiM[i];
					}
					else if (nappula->getKoodi() == MT) {
						summa += -1 * loppupelitorniM[i];
					}
					else if (nappula->getKoodi() == MK) {
						summa += -1 * loppupelikuningasM[i];
					}
					else if (nappula->getKoodi() == MD) {
						summa += -1 * loppupelidaamiM[i];
					}
				}
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

MinMaxPaluu Asema::alphaBetaMaxi(int alpha, int beta, int syvyys, std::unordered_map<int, std::vector<Siirto>> &umap)
{
	MinMaxPaluu paluu;
	double laudanArvo = -10000;
	Siirto parasSiirto;
	std::vector<Siirto> siirrot;
	siirrot.reserve(200);
	Asema uusiAsema = *this;

	annaLaillisetSiirrot(siirrot);
	// J‰rjest‰‰ syˆnti siirrot ensimm‰iseksi
	std::sort(siirrot.begin(), siirrot.end());
	Ruutu kuninkaanRuutu = getKuninkaanRuutu(getSiirtovuoro());

	// Otetaan negaatio siirtovuorosta. Tarvitaan onkoRuutuUhattu funktiolle
	int vastustajanSiirtoVuoro = getVastustajanSiirtovuoro();

	if (siirrot.empty())
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
		Asema rekursioAsema;
		// Flag onko killerit k‰yty
		bool onKayty = false;

		// Siirtoja on, k‰yd‰‰n kaikki l‰pi
		for (auto &siirto : siirrot)
		{
			

			// T‰h‰n kohtaan if joka katsoo onko syˆnti siirto, jos on syˆnti
			// jatketaan eteenp‰in, jos ei tarkistetaan killermovet
			if (siirto._onSyonti)
			{
				// Siirto on syˆnti, k‰yd‰‰n ne ensiksi
			}
			else
			{
				if (!onKayty)
				{
					// Killermoveja ei ole viel‰ k‰yty, k‰yd‰‰n ne

					// Etsit‰‰n hash taulusta t‰ll‰ syvyydell‰ olevat siirrot
					// Jos siirtoja lˆytyy, tarkistetaan ne, muuten hyp‰t‰‰n eteenp‰in

					auto iter = umap.find(syvyys);
					if (iter != umap.end())
					{
						// Lˆytyi killer siirtoja t‰lt‰ syvyydelt‰, k‰yd‰‰n ne l‰pi
						for (auto& killerSiirto : iter->second)
						{
							// Tarkistetaan ensin lˆytyykˆ kyseist‰ siirtoa edes siirtotaulusta
							for (auto& slSiirto : siirrot)
							{
								if (!slSiirto.onkoLyhytLinna() && !slSiirto.onkoPitkaLinna() &&
									!killerSiirto.onkoLyhytLinna() && !killerSiirto.onkoPitkaLinna() &&
									slSiirto.getAlkuruutu().getRivi() == killerSiirto.getAlkuruutu().getRivi() &&
									slSiirto.getAlkuruutu().getSarake() == killerSiirto.getAlkuruutu().getSarake() &&
									slSiirto.getLoppuruutu().getRivi() == killerSiirto.getLoppuruutu().getRivi() &&
									slSiirto.getLoppuruutu().getSarake() == killerSiirto.getLoppuruutu().getSarake())
								{
									// Jos siirto ei ole linnoitussiirto (helpottaa l‰pik‰ynti‰) ja killersiirto lˆytyy siirtolistasta
									
									rekursioAsema = *this;

									rekursioAsema.paivitaAsema(&killerSiirto);
									miniPaluu = rekursioAsema.alphaBetaMini(alpha, beta, syvyys - 1, umap);

									if (miniPaluu._evaluointiArvo >= beta)
									{
										miniPaluu._evaluointiArvo = beta;
										return miniPaluu;
									}

									if (miniPaluu._evaluointiArvo > laudanArvo)
									{
										laudanArvo = miniPaluu._evaluointiArvo;
										parasSiirto = killerSiirto;
									}
								}
							}
						}
					}
					onKayty = true;
				}
			}

			

			// T‰ytyy luoda for loopissa aina uusi asema, joka syˆtet‰‰n syvemm‰lle rekursiossa
			rekursioAsema = *this;

			rekursioAsema.paivitaAsema(&siirto);
			miniPaluu = rekursioAsema.alphaBetaMini(alpha, beta, syvyys - 1, umap);

			// Beta leikkaus
			// Tulee ehk‰ ongelma ettei palauta siirtoa..?
			// T‰m‰ on killer move
			if (miniPaluu._evaluointiArvo >= beta)
			{
				miniPaluu._evaluointiArvo = beta;

				// Lis‰t‰‰n killer move hashmappiin
				auto iterator = umap.find(syvyys);
				if (iterator != umap.end())
				{
					// Lˆytyi jo olemassa oleva siirto t‰lt‰ syvyydelt‰, lis‰t‰‰n jatkoksi
					iterator->second.push_back(siirto);
				}
				else
				{
					// Ei lˆytynyt olemassa olevaa siirtoa t‰lt‰ syvyydelt‰, lis‰t‰‰n hashmappiin
					// Meneekˆh‰n t‰‰ oikein?
					vector<Siirto> killerSiirrot;
					killerSiirrot.reserve(50);
					pair<int, vector<Siirto>> jeps(syvyys, killerSiirrot);
					umap.insert(jeps);
					
					//umap.insert(make_pair<int, vector<Siirto>>(syvyys, killerSiirrot));
				}
				
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

MinMaxPaluu Asema::alphaBetaMini(int alpha, int beta, int syvyys, std::unordered_map<int, std::vector<Siirto>> &umap)
{
	MinMaxPaluu paluu;
	double laudanArvo = 10000;
	Siirto parasSiirto;
	std::vector<Siirto> siirrot;
	siirrot.reserve(200);
	Asema uusiAsema = *this;

	annaLaillisetSiirrot(siirrot);
	// J‰rjest‰‰ syˆnti siirrot ensimm‰iseksi
	std::sort(siirrot.begin(), siirrot.end());
	Ruutu kuninkaanRuutu = getKuninkaanRuutu(getSiirtovuoro());

	// Otetaan negaatio siirtovuorosta. Tarvitaan onkoRuutuUhattu funktiolle
	int vastustajanSiirtoVuoro = getVastustajanSiirtovuoro();

	if (siirrot.empty())
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
		Asema rekursioAsema;
		// Flag onko killerit k‰yty
		bool onKayty = false;

		// Siirtoja on, k‰yd‰‰n kaikki l‰pi
		for (auto& siirto : siirrot)
		{
			

			// T‰h‰n kohtaan if joka katsoo onko syˆnti siirto, jos on syˆnti
			// jatketaan eteenp‰in, jos ei tarkistetaan killermovet
			if (siirto._onSyonti)
			{
				// Siirto on syˆnti, k‰yd‰‰n ne ensiksi
			}
			else
			{
				if (!onKayty)
				{
					// Killermoveja ei ole viel‰ k‰yty, k‰yd‰‰n ne

					// Etsit‰‰n hash taulusta t‰ll‰ syvyydell‰ olevat siirrot
					// Jos siirtoja lˆytyy, tarkistetaan ne, muuten hyp‰t‰‰n eteenp‰in

					auto iter = umap.find(syvyys);
					if (iter != umap.end())
					{
						// Lˆytyi killer siirtoja t‰lt‰ syvyydelt‰, k‰yd‰‰n ne l‰pi
						for (auto& killerSiirto : iter->second)
						{
							// Tarkistetaan ensin lˆytyykˆ kyseist‰ siirtoa edes siirtotaulusta
							for (auto& slSiirto : siirrot)
							{
								if (!slSiirto.onkoLyhytLinna() && !slSiirto.onkoPitkaLinna() &&
									!killerSiirto.onkoLyhytLinna() && !killerSiirto.onkoPitkaLinna() &&
									slSiirto.getAlkuruutu().getRivi() == killerSiirto.getAlkuruutu().getRivi() &&
									slSiirto.getAlkuruutu().getSarake() == killerSiirto.getAlkuruutu().getSarake() &&
									slSiirto.getLoppuruutu().getRivi() == killerSiirto.getLoppuruutu().getRivi() &&
									slSiirto.getLoppuruutu().getSarake() == killerSiirto.getLoppuruutu().getSarake())
								{
									// Jos siirto ei ole linnoitussiirto (helpottaa l‰pik‰ynti‰) ja killersiirto lˆytyy siirtolistasta

									rekursioAsema = *this;

									rekursioAsema.paivitaAsema(&killerSiirto);
									maxiPaluu = rekursioAsema.alphaBetaMaxi(alpha, beta, syvyys - 1, umap);

									if (maxiPaluu._evaluointiArvo >= beta)
									{
										maxiPaluu._evaluointiArvo = beta;
										return maxiPaluu;
									}

									if (maxiPaluu._evaluointiArvo > laudanArvo)
									{
										laudanArvo = maxiPaluu._evaluointiArvo;
										parasSiirto = killerSiirto;
									}
								}
							}
						}
					}
					onKayty = true;
				}
			}
			
			

			// T‰ytyy luoda for loopissa aina uusi asema, joka syˆtet‰‰n syvemm‰lle rekursiossa
			rekursioAsema = *this;

			rekursioAsema.paivitaAsema(&siirto);
			maxiPaluu = rekursioAsema.alphaBetaMaxi(alpha, beta, syvyys - 1, umap);

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
// Overloadattu versio huolehdiKuninkaanShakeista funktiota varten
bool Asema::onkoRuutuUhattu(Ruutu* kuninkaanRuutu, Asema* uusiAsema, int vastustajanVari, std::vector<Siirto> vastustajanSiirtolista)
{
	// Tyhjennet‰‰n siirtolista joka kierroksen alussa
	vastustajanSiirtolista.clear();
	Ruutu ruutu;
	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// Siirrot valkoisille nappuloille
			if (vastustajanVari == 0)
			{
				if (uusiAsema->_lauta[i][j] != NULL)
				{
					if (uusiAsema->_lauta[i][j]->getKoodi() == VS || uusiAsema->_lauta[i][j]->getKoodi() == VT || uusiAsema->_lauta[i][j]->getKoodi() == VR
						|| uusiAsema->_lauta[i][j]->getKoodi() == VL || uusiAsema->_lauta[i][j]->getKoodi() == VD || uusiAsema->_lauta[i][j]->getKoodi() == VK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
					}
				}
			}
			else // Siirrot mustille nappuloille
			{
				if (uusiAsema->_lauta[i][j] != NULL)
				{
					if (uusiAsema->_lauta[i][j]->getKoodi() == MS || uusiAsema->_lauta[i][j]->getKoodi() == MT || uusiAsema->_lauta[i][j]->getKoodi() == MR
						|| uusiAsema->_lauta[i][j]->getKoodi() == ML || uusiAsema->_lauta[i][j]->getKoodi() == MD || uusiAsema->_lauta[i][j]->getKoodi() == MK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
					}
				}
			}
		}
	}
	
	// K‰yd‰‰n vastustajan siirtolista l‰pi ja tarkistetaan, lˆytyykˆ kuninkaan ruutu
	bool ruutuUhattu = false;
	for (auto& siirto : vastustajanSiirtolista)
	{
		if (kuninkaanRuutu->getSarake() == siirto.getLoppuruutu().getSarake() && kuninkaanRuutu->getRivi() == siirto.getLoppuruutu().getRivi()) {
			ruutuUhattu = true;
			break;
		}
	}

	return ruutuUhattu;
}

// Versio ilman vectoria parametrina
bool Asema::onkoRuutuUhattu(Ruutu* kuninkaanRuutu, Asema* uusiAsema, int vastustajanVari)
{
	std::vector<Siirto> vastustajanSiirtolista;
	vastustajanSiirtolista.reserve(200);
	Ruutu ruutu;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// Siirrot valkoisille nappuloille
			if (vastustajanVari == 0)
			{
				if (uusiAsema->_lauta[i][j] != NULL)
				{
					if (uusiAsema->_lauta[i][j]->getKoodi() == VS || uusiAsema->_lauta[i][j]->getKoodi() == VT || uusiAsema->_lauta[i][j]->getKoodi() == VR
						|| uusiAsema->_lauta[i][j]->getKoodi() == VL || uusiAsema->_lauta[i][j]->getKoodi() == VD || uusiAsema->_lauta[i][j]->getKoodi() == VK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
					}
				}
			}
			else // Siirrot mustille nappuloille
			{
				if (uusiAsema->_lauta[i][j] != NULL)
				{
					if (uusiAsema->_lauta[i][j]->getKoodi() == MS || uusiAsema->_lauta[i][j]->getKoodi() == MT || uusiAsema->_lauta[i][j]->getKoodi() == MR
						|| uusiAsema->_lauta[i][j]->getKoodi() == ML || uusiAsema->_lauta[i][j]->getKoodi() == MD || uusiAsema->_lauta[i][j]->getKoodi() == MK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						uusiAsema->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &ruutu, uusiAsema, vastustajanVari);
					}
				}
			}
		}
	}

	// K‰yd‰‰n vastustajan siirtolista l‰pi ja tarkistetaan, lˆytyykˆ kuninkaan ruutu
	bool ruutuUhattu = false;
	for (auto& siirto : vastustajanSiirtolista)
	{
		if (kuninkaanRuutu->getSarake() == siirto.getLoppuruutu().getSarake() && kuninkaanRuutu->getRivi() == siirto.getLoppuruutu().getRivi()) {
			ruutuUhattu = true;
			break;
		}
	}

	return ruutuUhattu;
}

void Asema::huolehdiKuninkaanShakeista(std::vector<Siirto>& lista, int vari)
{ 
	Ruutu kuninkaanRuutu = getKuninkaanRuutu(vari);

	// Tehd‰‰n kopioasema, jota voidaan muokata sekoittamatta oikeaa nykyist‰ asemaa
	Asema uusiAsema;
	std::vector<Siirto> siivottuSiirtolista;
	siivottuSiirtolista.reserve(200);
	Ruutu ruutu;
	Nappula* siirtyvaNappula;

	// onkoRuutuUhattu funktiota varten
	std::vector<Siirto> vastustajanSiirtolista;
	vastustajanSiirtolista.reserve(200);
	
	// K‰yd‰‰n l‰pi siirtolistan siirrot ja poistetaan sielt‰ kuninkaan shakkiin johtavat siirrot
	for (auto& siirto : lista)
	{
		uusiAsema = *this;
		uusiAsema.paivitaAsema(&siirto);

		// Onko kuninkaan siirto?
		if (siirto.onkoLyhytLinna())
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
		else if(siirto.onkoPitkaLinna())
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
			siirtyvaNappula = (*this)._lauta[siirto.getAlkuruutu().getRivi()][siirto.getAlkuruutu().getSarake()];
			if (siirtyvaNappula->getKoodi() == VK || siirtyvaNappula->getKoodi() == MK)
			{
				ruutu.setSarake(siirto.getLoppuruutu().getSarake());
				ruutu.setRivi(siirto.getLoppuruutu().getRivi());
			}
			else
			{
				// Ei ole kuninkaan siirto, jolloin kuninkaan koordinaatit on samat kuin aiemmin
				ruutu = kuninkaanRuutu;
			}
		}

		int vastustajanVari = getVastustajanSiirtovuoro();

		// Jos siirtoruutu ei aiheuta kuninkaalle uhkaa vastustajan vuorolla, se lis‰t‰‰n uuteen siirtolistaan
		if (!onkoRuutuUhattu(&ruutu, &uusiAsema, vastustajanVari, vastustajanSiirtolista))
		{
			siivottuSiirtolista.push_back(siirto);
		}
	}

	lista = siivottuSiirtolista; // !!!T‰ytyy tarkistaa, toimiiko n‰in vai antaako tyhj‰n listan eteenp‰in!!!
}

void Asema::annaLaillisetSiirrot(std::vector<Siirto>& lista)
{
	Ruutu ruutu;
	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// Siirrot valkoisille nappuloille
			if (_siirtovuoro == 0)
			{
				if (_lauta[i][j] != NULL)
				{
					if (_lauta[i][j]->getKoodi() == VS || _lauta[i][j]->getKoodi() == VT || _lauta[i][j]->getKoodi() == VR || _lauta[i][j]->getKoodi() == VL || _lauta[i][j]->getKoodi() == VD || _lauta[i][j]->getKoodi() == VK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						_lauta[i][j]->annaSiirrot(lista, &ruutu, this, _siirtovuoro);
					}
				}
			}
			else // Siirrot mustille nappuloille
			{
				if (_lauta[i][j] != NULL)
				{
					if (_lauta[i][j]->getKoodi() == MS || _lauta[i][j]->getKoodi() == MT || _lauta[i][j]->getKoodi() == MR || _lauta[i][j]->getKoodi() == ML || _lauta[i][j]->getKoodi() == MD || _lauta[i][j]->getKoodi() == MK)
					{
						ruutu.setRivi(i);
						ruutu.setSarake(j);
						_lauta[i][j]->annaSiirrot(lista, &ruutu, this, _siirtovuoro);
					}

				}
			}
		}
	}
	annaLinnoitusSiirrot(lista, _siirtovuoro);
	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}

void Asema::annaLinnoitusSiirrot(std::vector<Siirto>& lista, int vari)
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