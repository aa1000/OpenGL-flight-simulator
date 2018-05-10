#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "GMath.h"


ParticleEmitter::ParticleEmitter()
	:GObject()
{
	MinLifeTime = MaxLifeTime = 1;
	MinSpeed = MaxSpeed = 1;
	MinSize = MaxSize = 1;
	MinAngle = MaxAngle = 0;
	MinFadingOverTime = MaxFadingOverTime = 1;
	MinSizeOverTime = MaxSizeOverTime = 1;
	MinStartVelocity = MaxStartVelocity = GVector(0);
	MinRotation = GVector(0);
	MaxRotation = GVector(1);
	Offset = GVector(0);
	StartColour = EndColour = GVector(1);
}

ParticleEmitter::ParticleEmitter(GObject* Parent)
	:GObject(Parent)
{
	MinLifeTime = MaxLifeTime = 1;
	MinSpeed = MaxSpeed = 1;
	MinSize = MaxSize = 1;
	MinAngle = MaxAngle = 0;
	MinFadingOverTime = MaxFadingOverTime = 1;
	MinSizeOverTime = MaxSizeOverTime = 1;
	MinStartVelocity = MaxStartVelocity = GVector(0);
	MinRotation = GVector(0);
	MaxRotation = GVector(1);
	Offset = GVector(0);
	StartColour = EndColour = GVector(1);
}

void ParticleEmitter::SetLifeTime(const float& MinLifeTime, const float& MaxLifeTime)
{
	this->MinLifeTime = MinLifeTime;
	this->MaxLifeTime = MaxLifeTime;
}

void ParticleEmitter::SetSpeed(const float& MinSpeed, const float& MaxSpeed)
{
	this->MinSpeed = MinSpeed;
	this->MaxSpeed = MaxSpeed;
}

void ParticleEmitter::SetSize(const float& MinSize, const float& MaxSize)
{
	this->MinSize = MinSize;
	this->MaxSize = MaxSize;
}

void ParticleEmitter::SetAngle(const float& MinAngle, const float& MaxAngle)
{
	this->MinAngle = MinAngle;
	this->MaxAngle = MaxAngle;
}

void ParticleEmitter::SetAngularVelocity(const float& Min, const float& Max)
{
	this->MinAngularVelocity = Min;
	this->MaxAngularVelocity = Max;
}

void ParticleEmitter::SetFadingOverTime(const float& MinFading, const float& MaxFading)
{
	this->MinFadingOverTime = MinFading;
	this->MaxFadingOverTime = MaxFading;
}

void ParticleEmitter::SetSizeOvertime(const float& MinSizeOverTime, const float& MaxSizeOverTime)
{
	this->MinSizeOverTime = MinSizeOverTime;
	this->MaxSizeOverTime = MaxSizeOverTime;
}

void ParticleEmitter::SetStartVelocity(const GVector& MinStartVelocity, const GVector& MaxStartVelocity)
{
	this->MinStartVelocity = MinStartVelocity;
	this->MaxStartVelocity = MaxStartVelocity;
}

void ParticleEmitter::SetParticleRotation(const GVector& MinRot, const GVector& MaxRot)
{
	this->MinRotation = MinRot;
	this->MaxRotation = MaxRot;
}

void ParticleEmitter::SetOffset(const GVector & Offset)
{
	this->Offset = Offset;
}

void ParticleEmitter::SetColour(const GVector& StartColour, const GVector& EndColour)
{
	this->StartColour = EndColour;
	this->EndColour = EndColour;
}

void ParticleEmitter::EmitParticle(Particle& p)
{
	GObject* Parent = GetParent();
	GVector Origin(0);

	if (Parent)
		Origin = Parent->GetLocation();

	p.Age = p.LifeTime = GMath::RandNumRange<float>(MinLifeTime, MaxLifeTime);
	p.Scale = p.Size = GMath::RandNumRange<float>(MinSize, MaxSize);
	p.SizeOverTime = GMath::RandNumRange<float>(MinSizeOverTime, MaxSizeOverTime);
	p.FadingOverTime = GMath::RandNumRange<float>(MinFadingOverTime, MaxFadingOverTime);
	p.Rotation = GMath::RandNumRange<GVector>(MinRotation, MaxRotation);
	p.Velocity = GMath::RandNumRange<GVector>(MinStartVelocity, MaxStartVelocity);
	p.AngularVelocity = GMath::RandNumRange<float>(MinAngularVelocity, MaxAngularVelocity);
	p.Angle = GMath::RandNumRange<float>(MinAngle, MaxAngle);
	p.flirckering = GMath::RandNumRange<GVector>(MinFlickering, MaxFlickering);
	p.SetColour(GMath::RandNumRange<GVector>(StartColour, EndColour));
	p.Location += Offset + Origin;
}
