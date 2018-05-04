#include "ResourceManager.h"

std::vector<GObject*> ResourceManager::GameObjects;
ResourceManager::~ResourceManager()
{
	for (int i = 0; i < GameObjects.size(); i++)
		delete GameObjects[i];
}

void ResourceManager::AddGameObject(GObject* GameObject)
{
	GameObjects.push_back(GameObject);
}
