#pragma once
#include "ParticleEmitter.h"

class SphereParticleEmitter : public ParticleEmitter
{

	float Raduis;
public:
	
	SphereParticleEmitter();
	SphereParticleEmitter(GObject* Parent);
	SphereParticleEmitter(GObject* Parent, const float & Raduis);

	void SetRaduis(const float & Raduis);
	inline float GetRaduis() const { return Raduis; }

	virtual void EmitParticle(Particle& p) override;
};
