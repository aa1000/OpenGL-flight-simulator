#pragma once
#include <vector>



#include "RenderedObject.h"
#include "PhysicsObject.h"
#include "Camera.h"


//#include "GL\GL.h"
using namespace std;

class ParticleEmitter;

struct Particle
{
	GVector Location;
	GVector Rotation;
	GVector Velocity;

	float R, G, B, A;
	
	float AngularVelocity;

	float FadingOverTime;
	float SizeOverTime;

	float Angle;
	GVector flirckering;

	GLuint Texture;

	float Size;
	float Scale;
	float LifeTime;
	float Age;


public:
	Particle()
	{
		R = G = B = A = 1;
		Size = 1;
		Angle = 0;
		FadingOverTime = 1;
		SizeOverTime = 1;
	}
	void SetColour(const GVector & Colour)
	{
		this->R = Colour.x;
		this->G = Colour.y;
		this->B = Colour.z;
	}


};

class ParticleSystem : public RenderedObject, public PhysicsObject
{

	vector<GLuint> Textures;

	int MaxParticles;
	int NewParticles;

	Particle* ParticlesContainer;

	ParticleEmitter* Emitter;
	Camera* camera;

protected:

	virtual void EmitParticle(Particle & p);
public:
	ParticleSystem();
	ParticleSystem(GObject* Parent);
	ParticleSystem(int MaxParticles);
	ParticleSystem(GObject* Parent, int MaxParticles);
	ParticleSystem(GObject* Parent, ParticleEmitter* Emitter, int MaxParticles);
	
	~ParticleSystem();

	void SetMaxParticles(const int & NewMax);
	inline int GetMaxParticles() const { return MaxParticles; }

	void SetCamera(Camera* camera);

	void SetNewParticles(const int & NewParticles);
	inline int GetNewParticles() const { return NewParticles; }

	void SetEmitter(ParticleEmitter* Emitter);
	inline ParticleEmitter* GetEmitter() { return Emitter; }

	void AddTexture(char* FileName);

	void InitPaticles();

	virtual void Update(const float & DeltaTime) override;
	virtual void Render() override;
	
};
