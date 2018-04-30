#include "RenderedObject.h"

RenderedObject::RenderedObject()
{
	glListIndex = -1;
	Scale.init(1);
}

RenderedObject::RenderedObject(int glListIndex)
{
	this->glListIndex = glListIndex;
}

RenderedObject::~RenderedObject()
{
	if (glListIndex > -1)
		glDeleteLists(glListIndex, 1);
}

void RenderedObject::SetScale(float NewScale)
{
	Scale.x = Scale.y = Scale.z = NewScale;
}

bool RenderedObject::Load(char* FileName)
{
	Compile();
	return true;
}

void RenderedObject::ApplyTransforms()
{
	glTranslatef(Location.x, Location.y, Location.z);
	glRotatef(1.0f, Rotation.x, Rotation.y, Rotation.z);
	glScalef(Scale.x, Scale.y, Scale.z);
}

void RenderedObject::Build()
{
}


void RenderedObject::Compile()
{
	if (glListIndex > -1)
	{
		glNewList(glListIndex, GL_COMPILE);
		Build();
		glEndList();
	}
}

void RenderedObject::Render()
{
	glPushMatrix();
	ApplyTransforms();
	
	if (glListIndex > -1)
		glCallList(glListIndex);
	else
		Build();

	glPopMatrix();
}
