#pragma once
#include <vector>
#include "GVector.h"
#include "GObject.h"

using namespace std;
class PhysicsObject : public GObject
{
	static vector<PhysicsObject*> PhysicsObjects;

	GVector Location;
	GVector Velocity;
protected:

	static void AddPhysicsObject(PhysicsObject* PO);
public:
	GObject* parent;
	PhysicsObject();
	PhysicsObject(GVector Location, GVector Velocity);
	
	void Integrate(float DeltaTime);

	void SimulatePhysicsObject();
	static void SimulateObjects();
};
