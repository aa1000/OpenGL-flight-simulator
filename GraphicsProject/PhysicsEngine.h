#pragma once
#include "PhysicsObject.h"
#include <vector>

using namespace std;
class PhysicsEngine
{
	static vector<PhysicsObject*> PhysicsObjects;
	
	static float Gravity;
	PhysicsEngine() {}

public:

	//
	//~PhysicsEngine();

	static void AddPhysicsObject(PhysicsObject* PhysicsObject);
	static void Simulate(float DeltaTime);

	static float GetGravity();
	
};
