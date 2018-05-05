#pragma once
#include "ParticleEmitter.h"

class BoxParticleEmitter : public ParticleEmitter
{
	GVector MinBounds;
	GVector MaxBounds;
public:
	
	BoxParticleEmitter();
	BoxParticleEmitter(GObject* Parent);
	BoxParticleEmitter(GObject* Parent, const GVector & MinBounds, const GVector & MaxBounds);
	virtual void EmitParticle(Particle& p) override;

	void SetMinBounds(const GVector & MinBounds);
	void SetMaxBounds(const GVector & MaxBounds);

	inline GVector GetMinBounds() const { return MinBounds; }
	inline GVector GetMaxBounds() const { return  MinBounds; }
};
