#include "peli.h"

using namespace std;


Peli::Peli(int ihmisenVari)
{
	if (ihmisenVari == 0)
	{
		_koneenVari = 1;
	}
	else
	{
		_koneenVari = 0;
	}
}


int Peli::getKoneenVari(){
	return _koneenVari;
}
