#pragma once
#include "PhysicsObject.h"
#include <vector>

using namespace std;
class PhysicsEngine
{
	vector<PhysicsObject*> PhysicsObjects;

public:

	~PhysicsEngine();

	void AddPhysicsObject(PhysicsObject* PhysicsObject);
	void Simulate(float DeltaTime);

	
};
