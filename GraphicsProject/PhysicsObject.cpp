#include "PhysicsObject.h"
#include "PhysicsEngine.h"


PhysicsObject::PhysicsObject()
	:GObject()
{
	PhysicsEngine::AddPhysicsObject(this);
	this->Mass = 1;
}

PhysicsObject::PhysicsObject(const float& Mass)
	:GObject()
{
	PhysicsEngine::AddPhysicsObject(this);
	this->Mass = Mass;
}

PhysicsObject::PhysicsObject(GObject* Parent)
	:GObject(Parent)
{
	PhysicsEngine::AddPhysicsObject(this);
	this->Mass = 1;

	if (Parent)
	{
		this->SetLocation(Parent->GetLocation());
		this->SetRoation(Parent->GetRoation());
	}
}

PhysicsObject::PhysicsObject(GObject* Parent, const float& Mass)
	:GObject(Parent)
{
	PhysicsEngine::AddPhysicsObject(this);
	this->Mass = Mass;

	if (Parent)
	{
		this->SetLocation(Parent->GetLocation());
		this->SetRoation(Parent->GetRoation());
	}
}


void PhysicsObject::SetVelocity(const GVector& NewVelocity)
{
	this->Velocity = NewVelocity;
}

void PhysicsObject::AddRelativeVelocity(const GVector& Amount)
{
	this->Velocity += Amount;
}

void PhysicsObject::AddRelativeVelocity(const float& AmountX, const float& AmountY, const float& AmountZ)
{
	this->Velocity.AddFloatAmount(AmountX, AmountY, AmountZ);
}

void PhysicsObject::SetAcceleration(const GVector& NewAcceleration)
{
	this->Acceleration = NewAcceleration;
}

void PhysicsObject::AddRelativeAcceleration(const GVector& Amount)
{
	this->Acceleration += Amount;
}

void PhysicsObject::AddRelativeAcceleration(const float& AmountX, const float& AmountY, const float& AmountZ)
{
	this->Acceleration.AddFloatAmount(AmountX, AmountY, AmountZ);
}

void PhysicsObject::SetMass(const float& NewMass)
{
	this->Mass = Mass;
}

void PhysicsObject::Update(const float& DeltaTime)
{
	Integrate(DeltaTime);
	GObject* Parent = GetParent();

	if (Parent)
	{
		Parent->SetLocation(GetLocation());
		Parent->SetRoation(GetRoation());
		Parent->SetAngle(GetAngle());
	}
}

void PhysicsObject::Integrate(const float & DeltaTime)
{
	Acceleration.y -= PhysicsEngine::GetGravity() * Mass;
	AddRelativeVelocity(Acceleration * DeltaTime);
	AddRelativeLocation(Velocity * DeltaTime);
}

