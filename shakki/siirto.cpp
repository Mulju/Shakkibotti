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

bool Siirto::operator<(const Siirto& rhs) const
{
	if (this->_onSyonti == rhs._onSyonti)
	{
		return false;
	}

	if (this->_onSyonti == true && rhs._onSyonti == false)
	{
		return true;
	}

	if (this->_onSyonti == false && rhs._onSyonti == true)
	{
		return false;
	}
}