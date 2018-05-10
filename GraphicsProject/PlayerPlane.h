#pragma once
#include "Mesh.h"
#include "PhysicsObject.h"
#include "ParticleSystem.h"

class PlayerPlane : public GObject
{
	Mesh* Plane;
	PhysicsObject* PlanePhysics;
	ParticleSystem* Bullets;

	float PlaneSpeed;
	float Step;

	bool MovingRight;
	bool MovingLeft;
	bool MovingUp;
	bool MoingDown;

public:
	PlayerPlane();
	PlayerPlane(const float & PlaneSpeed);

	void SetPlaneSpeed(const float & PlaneSpeed); 
	inline float GetPlaneSpeed() const { return PlaneSpeed; }

	inline PhysicsObject* GetPhysics() { return PlanePhysics; }
	inline Mesh* GetPlaneMesh() { return Plane; }

	void SetBullets(ParticleSystem* Bullets);

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	void Accelerate();
	void Break();
	void Shoot();
	void StopShooting();
	
};
