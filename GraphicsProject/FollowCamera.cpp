#include "FollowCamera.h"
#include "PhysicsObject.h"
#include "PlayerPlane.h"

FollowCamera::FollowCamera(PlayerPlane* Parent)
	:Camera()
{
	Offset = GVector(-30, 10, 0);

	Player = Parent;
	CameraPhysics = new PhysicsObject(this, 0);
	CameraPhysics->SetMass(0);
}

void FollowCamera::RenderLookAt()
{
	GVector PlayerLocation;
	if(Player)
	{
		PhysicsObject* PlayerPhysics = Player->GetPhysics();

		if (PlayerPhysics)
		{
			PlayerLocation = PlayerPhysics->GetLocation();
			CameraPhysics->SetVelocity(PlayerPhysics->GetVelocity());
		}
	}
	
	CameraLocation = PlayerLocation +Offset;

	glLoadIdentity();
	gluLookAt(CameraLocation.x, CameraLocation.y, CameraLocation.z,
		PlayerLocation.x, PlayerLocation.y, PlayerLocation.z, 0, 1, 0);

}
