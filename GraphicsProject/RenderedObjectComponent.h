#pragma once
#include "RenderedObject.h"

class RenderedObjectComponent : public GObject
{
	RenderedObject* renderedobject;
public:

	RenderedObjectComponent();
	~RenderedObjectComponent();
	void Load(char* FileName);
	void Render();

	
};
