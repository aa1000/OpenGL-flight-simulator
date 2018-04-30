#pragma once
#include "Gl/freeglut.h"
#include "GVector.h"
class Drawing
{
public:
	static GLuint LoadTexture(char* filename, bool invert = true);

	static GVector CalculateNormal(GVector A, GVector B, GVector C);
};


