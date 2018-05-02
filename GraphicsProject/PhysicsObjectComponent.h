#pragma once
#include "GObject.h"
#include "PhysicsObject.h"

class PhysicsObjectComponent : public GObject
{

	PhysicsObject* physicsObject;
public:

	PhysicsObjectComponent();

	void Update(float DeltaTime);
	
};
