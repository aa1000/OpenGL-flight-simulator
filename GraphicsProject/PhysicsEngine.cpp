#include "PhysicsEngine.h"

//PhysicsEngine::~PhysicsEngine()
//{
//	for (int i = 0; i < PhysicsObjects.size(); i++)
//		delete PhysicsObjects[i];
//}

vector<PhysicsObjectComponent*> PhysicsEngine:: PhysicsObjectComponenets;
float PhysicsEngine::Gravity = 9;

void PhysicsEngine::AddPhysicsObject(PhysicsObjectComponent* PhysicsObjectComponent)
{
	PhysicsEngine::PhysicsObjectComponenets.push_back(PhysicsObjectComponent);
}

void PhysicsEngine::Simulate(float DeltaTime)
{
	for (int i = 0; i < PhysicsObjectComponenets.size(); i++)
		PhysicsEngine::PhysicsObjectComponenets[i]->Update(DeltaTime);
}

float PhysicsEngine::GetGravity()
{
	return PhysicsEngine::Gravity;
}
