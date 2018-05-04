#include "ParticleSystem.h"
#include "ParticleEmitter.h"

const GLfloat ParticleSystem::VertexBufferData[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
};

void ParticleSystem::Init()
{
	RenderedObject::Init();
	PhysicsObject::Init();
	QuadsPerColor = 1;
	LastParticle = 0;
	NewParticles = MaxParticles / 10;
	ParticlesContainer = new Particle[MaxParticles];
}

ParticleSystem::ParticleSystem()
	:RenderedObject(), PhysicsObject()
{
	MaxParticles = 10000;
	Init();
}

ParticleSystem::ParticleSystem(GObject* Parent)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	Init();
}

ParticleSystem::ParticleSystem(Camera* camera)
	: RenderedObject(), PhysicsObject()
{
	this->camera = camera;
}

ParticleSystem::ParticleSystem(int MaxParticles)
	: RenderedObject(), PhysicsObject()
{
	this->MaxParticles = MaxParticles;
	Init();
}

ParticleSystem::ParticleSystem(GObject* Parent, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	Init();
	this->MaxParticles = MaxParticles;
}

ParticleSystem::ParticleSystem(GObject* Parent, Camera* camera, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	Init();
	this->MaxParticles = MaxParticles;
}

ParticleSystem::ParticleSystem(GObject* Parent, Camera* camera, ParticleEmitter* Emitter, int MaxParticles)
	:RenderedObject(Parent), PhysicsObject(Parent)
{
	Init();
	this->MaxParticles = MaxParticles;
	this->camera = camera;
	this->Emitter = Emitter;
}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < Textures.size(); i++)
		glDeleteTextures(1, &Textures[i]);

	delete[] ParticlesContainer;
}

void ParticleSystem::FindLastParticle()
{
	for (int i = LastParticle; i<MaxParticles; i++) {
		if (ParticlesContainer[i].LifeTime < 0) {
			LastParticle = i;
		}
	}

	for (int i = 0; i<LastParticle; i++) {
		if (ParticlesContainer[i].LifeTime < 0) {
			LastParticle = i;
		}
	}

	LastParticle = 0;
}

void ParticleSystem::Compile()
{
	// buffer for particle vertices
	glGenBuffers(1, &ParticlesVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferData), VertexBufferData, GL_STATIC_DRAW);

	// buffer for position and scale for particles
	glGenBuffers(1, &ParticlesLocationBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesLocationBuffer);
	// Initialize with null to update each frame later
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	//buffer for particles colour
	glGenBuffers(1, &ParticlesColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

	// vertices buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesVertexBuffer);
	// attribute - must match AttribArray, size, type, nomalization, stride, array buffer offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// particles' centers buffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesLocationBuffer);
	// attribute - must match AttribArray, size (x + y + z + size = 4), type, nomalization, stride, array buffer offset
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0	);

	// particles colors buffer
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, ParticlesColorBuffer);
	// attribute - must match AttribArray, size (r + g + b + a = 4), type, nomalization, stride, array buffer offset
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );


}


void ParticleSystem::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void ParticleSystem::Update(const float & DeltaTime)
{
	// Simulate all particles
	//int ParticlesCount = 0;
	//for (int i = 0; i<MaxParticles; i++) {

	//	Particle& P = ParticlesContainer[i];

	//	if (P.life > 0.0f) {

	//		// Decrease life
	//		P.life -= delta;
	//		if (P.life > 0.0f) {

	//			// Simulate simple physics : gravity only, no collisions
	//			P.Speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)delta * 0.5f;
	//			p.pos += p.speed * (float)delta;
	//			p.cameradistance = glm::length2(p.pos - CameraPosition);
	//			//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

	//			// Fill the GPU buffer
	//			g_particule_position_size_data[4 * ParticlesCount + 0] = p.pos.x;
	//			g_particule_position_size_data[4 * ParticlesCount + 1] = p.pos.y;
	//			g_particule_position_size_data[4 * ParticlesCount + 2] = p.pos.z;

	//			g_particule_position_size_data[4 * ParticlesCount + 3] = p.size;

	//			g_particule_color_data[4 * ParticlesCount + 0] = p.r;
	//			g_particule_color_data[4 * ParticlesCount + 1] = p.g;
	//			g_particule_color_data[4 * ParticlesCount + 2] = p.b;
	//			g_particule_color_data[4 * ParticlesCount + 3] = p.a;

	//		}
	//		else {
	//			// Particles that just died will be put at the end of the buffer in SortParticles();
	//			P.cameradistance = -1.0f;
	//		}

	//		ParticlesCount++;

	//	}
	//}
}

void ParticleSystem::Render()
{

	//glBindBuffer(GL_ARRAY_BUFFER, ParticlesLocationBuffer);
	//glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	//glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);

	//glBindBuffer(GL_ARRAY_BUFFER, ParticlesColorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	//glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);

	//// how many instences share the same data
	//glVertexAttribDivisor(0, 0); // reuse the same 4 vertices => 0
	//glVertexAttribDivisor(1, 1); // one quad per postion (center) => 1
	//glVertexAttribDivisor(2, QuadsPerColor); // one quad per colour => 1

	//// ex glVertexAttribDivisor(2, 1) => glVertexAttribDivisor(2, 10) means every 10 subsequent instances will have the same color

	//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, MaxParticles);
}
