#pragma once
#include "GObject.h"
#include "PhysicsObject.h"

class PhysicsObjectComponent : public GObject
{

	PhysicsObject PhysicsObject;
public:

	PhysicsObjectComponent();

	void Update(float DeltaTime);
	
};
