#pragma once
#include "RenderedObject.h"

template <class T>
class RenderedObjectComponent : public GObject
{
	RenderedObject* renderedobject;
public:

	RenderedObjectComponent(char* FileName);
	RenderedObjectComponent(GObject* Parent, char* FileName);
	~RenderedObjectComponent();
	//void Load(char* FileName);
	void Render();

	
};
