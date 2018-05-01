#pragma once
#include "PhysicsObject.h"
#include <vector>

using namespace std;
static class PhysicsEngine
{
	static vector<PhysicsObject*> PhysicsObjects;

public:

	//PhysicsEngine();
	//~PhysicsEngine();

	static void AddPhysicsObject(PhysicsObject* PhysicsObject);
	static void Simulate(float DeltaTime);

	
};
