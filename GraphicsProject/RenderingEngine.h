#pragma once
#include "RenderedObjectComponent.h"
#include <vector>



using namespace std;
class RenderingEngine
{
	static vector<RenderedObject*> RenderedObjects;

	RenderingEngine() {}

public:

	//
	//~PhysicsEngine();

	static void AddRenderedObject(RenderedObject* RenderedObject);
	static void Render();
	static int GetLastIndex();
	
};
