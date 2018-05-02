#include "PhysicsObject.h"
#include "PhysicsEngine.h"

PhysicsObject::PhysicsObject()
{
	PhysicsEngine::AddPhysicsObject(this);
}

PhysicsObject::PhysicsObject(GVector Location, GVector Velocity)
{
	this->Location = Location;
	this->Velocity = Velocity;
}

void PhysicsObject::Integrate(float DeltaTime)
{
	Velocity.y -= PhysicsEngine::GetGravity() * DeltaTime;
	Location += Velocity * DeltaTime;
}

void PhysicsObject::SimulatePhysicsObject()
{

}
