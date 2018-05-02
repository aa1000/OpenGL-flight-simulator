#include "RenderedObjectComponent.h"
#include "RenderingEngine.h"

RenderedObjectComponent::RenderedObjectComponent()
{
	RenderingEngine::AddRenderedObject(this);
}

void RenderedObjectComponent::Render()
{
	renderedobject.Render();
}
