
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
	SortToCamera = false;
	MaxParticles = 10000;
	NewParticles = MaxParticles * 0.002;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(GObject* Parent)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	SortToCamera = false;
	NewParticles = MaxParticles * 0.002;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(int MaxParticles)
	: RenderedObject(), PhysicsObject()
{
	SortToCamera = false;
	this->MaxParticles = MaxParticles;
	NewParticles = MaxParticles * 0.002;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem(GObject* Parent, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	SortToCamera = false;
	this->MaxParticles = MaxParticles;
	NewParticles = MaxParticles * 0.002;
	ParticlesContainer = new Particle[MaxParticles];
}


ParticleSystem::ParticleSystem(GObject* Parent, ParticleEmitter* Emitter, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	SortToCamera = false;
	this->MaxParticles = MaxParticles;
	this->Emitter = Emitter;
	NewParticles = MaxParticles * 0.002;
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

void ParticleSystem::SetSortToCamera(const bool& bSortToCamera)
{
	this->SortToCamera = bSortToCamera;
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

	if (Emitter != NULL)
		Emitter->EmitParticle(p);
}

void ParticleSystem::SetNewParticles(const int& NewParticles)
{
	this->NewParticles = NewParticles;
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

		if (P.Age < 0.0f && NewCounter < NewParticles)
		{
			EmitParticle(P);
			NewCounter++;
		}
		else
		{
			// Decrease life
			P.Age -= DeltaTime;

		//	P.Scale = ( ((1 - P.SizeOverTime) / P.LifeTime) * P.Age + P.SizeOverTime ) * P.Size;
			P.A = ((1 - P.FadingOverTime)/P.LifeTime) * P.Age + P.FadingOverTime;
			// Simulate simple physics
			P.Velocity += GetAcceleration() * DeltaTime;
			P.Location += P.Velocity * DeltaTime;
			P.Angle += P.AngularVelocity * DeltaTime;

			P.CameraDistance = (P.Location - RenderingEngine::GetActiveCamera()->CameraLocation).Length();

		}
	}

	if(SortToCamera)
		std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
}

void ParticleSystem::Render()
{

	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	for (int i = 0; i < MaxParticles; i++)
	{
		Particle& P = ParticlesContainer[i];
		if (P.Age > 0)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			
			glPushMatrix();
			glColor4f(P.R, P.G, P.B, P.A);
			glScalef(P.Scale, P.Scale, P.Scale);
			glTranslatef(P.Location.x, P.Location.y, P.Location.z);
			glRotatef(P.Angle, P.Rotation.x, P.Rotation.y, P.Rotation.z);

			glBindTexture(GL_TEXTURE_2D, P.Texture);
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
	glEnable(GL_FOG);
}
