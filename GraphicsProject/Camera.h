#pragma once
#include "GVector.h"
#include "GObject.h"

class Camera : public GObject
{
public:
	GVector CameraLocation;
	GVector CameraRoation;
	GVector CameraHeading;

	float CameraLocationSen;
	float CameraRotationSen;
	float CameraHeadingSen;

	Camera();
	void RotateLeft();
	void RotateRight();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void MoveForward();
	void MoveBackwards();

	void RenderLookAt();
	
};
