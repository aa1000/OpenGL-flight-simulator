#pragma once
#include "ParticleEmitter.h"

class BoxParticleEmitter : public ParticleEmitter
{
public:
	
	BoxParticleEmitter();
	BoxParticleEmitter(GObject* Parent);
	virtual void EmitParticle(Particle& p) override;
};
