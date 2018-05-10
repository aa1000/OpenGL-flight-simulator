#include "PlayerPlane.h"
#include "GMath.h"
#include "SphereParticleEmitter.h"

PlayerPlane::PlayerPlane()
{
	PlaneSpeed = 5;
	Step = 0.5;

	Plane = new Mesh(true);
	Plane->SetRoation(GVector(0, 1, 0));
	Plane->Load("A6M_ZERO.obj");

	PlanePhysics = new PhysicsObject(Plane, 0);
	PlanePhysics->SetVelocity(GVector(PlaneSpeed, 0, 0));
	PlanePhysics->SetAngle(90);


}

PlayerPlane::PlayerPlane(const float& PlaneSpeed)
{
	this->PlaneSpeed = PlaneSpeed;
	Step = 0.5;

	Plane = new Mesh(true);
	Plane->SetRoation(GVector(0, 1, 0));
	Plane->Load("A6M_ZERO.obj");

	PlanePhysics = new PhysicsObject(Plane, 0);
	PlanePhysics->SetVelocity(GVector(PlaneSpeed, 0, 0));
	PlanePhysics->SetAngle(90);
}

void PlayerPlane::SetBullets(ParticleSystem* Bullets)
{
	this ->Bullets = Bullets;
}

void PlayerPlane::MoveRight()
{
	PlanePhysics->AddRelativeLocation(0, 0, Step);
}

void PlayerPlane::MoveLeft()
{
	PlanePhysics->AddRelativeLocation(0, 0, -Step);
}

void PlayerPlane::MoveUp()
{
	PlanePhysics->AddRelativeLocation(0, Step, 0);
	
}

void PlayerPlane::MoveDown()
{
	PlanePhysics->AddRelativeLocation(0, -Step, 0);
}

void PlayerPlane::Accelerate()
{
	GVector Vel = PlanePhysics->GetVelocity();

	Vel.y = Vel.y + Step < PlaneSpeed*2 ? Vel.y + 0.5 : Vel.y;

	//PlanePhysics->SetVelocity(Vel);
	PlanePhysics->AddRelativeVelocity(Step, 0,0);
}

void PlayerPlane::Break()
{
	GVector Vel = PlanePhysics->GetVelocity();

	if (Vel.x - 0.5 > PlaneSpeed)
		PlanePhysics->AddRelativeVelocity(-0.5, 0, 0);
}

void PlayerPlane::Shoot()
{
	Bullets->SetNewParticles(1);
}

void PlayerPlane::StopShooting()
{
	Bullets->SetNewParticles(0);
}

void PlayerPlane::SetPlaneSpeed(const float& PlaneSpeed)
{
	this->PlaneSpeed = PlaneSpeed;
}
