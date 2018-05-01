#include "PhysicsEngine.h"

//PhysicsEngine::~PhysicsEngine()
//{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		delete PhysicsObjects[i];
//}

void PhysicsEngine::AddPhysicsObject(PhysicsObject* PhysicsObject)
{
	PhysicsEngine::PhysicsObjects.push_back(PhysicsObject);
}

void PhysicsEngine::Simulate(float DeltaTime)
{
	for (int i = 0; i < PhysicsObjects.size(); i++)
		PhysicsEngine::PhysicsObjects[i]->Integrate(DeltaTime);
}
