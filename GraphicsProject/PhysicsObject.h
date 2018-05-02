#pragma once
#include <vector>
#include "GVector.h"

using namespace std;
class PhysicsObject
{

	

public:

	GVector Location;
	GVector Velocity;

	GVector Acceleration;

	PhysicsObject();
	PhysicsObject(GVector Location, GVector Velocity);
	
	void Integrate(float DeltaTime);
};
