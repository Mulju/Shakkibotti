#pragma once
#include <chrono>
#include <string>

using namespace std;

class Ajastin
{
	using Kello = std::chrono::steady_clock;

public:
	Kello::time_point _aloitusAika;
	std::wstring _nimi;

	Ajastin(std::wstring nimi);

	~Ajastin();
};

