#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "GMath.h"


ParticleEmitter::ParticleEmitter()
	:GObject()
{
	MinLifeTime = MaxLifeTime = 1;
	MinSpeed = MaxSpeed = 1;
	MinSize = MaxSize = 1;
}

ParticleEmitter::ParticleEmitter(GObject* Parent)
	:GObject(Parent)
{
	MinLifeTime = MaxLifeTime = 1;
	MinSpeed = MaxSpeed = 1;
	MinSize = MaxSize = 1;
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

void ParticleEmitter::EmitParticle(Particle& p)
{
	GVector Origin;
	GObject* Parent = GetParent();

	if (Parent)
		Origin = Parent->GetLocation();
	else Origin.init(0);

	p.LifeTime = GMath::RandNumRange<float>(MinLifeTime, MaxLifeTime);
	p.Size = GMath::RandNumRange<float>(MinSize, MaxSize);
	p.Velocity *= GMath::RandNumRange<float>(MinSpeed, MaxSpeed);
	p.Location += Origin;
}
