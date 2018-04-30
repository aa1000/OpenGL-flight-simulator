#pragma once
#include <vector>

using namespace std;
class PhysicsObject
{
	static vector<PhysicsObject*> PhysicsObjects;

protected:

	static void AddPhysicsObject(PhysicsObject* PO);
public:
	PhysicsObject();

	void SimulatePhysicsObject();
	static void SimulateObjects();
};
