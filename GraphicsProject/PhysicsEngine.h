#pragma once
#include "PhysicsObject.h"
#include <vector>
#include "PhysicsObjectComponent.h"

using namespace std;
class PhysicsEngine
{
	static vector<PhysicsObjectComponent*> PhysicsObjectComponenets;
	
	static float Gravity;
	PhysicsEngine() {}

public:

	//
	//~PhysicsEngine();

	static void AddPhysicsObject(PhysicsObjectComponent* PhysicsObject);
	static void Simulate(float DeltaTime);

	static float GetGravity();
	
};
