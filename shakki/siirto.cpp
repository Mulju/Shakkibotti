#include "siirto.h"


Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu, bool onSyonti)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_lyhytLinna = false;
	_pitkaLinna = false;
	_onSyonti = onSyonti;
}


Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) 
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
	_onSyonti = true;
}


Ruutu Siirto::getAlkuruutu()
{
	return _alkuRuutu;
}


Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}


bool Siirto::onkoLyhytLinna() 
{
	return _lyhytLinna;
}


bool Siirto::onkoPitkaLinna() 
{
	return _pitkaLinna;
}
