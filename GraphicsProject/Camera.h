#pragma once
#include "GVector.h"
#include "GObject.h"


class Camera : public GObject
{
public:

	//PlayerPlane* Plane;
	Camera();
	GVector Offset;
	GVector CameraLocation;
	GVector CameraRoation;
	GVector CameraHeading;

	float CameraLocationSen;
	float CameraRotationSen;
	float CameraHeadingSen;

	void RotateUp();
	void RotateDown();
	void RotateLeft();
	void RotateRight();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void MoveForward();
	void MoveBackwards();

	virtual void RenderLookAt();
	
};
