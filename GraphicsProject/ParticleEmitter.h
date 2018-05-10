#pragma once
#include "GObject.h"


class ParticleSystem;
struct Particle;

class ParticleEmitter : public GObject
{

	float MinLifeTime, MaxLifeTime;
	float MinSpeed, MaxSpeed;
	float MinSize, MaxSize;
	float MinAngle, MaxAngle;
	float MinAngularVelocity, MaxAngularVelocity;
	float MinFadingOverTime, MaxFadingOverTime;
	float MinSizeOverTime, MaxSizeOverTime;
	GVector MinStartVelocity, MaxStartVelocity;
	GVector MinFlickering, MaxFlickering;
	GVector MinRotation, MaxRotation;
	GVector Offset;
	GVector StartColour, EndColour;

public:

	ParticleEmitter();
	ParticleEmitter(GObject* Parent);

	void SetLifeTime(const float & MinLifeTime, const float & MaxLifeTime);
	void SetSpeed(const float & MinSpeed, const float & MaxSpeed);
	void SetSize(const float & MinSize, const float & MaxSize);
	void SetAngle(const float & MinAngle, const float & MaxAngle);
	void SetAngularVelocity(const float & Min, const float & Max);
	void SetFadingOverTime(const float & MinFading, const float & MaxFading);
	void SetSizeOvertime(const float & MinSizeOverTime, const float & MaxSizeOverTime);
	void SetStartVelocity(const GVector & MinStartVelocity, const GVector & MaxStartVelocity);
	void SetParticleRotation(const GVector & MinRot, const GVector & MaxRot);
	void SetOffset(const GVector & Offset);
	void SetColour(const GVector & StartColour, const GVector & EndColour);

	inline float GetMinLifeTime()			const { return MinLifeTime; }
	inline float GetMaxLifeTime()			const { return MaxLifeTime; }
	inline float GetMinSpeed()				const { return MinSpeed; }
	inline float GetMaxSpeed()				const { return MaxSpeed; }
	inline float GetMinSize()				const { return MinSize; }
	inline float GetMaxSize()				const { return MaxSize; }
	inline float GetMinAngle()				const { return MinAngle; }
	inline float GetMaxAngle()				const { return MaxAngle; }
	inline float GetMinAngularVelocity()	const { return MinAngularVelocity; }
	inline float GetMaxAngularVelcoty()		const { return MaxAngularVelocity; }
	inline float GetMinFadingOverTime()		const { return MinFadingOverTime; }
	inline float GetMaxFadingOverTime()		const { return MaxFadingOverTime; }
	inline float GetMinSizeOverTime()		const { return MinFadingOverTime; }
	inline float GetMaxSizeOverTime()		const { return MaxFadingOverTime; }
	inline GVector GetMinStartVelocity()	const { return MinStartVelocity; }
	inline GVector GetMaxStartVelocity()	const { return MaxStartVelocity; }
	inline GVector GetMinRotation()			const { return MinRotation; }
	inline GVector GetMaxRotation()			const { return MaxRotation; }
	inline GVector GetOffset()				const { return Offset; }
	inline GVector GetStartColour()			const { return StartColour; }
	inline GVector GetEndColour()			const { return EndColour; }

	virtual void EmitParticle(Particle & p);
};
