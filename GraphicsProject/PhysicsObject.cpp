#include "PhysicsObject.h"
#include "PhysicsEngine.h"

void PhysicsObject::Init()
{
	__super::Init();
	PhysicsEngine::AddPhysicsObject(this);
	this->Mass = 1;
}

PhysicsObject::PhysicsObject()
	:GObject()
{
	Init();
}

PhysicsObject::PhysicsObject(const float& Mass)
	:GObject()
{
	Init();
	this->Mass = Mass;
}

PhysicsObject::PhysicsObject(GObject* Parent)
	:GObject(Parent)
{
	Init();

	if (Parent)
	{
		this->SetLocation(Parent->GetLocation());
		this->SetRoation(Parent->GetRoation());
	}
}

PhysicsObject::PhysicsObject(GObject* Parent, const float& Mass)
	:GObject(Parent)
{
	Init();
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

void PhysicsObject::Update(const float& DeltaTime)
{
	Integrate(DeltaTime);
	GObject* Parent = GetParent();

	if (Parent)
	{
		Parent->SetLocation(GetLocation());
		Parent->SetRoation(GetRoation());
	}
}

void PhysicsObject::Integrate(const float & DeltaTime)
{
	Acceleration.y -= PhysicsEngine::GetGravity() * Mass;
	AddRelativeVelocity(Acceleration * DeltaTime);
	AddRelativeLocation(Velocity * DeltaTime);
}

