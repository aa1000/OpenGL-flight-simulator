#include "RenderingEngine.h"
#include "Camera.h"

vector<RenderedObject*> RenderingEngine::RenderedObjects;
Camera* RenderingEngine::ActiveCamera;

void RenderingEngine::SetActiveCamera(Camera* ActiveCamera)
{
	RenderingEngine::ActiveCamera = ActiveCamera;
}

void RenderingEngine::AddRenderedObject(RenderedObject* RenderedObject)
{
	RenderedObjects.push_back(RenderedObject);
}

void RenderingEngine::Render()
{

	ActiveCamera->RenderLookAt();

	for (int i = 0; i < RenderedObjects.size(); i++)
		if(RenderedObjects[i])
			RenderedObjects[i]->Render();

}

int RenderingEngine::GetLastIndex()
{
	return  RenderedObjects.size();
}
