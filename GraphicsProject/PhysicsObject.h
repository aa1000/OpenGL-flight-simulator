#pragma once
#include "GVector.h"
#include "GObject.h"

class PhysicsObject : public GObject
{

	GVector Velocity;
	GVector Acceleration;

	float Mass;

protected:

	virtual void Init() override;
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

	void SetMass(const float & NewMass);
	inline float GetMass() const { return Mass; }

	virtual	void Update(const float & DeltaTime);
	void Integrate(const float & DeltaTime);
};
