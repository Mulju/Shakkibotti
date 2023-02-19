#include "Ajastin.h"
#include <iostream>

Ajastin::Ajastin(std::wstring nimi)
{
	_aloitusAika = Kello::now();
	_nimi = nimi;
}

Ajastin::~Ajastin()
{
	Kello::time_point lopetusAika = Kello::now();
	std::chrono::duration<double, std::milli> kesto = lopetusAika - _aloitusAika;
	std::wcout << _nimi << L" : " << kesto.count() << L" ms\n";
}