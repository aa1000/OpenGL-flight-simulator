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
	GVector Velocity;


	GLuint Texture;

	float Size, ZAngle;
	float LifeTime;


public:
	Particle()
	{
		Size = 1;
		ZAngle = 0;
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

	void SetEmitter(ParticleEmitter* Emitter);
	inline ParticleEmitter* GetEmitter() { return Emitter; }

	void AddTexture(char* FileName);

	void InitPaticles();

	virtual void Update(const float & DeltaTime) override;
	virtual void Render() override;
	
};
