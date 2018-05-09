#pragma once
#include "GVector.h"
#include "GL/freeglut.h"
#include "GObject.h"

class RenderedObject : public GObject
{
	int glListIndex;

public:
	


	RenderedObject();
	RenderedObject(GObject* Parent);
	RenderedObject(bool RenderInList);
	RenderedObject(GObject* Parent, bool RenderInList);
	~RenderedObject();

	
	virtual bool Load(char* FileName);
	void ApplyTransforms();
	virtual void Build();
	virtual void Compile();
	virtual void BindTextures();
	virtual void Render();
};
