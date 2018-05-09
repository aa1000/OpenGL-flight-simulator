#include "PhysicsEngine.h"

//PhysicsEngine::~PhysicsEngine()
//{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		delete PhysicsObjects[i];
//}

vector<PhysicsObject*> PhysicsEngine:: PhysicsObjects;
float PhysicsEngine::Gravity = 1;

void PhysicsEngine::AddPhysicsObject(PhysicsObject* PhysicsObjectComponent)
{
	PhysicsEngine::PhysicsObjects.push_back(PhysicsObjectComponent);
}

void PhysicsEngine::Simulate(float DeltaTime)
{
	for (int i = 0; i < PhysicsObjects.size(); i++)
		if(PhysicsEngine::PhysicsObjects[i])
			PhysicsEngine::PhysicsObjects[i]->Update(DeltaTime);
}

float PhysicsEngine::GetGravity()
{
	return PhysicsEngine::Gravity;
}
