#include "GMath.h"

template<> 
int GMath::RandNumRange(const int& min, const int& max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

template<>
float GMath::RandNumRange(const float & min, const float & max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	static std::uniform_real_distribution<> dis(min, max);

	return (float)dis(gen);
}