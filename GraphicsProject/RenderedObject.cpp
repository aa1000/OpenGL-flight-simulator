#include "RenderedObject.h"
#include "RenderingEngine.h"

RenderedObject::RenderedObject()
	:GObject()
{
	glListIndex = -1;
	RenderingEngine::AddRenderedObject(this);
}

RenderedObject::RenderedObject(GObject* Parent)
	:GObject(Parent)
{
	glListIndex = -1;
	RenderingEngine::AddRenderedObject(this);
}

RenderedObject::RenderedObject(bool RenderInList)
	:GObject()
{
	RenderingEngine::AddRenderedObject(this);
	if(RenderInList)
		this->glListIndex = RenderingEngine::GetLastIndex();
	
}

RenderedObject::RenderedObject(GObject* Parent, bool RenderInList)
	:GObject(Parent)
{
	RenderingEngine::AddRenderedObject(this);
	if (RenderInList)
		this->glListIndex = RenderingEngine::GetLastIndex();
	
}

RenderedObject::~RenderedObject()
{
	if (glListIndex > -1)
		glDeleteLists(glListIndex, 1);
}

bool RenderedObject::Load(char* FileName)
{
	Compile();
	return true;
}

void RenderedObject::ApplyTransforms()
{
	GVector Location = GetLocation();
	GVector Rotation = GetRoation();
	GVector Scale = GetScale();

	glTranslatef(Location.x, Location.y, Location.z);
	glRotatef(GetAngle(), Rotation.x, Rotation.y, Rotation.z);
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

void RenderedObject::BindTextures()
{
}

void RenderedObject::Render()
{
	glPushMatrix();
	BindTextures();
	ApplyTransforms();
	
	if (glListIndex > -1)
		glCallList(glListIndex);
	else
		Build();

	glPopMatrix();
}
