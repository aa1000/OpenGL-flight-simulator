#include "RenderedObjectComponent.h"
#include "RenderingEngine.h"

RenderedObjectComponent::RenderedObjectComponent()
{
	renderedobject = new RenderedObject(RenderingEngine::GetLastIndex());
	RenderingEngine::AddRenderedObject(this);
}

RenderedObjectComponent::~RenderedObjectComponent()
{
	delete renderedobject;
}

void RenderedObjectComponent::Render()
{
	renderedobject->Render();
}
