#include "PhysicsObject.h"

void PhysicsObject::AddPhysicsObject(PhysicsObject* PO)
{
	//PhysicsObject::PhysicsObjects.push_back(PO);
}

PhysicsObject::PhysicsObject()
{
	PhysicsObject::AddPhysicsObject(this);
	Gravity = 9.0;
}

PhysicsObject::PhysicsObject(GVector Location, GVector Velocity)
{
	this->Location = Location;
	this->Velocity = Velocity;
}

void PhysicsObject::Integrate(float DeltaTime)
{
	Velocity.y -= Gravity * DeltaTime;
	Location += Velocity * DeltaTime;
}

void PhysicsObject::SimulatePhysicsObject()
{

}

void PhysicsObject::SimulateObjects()
{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		PhysicsObjects[i]->SimulatePhysicsObject();
}
