#include "GObject.h"

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
