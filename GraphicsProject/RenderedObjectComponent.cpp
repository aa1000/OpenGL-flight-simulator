#include "RenderedObjectComponent.h"
#include "RenderingEngine.h"

template <class T>
RenderedObjectComponent<T>::RenderedObjectComponent(char* FileName)
	:GObject()
{
	renderedobject = new T(RenderingEngine::GetLastIndex());
	renderedobject->Load(FileName);

	SetScale(GVector::StaticInit(1));
	renderedobject->Location = GetLocation();
	renderedobject->Rotation = GetRoation();
	renderedobject->Scale = GetScale();

	RenderingEngine::AddRenderedObject(this);
}

template <class T>
RenderedObjectComponent<T>::RenderedObjectComponent(GObject* Parent, char* FileName)
	:GObject(Parent)
{
	renderedobject = new T(RenderingEngine::GetLastIndex());
	renderedobject->Load(FileName);

	SetScale(GVector::StaticInit(1));
	renderedobject->Location = GetLocation();
	renderedobject->Rotation = GetRoation();
	renderedobject->Scale = GetScale();

	RenderingEngine::AddRenderedObject(this);
}

template <class T>
RenderedObjectComponent<T>::~RenderedObjectComponent()
{
	delete renderedobject;
}

template <class T>
void RenderedObjectComponent<T>::Render()
{
	GObject* P = GetParent();
	if (P)
	{
		renderedobject->Location = P->GetLocation();
		renderedobject->Rotation = P->GetRoation();
		renderedobject->Scale = P->GetScale();
	}
	renderedobject->Render();
}
