#include "Camera.h"
#include "GL\freeglut.h"
#include <math.h>

Camera::Camera()
{
	//CameraLocation = GVector(0, 10, 20);

	CameraLocationSen = 1;
	CameraRotationSen = 0.1;
	CameraHeadingSen = 0.5;

	//CameraRoation.y = 0.4;
	//CameraHeading.y = sin(CameraRoation.y);
}

void Camera::RotateLeft()
{
	CameraRoation.x -= CameraRotationSen;
	CameraHeading.x = sin(CameraRoation.x);
	CameraHeading.z = -cos(CameraRoation.x);
}

void Camera::RotateRight()
{
	CameraRoation.x += CameraRotationSen;
	CameraHeading.x = sin(CameraRoation.x);
	CameraHeading.z = -cos(CameraRoation.x);
}

void Camera::MoveUp()
{
	CameraLocation.y += CameraLocationSen;
	SetLocation(CameraLocation);
}

void Camera::MoveDown()
{
	CameraLocation.y -= CameraLocationSen;
	SetLocation(CameraLocation);
}

void Camera::MoveRight()
{
	CameraLocation.z -= CameraLocationSen;
	SetLocation(CameraLocation);
}

void Camera::MoveLeft()
{
	CameraLocation.z -= CameraLocationSen;
	SetLocation(CameraLocation);
}

void Camera::MoveForward()
{
	CameraLocation.x += CameraHeading.x * CameraHeadingSen;
	CameraLocation.z += CameraHeading.z * CameraHeadingSen;
	SetLocation(CameraLocation);
}

void Camera::MoveBackwards()
{
	CameraLocation.x -= CameraHeading.x * CameraHeadingSen;
	CameraLocation.z -= CameraHeading.z * CameraHeadingSen;
	SetLocation(CameraLocation);
}

void Camera::RenderLookAt()
{
	CameraLocation = GetLocation();
	glLoadIdentity();
	gluLookAt(CameraLocation.x, CameraLocation.y, CameraLocation.z,
		CameraLocation.x + CameraHeading.x, CameraLocation.y,
		CameraLocation.z + CameraHeading.z, 0, 1, 0);
}
