#include "BoxParticleEmitter.h"
#include "ParticleSystem.h"
#include "GMath.h"

BoxParticleEmitter::BoxParticleEmitter()
	:ParticleEmitter()
{
}

BoxParticleEmitter::BoxParticleEmitter(GObject* Parent)
	:ParticleEmitter(Parent)
{
}

BoxParticleEmitter::BoxParticleEmitter(GObject* Parent, const GVector& MinBounds, const GVector& MaxBounds)
	:ParticleEmitter(Parent)
{
	this->MinBounds = MinBounds;
	this->MaxBounds = MaxBounds;
}

void BoxParticleEmitter::EmitParticle(Particle& p)
{
	p.Location =  GMath::RandNumRange<GVector>(MinBounds, MaxBounds);
	__super::EmitParticle(p);
}

void BoxParticleEmitter::SetMinBounds(const GVector& MinBounds)
{
	this->MinBounds = MinBounds;
}

void BoxParticleEmitter::SetMaxBounds(const GVector& MaxBounds)
{
	this->MaxBounds = MaxBounds;
}
