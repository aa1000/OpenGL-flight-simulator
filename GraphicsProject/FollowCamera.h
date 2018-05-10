#pragma once
#include "Camera.h"

class PhysicsObject;
class PlayerPlane;

class FollowCamera : public Camera
{
	PhysicsObject* CameraPhysics;
	PlayerPlane* Player;
	GVector Offset;

public:
	FollowCamera(PlayerPlane* Parent);

	virtual void RenderLookAt() override;

};