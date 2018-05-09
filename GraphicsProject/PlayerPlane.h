#pragma once
#include "Mesh.h"
#include "PhysicsObject.h"
#include "Camera.h"

class PlayerPlane : public GObject
{
	Mesh* Plane;
	PhysicsObject* PlanePhysics;
	Camera* ActiveCamera;

	float PlaneSpeed;
public:
	PlayerPlane();

	void SetPlaneSpeed(const float & PlaneSpeed); 
	inline float GetPlaneSpeed() const { return PlaneSpeed; }


	void MoveRight();
	void MoveLeft();
	void Accelerate();
	void Break();
	
};
