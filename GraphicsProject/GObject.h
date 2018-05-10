#pragma once
#include "GVector.h"


struct GTransform
{

public:
	GVector Location, Rotation, Scale;
	float Angle;
	GTransform()
	{
		this->Scale = GVector::StaticInit(1);
		Angle = 0;
	}
	GTransform(GVector Location, GVector Rotation, GVector Scale, float Angle)
	{
		this->Location = Location;
		this->Rotation = Rotation;
		this->Scale = Scale;
		this->Angle = Angle;
	}
	GTransform(const GTransform & Other)
	{
		this->Location = Other.Location;
		this->Rotation = Other.Rotation;
		this->Scale = Other.Scale;
		this->Angle = Other.Angle;
	}
	GTransform& operator=(const GTransform& Other)
	{
		this->Location = Other.Location;
		this->Rotation = Other.Rotation;
		this->Scale = Other.Scale;
		this->Angle = Other.Angle;

		return *this;
	}

};
class GObject
{
	GObject* Parent;
	GTransform Transform;

public:

	bool UpdateObject;
	

	GObject();
	GObject(GObject* Parent);

	void SetParent(GObject* Parent);
	inline GObject* GetParent() const { return  Parent; }

	inline GTransform GetTransform() { return Transform; }
	inline GVector GetLocation() { return Transform.Location; }
	inline GVector GetRoation() { return Transform.Rotation; }
	inline GVector GetScale() { return Transform.Scale; }
	inline float GetAngle() { return Transform.Angle; }
	
	void SetTransform(const GTransform & NewTransform);
	void SetTransform(const GVector & Location, const GVector & Rotation, const GVector & Scale, const float & Angle);
	void SetLocation(const GVector & NewLocation);
	void SetRoation(const GVector & NewRotaion);
	void SetScale(const GVector & Scale);
	void SetScale(const float & NewScale);
	void MultiplyScale(const float & Mul);
	void SetAngle(const float & NewAngle);

	void AddRelativeLocation(const GVector & Amount);
	void AddRelativeLocation(const float & AmountX, const float & AmountY, const float & AmountZ);

	void AddRelativeRotation(const GVector & Amount);
	void AddRelativeRotation(const float & AmountX, const float & AmountY, const float & AmountZ);

	void AddRelativeScale(const GVector & Amount);
	void AddRelativeScale(const float & AmountX, const float & AmountY, const float & AmountZ);
	
	
};
