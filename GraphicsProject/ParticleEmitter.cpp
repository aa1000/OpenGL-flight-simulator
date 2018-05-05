#include "ParticleEmitter.h"
#include "ParticleSystem.h"


ParticleEmitter::ParticleEmitter()
	:GObject()
{
	MinSpeed = MaxSpeed = 1;
	MinLifeTime = MaxLifeTime = 5;
}

ParticleEmitter::ParticleEmitter(GObject* Parent)
	:GObject(Parent)
{
	MinSpeed = MaxSpeed = 1;
	MinLifeTime = MaxLifeTime = 5;
}

ParticleEmitter::ParticleEmitter(GObject* Parent, const float& MinLifeTime, const float& MaxLifeTime,
	const float& MinSpeed, const float& MaxSpeed)
	:GObject(Parent)
{
	this->MinLifeTime = MinLifeTime;
	this->MaxLifeTime = MaxLifeTime;
	this->MinSpeed = MinSpeed;
	this->MaxSpeed = MaxSpeed;
}
