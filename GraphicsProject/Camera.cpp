#include "Camera.h"
#include "GL\freeglut.h"
#include <math.h>


Camera::Camera()
	:GObject()
{

	CameraLocationSen = 1;
	CameraRotationSen = 0.1;
	CameraHeadingSen = 0.5;

	CameraRoation.x = 1.4;
	CameraHeading.x = 1;
	CameraHeading.z = 0.15;

}

void Camera::RotateUp()
{
	CameraRoation.y += CameraRotationSen;
	CameraHeading.y = sin(CameraRoation.y);
	CameraHeading.z = -cos(CameraRoation.y);
}

void Camera::RotateDown()
{
	CameraRoation.y -= CameraRotationSen;
	CameraHeading.y = sin(CameraRoation.y);
	CameraHeading.z = -cos(CameraRoation.y);
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
}

void Camera::MoveDown()
{
	CameraLocation.y -= CameraLocationSen;
}

void Camera::MoveRight()
{
	CameraLocation.z -= CameraLocationSen;
}

void Camera::MoveLeft()
{
	CameraLocation.z -= CameraLocationSen;
}

void Camera::MoveForward()
{
	CameraLocation.x += CameraHeading.x * CameraHeadingSen;
	CameraLocation.z += CameraHeading.z * CameraHeadingSen;
}

void Camera::MoveBackwards()
{
	CameraLocation.x -= CameraHeading.x * CameraHeadingSen;
	CameraLocation.z -= CameraHeading.z * CameraHeadingSen;
}

void Camera::RenderLookAt()
{
	glLoadIdentity();
	gluLookAt(CameraLocation.x, CameraLocation.y, CameraLocation.z,
		CameraLocation.x + CameraHeading.x, CameraLocation.y + CameraHeading.y,
		CameraLocation.z + CameraHeading.z, 0, 1, 0);
}
