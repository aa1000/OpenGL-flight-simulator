#pragma once
#include "GObject.h"
#include <vector>

class ResourceManager
{
	static std::vector<GObject*> GameObjects;
public:
	
	~ResourceManager();
	static void AddGameObject(GObject* GameObject);
};
