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
	}

};
class GObject
{
	GObject* Parent;

public:

	GTransform Transform;

	GObject();
	GObject(GObject* Parent);

	void SetParent(GObject* Parent);
	inline GObject* GetParent() const { return  Parent; }
};
