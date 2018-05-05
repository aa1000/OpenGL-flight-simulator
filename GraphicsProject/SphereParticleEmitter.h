#pragma once
#include "ParticleEmitter.h"

class SphereParticleEmitter : public ParticleEmitter
{
public:
	
	SphereParticleEmitter();
	SphereParticleEmitter(GObject* Parent);
	virtual void EmitParticle(Particle& p) override;
};
