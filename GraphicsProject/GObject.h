#pragma once
#include "GVector.h"


struct GTransform
{

public:
	GVector Location, Rotation, Scale;
	GTransform()
	{
		
	}
	GTransform(GVector Location, GVector Rotation, GVector Scale)
	{
		this->Location = Location;
		this->Rotation = Rotation;
		this->Scale = Scale;
	}
	GTransform(const GTransform & Other)
	{
		this->Location = Other.Location;
		this->Rotation = Other.Rotation;
		this->Scale = Other.Scale;

	}
	GTransform& operator=(const GTransform& Other)
	{
		this->Location = Other.Location;
		this->Rotation = Other.Rotation;
		this->Scale = Other.Scale;

		return *this;
	}

};
class GObject
{
	GObject* Parent;
	GTransform Transform;

protected:

	virtual void Init();
public:

	

	GObject();
	GObject(GObject* Parent);

	void SetParent(GObject* Parent);
	inline GObject* GetParent() const { return  Parent; }

	inline GTransform GetTransform() { return Transform; }
	inline GVector GetLocation() { return Transform.Location; }
	inline GVector GetRoation() { return Transform.Rotation; }
	inline GVector GetScale() { return Transform.Scale; }
	
	void SetTransform(const GTransform & NewTransform);
	void SetTransform(const GVector & Location, const GVector & Rotation, const GVector & Scale);
	void SetLocation(const GVector & NewLocation);
	void SetRoation(const GVector & NewRotaion);
	void SetScale(const GVector & Scale);
	void SetScale(const float & NewScale);
	void MultiplyScale(const float & Mul);

	void AddRelativeLocation(const GVector & Amount);
	void AddRelativeLocation(const float & AmountX, const float & AmountY, const float & AmountZ);

	void AddRelativeRotation(const GVector & Amount);
	void AddRelativeRotation(const float & AmountX, const float & AmountY, const float & AmountZ);

	void AddRelativeScale(const GVector & Amount);
	void AddRelativeScale(const float & AmountX, const float & AmountY, const float & AmountZ);
	
	
};
