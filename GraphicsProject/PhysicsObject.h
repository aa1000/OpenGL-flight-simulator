#pragma once
#include <vector>
#include "GVector.h"
#include "GObject.h"

using namespace std;
class PhysicsObject
{

	GVector Location;
	GVector Velocity;
	
	GVector Acceleration;

public:
	GObject* parent;
	PhysicsObject();
	PhysicsObject(GVector Location, GVector Velocity);
	
	void Integrate(float DeltaTime);

};
