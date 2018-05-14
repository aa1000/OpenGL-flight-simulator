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

	float CameraDistance;

public:
	Particle()
	{
		R = G = B = A = 1;
		Size = 1;
		Angle = 0;
		FadingOverTime = 1;
		SizeOverTime = 1;
		CameraDistance = -1;
	}
	void SetColour(const GVector & Colour)
	{
		this->R = Colour.x;
		this->G = Colour.y;
		this->B = Colour.z;
	}

	bool operator<(Particle& other) 
	{
		// Sort in reverse order far particles drawn first
		return this->CameraDistance > other.CameraDistance;
	}


};

class ParticleSystem : public RenderedObject, public PhysicsObject
{

	vector<GLuint> Textures;

	int MaxParticles;
	int NewParticles;

	bool SortToCamera;
	Particle* ParticlesContainer;

	ParticleEmitter* Emitter;

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

	void SetSortToCamera(const bool & bSortToCamera);
	inline bool GetSortToCamera() const { return SortToCamera; }

	void SetNewParticles(const int & NewParticles);
	inline int GetNewParticles() const { return NewParticles; }

	void SetEmitter(ParticleEmitter* Emitter);
	inline ParticleEmitter* GetEmitter() { return Emitter; }

	void AddTexture(char* FileName);

	void InitPaticles();

	virtual void Update(const float & DeltaTime) override;
	virtual void Render() override;
	
};
