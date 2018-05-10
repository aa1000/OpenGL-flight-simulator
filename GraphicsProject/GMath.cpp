#include "GMath.h"
#include "GVector.h"

template<> 
int GMath::RandNumRange(const int& min, const int& max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

template<>
float GMath::RandNumRange(const float & min, const float & max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);

	return (float)dis(gen);
}

template<>
GVector GMath::RandNumRange(const GVector & min, const GVector & max)
{
	GVector out;
	out.x = GMath::RandNumRange<float>(min.x, max.x);
	out.y = GMath::RandNumRange<float>(min.y, max.y);
	out.z = GMath::RandNumRange<float>(min.z, max.z);
	
	return out;
}


template <typename T>
T GMath::Clamp(const T & value, const T& min, const T& max)
{
	if (value > max)
		return  max;
	else if (value < min)
		return min;
	else
		return value;
}


template <>
GVector GMath::Clamp(const GVector & value, const GVector& min, const GVector& max)
{
	if (value.x > max.x && value.y > max.y && value.z > max.z)
		return  max;
	else if (value.x < min.x && value.y < min.y && value.z  < min.z)
		return min;
	else
		return value;
}