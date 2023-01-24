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

Torni::Torni(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) 
{

}

Ratsu::Ratsu(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) 
{

}

Lahetti::Lahetti(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi)
{

}

Daami::Daami(std::wstring unicode, int vari, int koodi) :
	Nappula(unicode, vari, koodi), Lahetti(unicode, vari, koodi), Torni(unicode, vari, koodi) 
{

}

Kuningas::Kuningas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi)
{

}

Sotilas::Sotilas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) 
{

}



// Funktiot
void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
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
