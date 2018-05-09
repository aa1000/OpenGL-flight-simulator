#include "PlayerPlane.h"
#include "RenderingEngine.h"

PlayerPlane::PlayerPlane()
{
	PlaneSpeed = 5;

	Plane = new Mesh(true);
	Plane->SetRoation(GVector(0, 1, 0));
	Plane->Load("A6M_ZERO.obj");

	PlanePhysics = new PhysicsObject(Plane, 0.001);
	PlanePhysics->SetVelocity(GVector(PlaneSpeed, 0, 0));
	PlanePhysics->SetAngle(90);

	ActiveCamera = RenderingEngine::GetActiveCamera();
}

void PlayerPlane::MoveRight()
{
	if (ActiveCamera)
	{
		ActiveCamera->RotateRight();
		ActiveCamera->MoveRight();
	}
}

void PlayerPlane::MoveLeft()
{
	if (ActiveCamera)
	{
		ActiveCamera->RotateRight();
		ActiveCamera->MoveLeft();
	}
}

void PlayerPlane::Accelerate()
{
	if (ActiveCamera)
	{
		//ActiveCamera->MoveForward();
		
	}

	PlanePhysics->AddRelativeAcceleration(PlaneSpeed, 0, 0);
}

void PlayerPlane::Break()
{
	if (ActiveCamera)
	{
		PlanePhysics->AddRelativeAcceleration(-PlaneSpeed, 0, 0);

	}
}

void PlayerPlane::SetPlaneSpeed(const float& PlaneSpeed)
{
	this->PlaneSpeed = PlaneSpeed;
}
