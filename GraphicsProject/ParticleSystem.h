#pragma once
#include <vector>


#include <GL/glew.h>
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

	GLubyte R, G, B, A; // color

	float Size, ZAngle;
	float LifeTime;

	bool operator<(Particle& other) {
		// Sort in reverse order : far particles drawn first.
	//	return this->cameradistance > other.cameradistance;
	}

//public:
//	Particle()
//	{
//		
//	}


};

class ParticleSystem : public RenderedObject, public PhysicsObject
{
	static const GLfloat VertexBufferData[]; 

	vector<GLuint> Textures;

	GLuint ParticlesVertexBuffer;
	GLuint ParticlesLocationBuffer;
	GLuint ParticlesColorBuffer;

	int MaxParticles;
	int NewParticles;
	int QuadsPerColor;

	int LastParticle;
	Particle* ParticlesContainer;

	ParticleEmitter* Emitter;
	Camera* camera;

	void FindLastParticle();
protected:
	virtual void Init() override;
	virtual void Compile() override;
public:
	ParticleSystem();
	ParticleSystem(GObject* Parent);
	ParticleSystem(Camera* camera);
	ParticleSystem(int MaxParticles);
	ParticleSystem(GObject* Parent, int MaxParticles);
	ParticleSystem(GObject* Parent, Camera* camera, int MaxParticles);
	ParticleSystem(GObject* Parent, Camera* camera, ParticleEmitter* Emitter, int MaxParticles);
	
	~ParticleSystem();

	void SetMaxParticles(const int & NewMax);
	inline int GetMaxParticles() const { return MaxParticles; }

	void SetCamera(Camera* camera);

	virtual void Update(const float & DeltaTime) override;
	virtual void Render() override;
	
};
