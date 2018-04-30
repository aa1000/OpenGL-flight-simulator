#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	MaxParticles = 10000;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(int MaxParticles)
{
	this->MaxParticles = MaxParticles;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::~ParticleSystem()
{
	delete[] ParticlesContainer;
}
