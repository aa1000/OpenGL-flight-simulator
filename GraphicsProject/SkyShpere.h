#pragma once
#include "RenderedObject.h"
#include <GL/glut.h>

class SkyShpere : RenderedObject
{
	GLUquadric* Sphere;
	GLuint Texture;
	float Raduis;
public:
	
	SkyShpere(GObject* Parent, const float & Raduis);
	virtual bool Load(char* FileName) override;
	virtual  void Build() override;
	virtual void Render() override;
};
