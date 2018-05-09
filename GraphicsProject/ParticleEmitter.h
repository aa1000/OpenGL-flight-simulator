#pragma once
#include "GObject.h"


class ParticleSystem;
struct Particle;

class ParticleEmitter : public GObject
{

	float MinLifeTime, MaxLifeTime;
	float MinSpeed, MaxSpeed;
	float MinSize, MaxSize;

public:

	ParticleEmitter();
	ParticleEmitter(GObject* Parent);

	void SetLifeTime(const float & MinLifeTime, const float & MaxLifeTime);
	void SetSpeed(const float & MinSpeed, const float & MaxSpeed);
	void SetSize(const float & MinSize, const float & MaxSize);

	inline float GetMinLifeTime() const { return MinLifeTime; }
	inline float GetMaxLifeTime() const { return MaxLifeTime; }
	inline float GetMinSpeed()	  const { return MinSpeed; }
	inline float GetMaxSpeed()	  const { return MaxSpeed; }
	inline float GetMinSize()	  const { return MinSize; }
	inline float GetMaxSize()	  const { return MaxSize; }

	virtual void EmitParticle(Particle & p);
};
