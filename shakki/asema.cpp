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

}


void Asema::paivitaAsema(Siirto *siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna


	// onko pitk� linna
	if (siirto->onkoLyhytLinna())
	{
		if (_siirtovuoro == 0)
		{
			_lauta[4][7] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[6][7] = vk; // Kuningas uudelle paikalle
			_lauta[7][7] = NULL; // Tornin paikalle tyhj�
			_lauta[5][7] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1)
		{
			_lauta[4][0] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[6][0] = mk; // Kuningas uudelle paikalle
			_lauta[7][0] = NULL; // Tornin paikalle tyhj�
			_lauta[5][0] = mt; // Torni uudelle paikalle
		}
	}
	else if (siirto->onkoPitkaLinna())
	{
		if (_siirtovuoro == 0)
		{
			_lauta[4][7] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[2][7] = vk; // Kuningas uudelle paikalle
			_lauta[0][7] = NULL; // Tornin paikalle tyhj�
			_lauta[3][7] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1)
		{
			_lauta[4][0] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[2][0] = mk; // Kuningas uudelle paikalle
			_lauta[0][0] = NULL; // Tornin paikalle tyhj�
			_lauta[3][0] = mt; // Torni uudelle paikalle
		}
	}
	else // Kaikki muut siirrot
	{
		//Ottaa siirron alkuruudussa olleen nappulan talteen
		Nappula* nappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL;

	}

		//Ottaa siirron alkuruudussa olleen nappulan talteen 


		//Laittaa talteen otetun nappulan uuteen ruutuun


		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)

		// Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)

	//p�ivitet��n _siirtovuoro
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
L�hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv� ett� kunigas g1 tai b1/c1
Loppupeliss� vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est�m�ss� vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki� linjoja daami, torni ja l�hetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai v�hemm�n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

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


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
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
	
	// Rekursion kantatapaus 2: katkaisusyvyydess�
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	
}
