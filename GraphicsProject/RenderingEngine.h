#pragma once
#include "RenderedObject.h"
#include <vector>


using namespace std;
class RenderingEngine
{
	static std::vector<RenderedObject*> PhysicsObjects;

	static float Gravity;
	RenderingEngine() {}

public:

	//
	//~PhysicsEngine();

	static void AddRenderedObject(RenderedObject* RenderedObject);
	static void Simulate(float DeltaTime);

	
};
