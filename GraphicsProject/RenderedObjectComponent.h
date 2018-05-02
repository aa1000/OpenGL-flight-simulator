#pragma once
#include "RenderedObject.h"

class RenderedObjectComponent : public GObject
{
	RenderedObject renderedobject;
public:

	RenderedObjectComponent();
	void Render();

	
};
