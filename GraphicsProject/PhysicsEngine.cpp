#include "PhysicsEngine.h"

//PhysicsEngine::~PhysicsEngine()
//{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		delete PhysicsObjects[i];
//}

vector<PhysicsObject*> PhysicsEngine:: PhysicsObjects;
float PhysicsEngine::Gravity = 9;

void PhysicsEngine::AddPhysicsObject(PhysicsObject* PhysicsObject)
{
	PhysicsEngine::PhysicsObjects.push_back(PhysicsObject);
}

void PhysicsEngine::Simulate(float DeltaTime)
{
	for (int i = 0; i < PhysicsObjects.size(); i++)
		PhysicsEngine::PhysicsObjects[i]->Integrate(DeltaTime);
}

float PhysicsEngine::GetGravity()
{
	return PhysicsEngine::Gravity;
}
