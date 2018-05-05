#pragma once
#include "GObject.h"


class ParticleSystem;
struct Particle;

class ParticleEmitter : public GObject
{

	float MinLifeTime, MaxLifeTime;
	float MinSpeed, MaxSpeed;

public:

	ParticleEmitter();
	ParticleEmitter(GObject* Parent);
	ParticleEmitter(GObject* Parent, const float & MinLifeTime, const float & MaxLifeTime, const float & MinSpeed, const float & MaxSpeed);

	virtual void EmitParticle(Particle & p) = 0;
};
