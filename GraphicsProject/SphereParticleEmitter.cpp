#include "SphereParticleEmitter.h"
#include "ParticleSystem.h"
#include "GMath.h"

SphereParticleEmitter::SphereParticleEmitter()
	:ParticleEmitter()
{
	Raduis = 0;
}

SphereParticleEmitter::SphereParticleEmitter(GObject* Parent)
	:ParticleEmitter(Parent)
{
	Raduis = 0;
}

void SphereParticleEmitter::SetRaduis(const float& Raduis)
{
	this->Raduis = Raduis;
}

void SphereParticleEmitter::EmitParticle(Particle& p)
{
	p.Location = GMath::RandNumRange<GVector>(GVector::StaticInit(0), GVector::StaticInit(Raduis));
	__super::EmitParticle(p);
}
