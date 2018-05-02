#pragma once
#include "RenderedObjectComponent.h"
#include <vector>



using namespace std;
class RenderingEngine
{
	static vector<RenderedObjectComponent*> RenderedObjectsComponents;

	RenderingEngine() {}

public:

	//
	//~PhysicsEngine();

	static void AddRenderedObject(RenderedObjectComponent* RenderedObject);
	static void Render(float DeltaTime);

	
};
