#pragma once
#include "GObject.h"


class ParticleSystem;
struct Particle;

class ParticleEmitter : public GObject
{
public:

	ParticleEmitter();
	ParticleEmitter(GObject* Parent);

	virtual void EmitParticle(Particle & p) = 0;
};
