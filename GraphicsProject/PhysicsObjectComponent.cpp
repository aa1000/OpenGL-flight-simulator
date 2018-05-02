#include "PhysicsObjectComponent.h"
#include "PhysicsEngine.h"

PhysicsObjectComponent::PhysicsObjectComponent()
	:GObject()
{
	PhysicsEngine::AddPhysicsObject(this);
}

void PhysicsObjectComponent::Update(float DeltaTime)
{
	GTransform trans = GetTransform();
	PhysicsObject.Integrate(DeltaTime);
	trans.Location = this->Transform.Location;
	trans.Rotation = this->Transform.Rotation;

	GetParent()->SetTransform(trans);
}
