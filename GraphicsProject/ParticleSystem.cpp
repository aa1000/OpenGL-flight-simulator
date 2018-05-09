
#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include <algorithm>
#include "Drawing.h"
#include "GMath.h"

//half height and half width set to 0.5 so that the unscaled size will be 1
//const GLfloat ParticleSystem::VertexBufferData[] = {
//	-0.5f, -0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	-0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.0f,
//};


ParticleSystem::ParticleSystem()
	:RenderedObject(), PhysicsObject()
{
	MaxParticles = 10000;
	NewParticles = MaxParticles * 0.002;
	this->camera = RenderingEngine::GetActiveCamera();
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(GObject* Parent)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	NewParticles = MaxParticles * 0.002;
	this->camera = RenderingEngine::GetActiveCamera();
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(int MaxParticles)
	: RenderedObject(), PhysicsObject()
{
	this->MaxParticles = MaxParticles;
	NewParticles = MaxParticles * 0.002;
	this->camera = RenderingEngine::GetActiveCamera();
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(GObject* Parent, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	this->MaxParticles = MaxParticles;
	NewParticles = MaxParticles * 0.002;
	this->camera = RenderingEngine::GetActiveCamera();
	ParticlesContainer = new Particle[MaxParticles];
}


ParticleSystem::ParticleSystem(GObject* Parent, ParticleEmitter* Emitter, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	this->MaxParticles = MaxParticles;
	this->Emitter = Emitter;
	NewParticles = MaxParticles * 0.002;
	this->camera = RenderingEngine::GetActiveCamera();
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < Textures.size(); i++)
		glDeleteTextures(1, &Textures[i]);

	delete[] ParticlesContainer;
	
}

void ParticleSystem::SetMaxParticles(const int& NewMax)
{
	this->MaxParticles = NewMax;
	delete[] ParticlesContainer;
}

void ParticleSystem::InitPaticles()
{
	for(int i = 0; i < MaxParticles; i++)
	{
		Particle& P = ParticlesContainer[i];

		const int t = GMath::RandNumRange<int>(0, Textures.size() - 1);
		P.Texture = Textures[t];

		EmitParticle(P);

	}
}

void ParticleSystem::EmitParticle(Particle& p)
{

	const int t = GMath::RandNumRange<int>(0, Textures.size() - 1);
	p.Texture = Textures[t];

	p.Velocity.init(0);

	if (Emitter != nullptr)
		Emitter->EmitParticle(p);
}


void ParticleSystem::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void ParticleSystem::SetEmitter(ParticleEmitter* Emitter)
{
	this->Emitter = Emitter;
}

void ParticleSystem::AddTexture(char* FileName)
{
	Textures.push_back(Drawing::LoadTexture(FileName));
}


void ParticleSystem::Update(const float & DeltaTime)
{
	int NewCounter = 0;
	// Simulate all particles
	for (int i = 0; i<MaxParticles; i++) 
	{

		Particle& P = ParticlesContainer[i];

		if (P.LifeTime < 0.0f && NewCounter < NewParticles)
		{
			EmitParticle(P);
			NewCounter++;
		}
		else
		{
			// Decrease life
			P.LifeTime -= DeltaTime;

			// Simulate simple physics
			P.Velocity += GVector(0.0f, GetMass() * -PhysicsEngine::GetGravity(), 0.0f) * DeltaTime;
			P.Location += P.Velocity * DeltaTime;

		}
	}
}

void ParticleSystem::Render()
{
	glDisable(GL_LIGHTING);
	for (int i = 0; i < MaxParticles; i++)
	{
		if (ParticlesContainer[i].LifeTime > 0)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			glColor4f(1, 1, 1, 1);
			glPushMatrix();
			glScalef(ParticlesContainer[i].Size, ParticlesContainer[i].Size, ParticlesContainer[i].Size);
			glTranslatef(ParticlesContainer[i].Location.x, ParticlesContainer[i].Location.y, ParticlesContainer[i].Location.z);
		//	glRotatef(flakes[i].rotAng, flakes[i].xr, flakes[i].yr, flakes[i].zr);

			glBindTexture(GL_TEXTURE_2D, ParticlesContainer[i].Texture);
			glBegin(GL_QUADS);

			glTexCoord2d(0, 0);
			glVertex3f(-0.5, -0.5, 0);
			glTexCoord2d(0, 1);
			glVertex3f(-0.5, 0.5, 0);
			glTexCoord2d(1, 1);
			glVertex3f(0.5, 0.5, 0);
			glTexCoord2d(1, 0);
			glVertex3f(0.5, -0.5, 0);

			glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		}
	}
	glEnable(GL_LIGHTING);
}
