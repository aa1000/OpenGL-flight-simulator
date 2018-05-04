﻿#include "GObject.h"
#include "ResourceManager.h"

void GObject::Init()
{
	ResourceManager::AddGameObject(this);
	SetScale(GVector::StaticInit(1));
}

GObject::GObject()
{
	Parent = nullptr;
}

GObject::GObject(GObject* Parent)
{
	this->Parent = Parent;
}

void GObject::SetParent(GObject* Parent)
{
	this->Parent = Parent;
}

void GObject::SetTransform(const GTransform& NewTransform)
{
	this->Transform = NewTransform;
}

void GObject::SetTransform(const GVector& Location, const GVector& Rotation, const GVector& Scale)
{
	this->Transform.Location = Location;
	this->Transform.Rotation = Rotation;
	this->Transform.Scale = Scale;
}

void GObject::SetLocation(const GVector& NewLocation)
{
	this->Transform.Location = NewLocation;
}

void GObject::SetRoation(const GVector& NewRotaion)
{
	this->Transform.Rotation = NewRotaion;
}

void GObject::SetScale(const GVector& Scale)
{
	this->Transform.Scale = Scale;
}

void GObject::SetScale(const float & NewScale)
{
	this->Transform.Scale.x = this->Transform.Scale.y = this->Transform.Scale.z = NewScale;
}

void GObject::MultiplyScale(const float& Mul)
{
	this->Transform.Scale *= Mul;
}

void GObject::AddRelativeLocation(const GVector& Amount)
{
	this->Transform.Location += Amount;
}

void GObject::AddRelativeLocation(const float& AmountX, const float& AmountY, const float& AmountZ)
{
	this->Transform.Location.AddFloatAmount(AmountX, AmountY, AmountZ);
}

void GObject::AddRelativeRotation(const GVector& Amount)
{
	this->Transform.Rotation += Amount;
}

void GObject::AddRelativeRotation(const float& AmountX, const float& AmountY, const float& AmountZ)
{
	this->Transform.Rotation.AddFloatAmount(AmountX, AmountY, AmountZ);
}

void GObject::AddRelativeScale(const GVector& Amount)
{
	this->Transform.Scale += Amount;
}

void GObject::AddRelativeScale(const float& AmountX, const float& AmountY, const float& AmountZ)
{
	this->Transform.Scale.AddFloatAmount(AmountX, AmountY, AmountZ);
}
