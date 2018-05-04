#include "RenderedObject.h"
#include "RenderingEngine.h"

void RenderedObject::Init()
{
	__super::Init();
	glListIndex = -1;
	RenderingEngine::AddRenderedObject(this);
}

RenderedObject::RenderedObject()
	:GObject()
{
	Init();
}

RenderedObject::RenderedObject(GObject* Parent)
	:GObject(Parent)
{
	Init();
}

RenderedObject::RenderedObject(bool RenderInList)
	:GObject()
{
	Init();
	if(RenderInList)
		this->glListIndex = RenderingEngine::GetLastIndex();
}

RenderedObject::RenderedObject(GObject* Parent, bool RenderInList)
	:GObject(Parent)
{
	Init();
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
