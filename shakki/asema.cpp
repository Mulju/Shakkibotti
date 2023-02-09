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

	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.
	//kaksoisaskelSarakkeella = -1;


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (_siirtovuoro == 0 )
		{
			_lauta[7][4] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[7][6] = vk; // Kuningas uudelle paikalle
			_lauta[7][7] = NULL; // Tornin paikalle tyhj�
			_lauta[7][5] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1 )
		{
			_lauta[0][4] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[0][6] = mk; // Kuningas uudelle paikalle
			_lauta[0][7] = NULL; // Tornin paikalle tyhj�
			_lauta[0][5] = mt; // Torni uudelle paikalle
		}
	}
	else if (siirto->onkoPitkaLinna()) // onko pitk� linna
	{
		if (_siirtovuoro == 0)
		{
			_lauta[7][4] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[7][2] = vk; // Kuningas uudelle paikalle
			_lauta[7][0] = NULL; // Tornin paikalle tyhj�
			_lauta[7][3] = vt; // Torni uudelle paikalle
		}
		if (_siirtovuoro == 1 )
		{
			_lauta[0][4] = NULL; // Kuninkaan paikalle tyhj�
			_lauta[0][2] = mk; // Kuningas uudelle paikalle
			_lauta[0][0] = NULL; // Tornin paikalle tyhj�
			_lauta[0][3] = mt; // Torni uudelle paikalle
		}
	}
	else // Kaikki muut siirrot
	{
		//Ottaa siirron alkuruudussa olleen nappulan talteen
		Nappula* nappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];

		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		
		// Tarkistetaan, onko ohestaly�nti. Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.
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

		//// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		
		// Maikan ylempi kommentti on h�mment�v�. Luullakseni t�m� korottaa sotilaan oikein
		if ((siirto->getLoppuruutu().getRivi() == 7 || siirto->getLoppuruutu().getRivi() == 0) &&
			(nappula == ms || nappula == vs))
		{
			// Siirron loppuruutu on laudan p��ty, sek� nappula on sotilas. Siirrolla on korotus arvo
			// Asetetaan nappula osoitin osoittamaan korotusarvon omaiseen nappulaan
			nappula = siirto->_miksikorotetaan;
			// P�ivitet��n laudalle oikean tyyppinen nappula
			_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		}

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL;

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
		if (nappula == mk) {
			_onkoMustaKuningasLiikkunut = true;
		}
		if (nappula == vk) {
			_onkoValkeaKuningasLiikkunut = true;
		}

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)
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
	double laudanArvo = 0;
	// Heinin kommentti: kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta

	//1. Nappuloiden arvo
	laudanArvo += laskeNappuloidenArvo(getSiirtovuoro());
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
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
		// Siirtolista on tyhj�, tilanne on joko matti tai patti
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

		// Siirtoja on, k�yd��n kaikki l�pi
		for (auto &siirto : siirtoLista)
		{
			// T�ytyy luoda for loopissa aina uusi asema, joka sy�tet��n syvemm�lle rekursiossa
			Asema rekursioAsema(*this);

			rekursioAsema.paivitaAsema(&siirto);
			miniPaluu = rekursioAsema.mini(syvyys - 1);
			if (miniPaluu._evaluointiArvo > laudanArvo)
			{
				// Voisi kirjoittaa my�s kopiokonstruktorin MinMaxPaluulle
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


MinMaxPaluu Asema::mini(int syvyys) 
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
		// Siirtolista on tyhj�, tilanne on joko matti tai patti
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

		// Siirtoja on, k�yd��n kaikki l�pi
		for (auto& siirto : siirtoLista)
		{
			// T�ytyy luoda for loopissa aina uusi asema, joka sy�tet��n syvemm�lle rekursiossa
			Asema rekursioAsema(*this);

			rekursioAsema.paivitaAsema(&siirto);
			maxiPaluu = rekursioAsema.maxi(syvyys - 1);
			if (maxiPaluu._evaluointiArvo < laudanArvo)
			{
				// Voisi kirjoittaa my�s kopiokonstruktorin MinMaxPaluulle
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
	
	// K�yd��n vastustajan siirtolista l�pi ja tarkistetaan, l�ytyyk� kuninkaan ruutu
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
	
	// Teht�isiink� t�m� annaLaillisetSiirrot-funkkarissa?
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

	// Tehd��n kopioasema, jota voidaan muokata sekoittamatta oikeaa nykyist� asemaa
	Asema uusiAsema;
	std::list<Siirto> siivottuSiirtolista;
	Ruutu ruutu;
	
	// K�yd��n l�pi siirtolistan siirrot ja poistetaan sielt� kuninkaan shakkiin johtavat siirrot
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
			if (uusiAsema.getSiirtovuoro() == 0) {
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
			if (uusiAsema.getSiirtovuoro() == 0) {
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

		// Jos siirtoruutu ei aiheuta kuninkaalle uhkaa vastustajan vuorolla, se lis�t��n uuteen siirtolistaan
		if (!onkoRuutuUhattu(&ruutu, &uusiAsema, vastustajanVari))
		{
			siivottuSiirtolista.push_back(*siirto);
		}
	}

	lista = siivottuSiirtolista; // !!!T�ytyy tarkistaa, toimiiko n�in vai antaako tyhj�n listan eteenp�in!!!
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

		//pitk�n valkoisen linnotuksen lis��minen lailliseksi siirroksi
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

		//lyhyt valkoisen linnotuksen lis��minen lailliseksi siirroksi
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

		//pitk�n musta linnotuksen lis��minen lailliseksi siirroksi
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

		//lyhyt musta linnotuksen lis��minen lailliseksi siirroksi
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