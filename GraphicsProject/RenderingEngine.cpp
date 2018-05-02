#include "RenderingEngine.h"


vector<RenderedObjectComponent*> RenderingEngine::RenderedObjectsComponents;


void RenderingEngine::AddRenderedObject(RenderedObjectComponent* RenderedObject)
{
	RenderedObjectsComponents.push_back(RenderedObject);
}
