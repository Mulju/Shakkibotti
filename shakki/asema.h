#pragma once

#include <list>
#include <string>
#include "minmaxpaluu.h"
#include "siirto.h"
#include <vector>
#include <unordered_map>


// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell‰ Nappula-osoittimia ilman,
// ett‰ nappula.h -tiedostoa t‰ytyy includoida.
class Nappula;


// Asema sis‰lt‰‰ kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, siirtovuoro, linnoitusoikeudet jne.).
class Asema
{

public:
	// Pelilauta sis‰lt‰‰ osoittimet kunkin ruudun nappula-olioon (nullptr/NULL/0 jos ruutu on tyhj‰).
	// Public-m‰‰reell‰, koska t‰t‰ k‰ytet‰‰n paljon muualla.
	Nappula* _lauta[8][8];

	// Nappula-oliot. Huomaa, ett‰ samaa nappulaa voidaan k‰ytt‰‰ useissa eri ruuduissa.
	// M‰‰ritelty static-m‰‰reell‰, joten nappulat ovat kaikkien lauta-olioiden "yhteisk‰ytˆss‰"
	// (suorituskyvyn vuoksi).
	static Nappula *vk, *vd, *vt, *vl, *vr, *vs;	// Valkeat nappulat.
	static Nappula *mk, *md, *mt, *ml, *mr, *ms;	// Mustat nappulat.

	// Ohestalyˆnti‰ varten (-1 = sotilaan kaksoisaskelta ei tapahtunut edellisell‰ siirrolla).
	int kaksoisaskelSarakkeella = -1;

	Asema();												// Asettaa alkuaseman.
	void paivitaAsema(Siirto*);								// P‰ivitt‰‰ aseman annetulla siirrolla.
	double evaluoi();										// Aseman numeerinen arviointi.
	MinMaxPaluu alphaBetaMaxi(int alpha, int beta, int syvyys);					// Minimax (max:n siirtovuoro).
	MinMaxPaluu alphaBetaMini(int alpha, int beta, int syvyys);					// Minimax (min:n siirtovuoro).
	MinMaxPaluu minimax(int syvyys);						// Minimax-algoritmi.
	void annaLaillisetSiirrot(std::vector<Siirto>& lista);	// Siirtogeneraattori.
	int getSiirtovuoro();									// Palauttaa siirtovuoron.
	int getVastustajanSiirtovuoro();
	void setSiirtovuoro(int);								// Asettaa siirtovuoron.
	bool getOnkoValkeaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoMustaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoValkeaDTliikkunut();						// Linnoittuminen mahdollista?
	bool getOnkoValkeaKTliikkunut();						// Linnoittuminen mahdollista?
	bool getOnkoMustaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaKTliikkunut();							// Linnoittuminen mahdollista?
	
private:

	// Lis‰informaatio pelitilanteesta.
	int _siirtovuoro;					// 0 = valkea, 1 = musta.
	bool _onkoValkeaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoMustaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoValkeaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisivustan torni on liikkunut.
	bool _onkoValkeaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	bool _onkoMustaDTliikkunut;			// Linnoitus ei ole sallittu, jos daamisuvustan torni on liikkunut.	
	bool _onkoMustaKTliikkunut;			// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	bool _onkoValkeaDLaudalla;
	bool _onkoMustaDLaudalla;
	int _valkoisetUpseerit;
	int _mustatUpseerit;

	double laskeNappuloidenArvo(int);
	bool onkoKeskiVaiLoppupeli(int);
	double nappuloitaKeskella(int);
	double linjat(int);
	bool onkoRuutuUhattu(Ruutu*, Asema* asema, int vastustajanVari);
	void annaLinnoitusSiirrot(std::vector<Siirto>& lista, int vari);
	Ruutu getKuninkaanRuutu(int vari);

	// Karsii siirrot, jotka j‰tt‰v‰t oman K:n shakkiin.
	void huolehdiKuninkaanShakeista(std::vector<Siirto>& lista, int vari);
};