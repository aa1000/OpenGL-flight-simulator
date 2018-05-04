#include "RenderingEngine.h"


vector<RenderedObject*> RenderingEngine::RenderedObjects;


void RenderingEngine::AddRenderedObject(RenderedObject* RenderedObject)
{
	RenderedObjects.push_back(RenderedObject);
}

void RenderingEngine::Render()
{
	for (int i = 0; i < RenderedObjects.size(); i++)
		RenderedObjects[i]->Render();
}

int RenderingEngine::GetLastIndex()
{
	return  RenderedObjects.size();
}
