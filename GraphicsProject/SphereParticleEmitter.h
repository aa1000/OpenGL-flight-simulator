#pragma once
#include "ParticleEmitter.h"

class SphereParticleEmitter : public ParticleEmitter
{

	float Raduis;
public:
	
	SphereParticleEmitter();
	SphereParticleEmitter(GObject* Parent);

	void SetRaduis(const float & Raduis);
	inline float GetRaduis() const { return Raduis; }

	virtual void EmitParticle(Particle& p) override;
};
