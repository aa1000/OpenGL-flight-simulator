#pragma once
#include "RenderedObjectComponent.h"
#include <vector>

class Camera;

using namespace std;
class RenderingEngine
{
	static vector<RenderedObject*> RenderedObjects;

	RenderingEngine() {}

	static Camera* ActiveCamera;

public:

	//
	//~PhysicsEngine();

	inline static Camera* GetActiveCamera() { return ActiveCamera; }
	static void SetActiveCamera(Camera* ActiveCamera);
	static void AddRenderedObject(RenderedObject* RenderedObject);
	static void Render();
	static int GetLastIndex();
	
};
