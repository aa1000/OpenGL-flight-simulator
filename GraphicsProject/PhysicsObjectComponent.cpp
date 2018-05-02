#include "PhysicsObjectComponent.h"
#include "PhysicsEngine.h"

PhysicsObjectComponent::PhysicsObjectComponent()
	:GObject()
{
	physicsObject = new PhysicsObject();
	PhysicsEngine::AddPhysicsObject(this);
}

void PhysicsObjectComponent::Update(float DeltaTime)
{
	GTransform trans = GetTransform();
	physicsObject->Integrate(DeltaTime);
	trans.Location = physicsObject->Location;
	//trans.Rotation = physicsObject->Rotation;

	GetParent()->SetTransform(trans);
}
