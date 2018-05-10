#pragma once
#include "GVector.h"
#include "GObject.h"

class PhysicsObject : public GObject
{

	GVector Velocity;
	GVector Acceleration;
	float AngularVelocity;

	float Mass;

public:


	PhysicsObject();
	PhysicsObject(const float & Mass);
	PhysicsObject(GObject* Parent);
	PhysicsObject(GObject* Parent, const float & Mass);
	
	inline GVector GetVelocity() const { return Velocity; }
	inline GVector GetAcceleration() const { return Acceleration; }

	void SetVelocity(const GVector & NewVelocity);
	void AddRelativeVelocity(const GVector & Amount);
	void AddRelativeVelocity(const float & AmountX, const float & AmountY, const float & AmountZ);

	void SetAcceleration(const GVector & NewAcceleration);
	void AddRelativeAcceleration(const GVector & Amount);
	void AddRelativeAcceleration(const float & AmountX, const float & AmountY, const float & AmountZ);

	void SetAngularVelocity(const float & AngularVelocity);
	void AddRelativeAngularVelocity(const float & AngularVelocity);
	inline float GetAngularVelocity() const { return AngularVelocity; }

	void SetMass(const float & NewMass);
	inline float GetMass() const { return Mass; }

	virtual	void Update(const float & DeltaTime);
	void Integrate(const float & DeltaTime);
};
