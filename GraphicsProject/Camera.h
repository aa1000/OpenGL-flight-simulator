#pragma once
#include "GVector.h"
class Camera
{
public:
	GVector CameraLocation;
	GVector CameraRoation;
	float CameraHeadingX;
	float CameraHeadingZ;

	float CameraLocationSen;
	float CameraRotationSen;
	float CameraHeadingSen;

	Camera();
	void RotateLeft();
	void RotateRight();

	void MoveUp();
	void MoveDown();

	void MoveForward();
	void MoveBackwards();

	void RenderLookAt();
	
};
