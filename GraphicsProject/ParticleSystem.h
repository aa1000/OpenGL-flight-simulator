#pragma once
#include <vector>
#include "GL\freeglut.h"
#include "RenderedObject.h"

using namespace std;

struct Particle
{
	GVector Location;
	GVector Speed;

	unsigned char r, g, b, a; // color

	float Size, Angle;
	float life;


};

class ParticleSystem : RenderedObject
{
	vector<GLint> Textures;
	int MaxParticles;
	Particle* ParticlesContainer;

public:
	ParticleSystem();
	ParticleSystem(int MaxParticles);

	~ParticleSystem();
};
