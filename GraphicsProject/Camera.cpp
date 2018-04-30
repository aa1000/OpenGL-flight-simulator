#include "Camera.h"
#include "GL\freeglut.h"
#include <math.h>

Camera::Camera()
{
	CameraLocation = GVector(0, 10, 20);

	CameraHeadingX = 0;
	CameraHeadingZ = -1;

	CameraLocationSen = 1;
	CameraRotationSen = 0.1;
	CameraHeadingSen = 0.5;
}

void Camera::RotateLeft()
{
	CameraRoation.x -= CameraRotationSen;
	CameraHeadingX = sin(CameraRoation.x);
	CameraHeadingZ = -cos(CameraRoation.x);
}

void Camera::RotateRight()
{
	CameraRoation.x += CameraRotationSen;
	CameraHeadingX = sin(CameraRoation.x);
	CameraHeadingZ = -cos(CameraRoation.x);
}

void Camera::MoveUp()
{
	CameraLocation.y += CameraLocationSen;
}

void Camera::MoveDown()
{
	CameraLocation.y -= CameraLocationSen;
}

void Camera::MoveForward()
{
	CameraLocation.x += CameraHeadingX * CameraHeadingSen;
	CameraLocation.z += CameraHeadingZ * CameraHeadingSen;
}

void Camera::MoveBackwards()
{
	CameraLocation.x -= CameraHeadingX * CameraHeadingSen;
	CameraLocation.z -= CameraHeadingZ * CameraHeadingSen;
}

void Camera::RenderLookAt()
{
	glLoadIdentity();
	gluLookAt(CameraLocation.x, CameraLocation.y, CameraLocation.z,
		CameraLocation.x + CameraHeadingX, CameraLocation.y,
		CameraLocation.z + CameraHeadingZ, 0, 1, 0);
}
