#pragma once
#include <math.h>
#include <random>
class GMath
{
public:
	template <typename T>
	static T RandNumRange(const T & min, const T & max);
	template <typename T>
	static T Clamp(const T & value, const T & min, const T & max);
	
};



