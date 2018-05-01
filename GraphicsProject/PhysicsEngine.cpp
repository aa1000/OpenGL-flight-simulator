#include "PhysicsEngine.h"

//PhysicsEngine::~PhysicsEngine()
//{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		delete PhysicsObjects[i];
//}

void PhysicsEngine::AddPhysicsObject(PhysicsObject* PhysicsObject)
{
	PhysicsObjects.push_back(PhysicsObject);
}

void PhysicsEngine::Simulate(float DeltaTime)
{
	for (int i = 0; i < PhysicsObjects.size(); i++)
		PhysicsObjects[i]->Integrate(DeltaTime);
}
