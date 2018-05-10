#include "SkyShpere.h"
#include "Drawing.h"

SkyShpere::SkyShpere(GObject* Parent, const float& Raduis)
	:RenderedObject(Parent)
{
	this->Raduis = Raduis;
	SetAngle(90);
	SetRoation(GVector(1, 0, 0));
}

bool SkyShpere::Load(char* FileName)
{
	Texture = Drawing::LoadTexture(FileName);
	return __super::Load(FileName);
}

void SkyShpere::Build()
{
	glBindTexture(GL_TEXTURE_2D, Texture);
	Sphere = gluNewQuadric();
	gluQuadricDrawStyle(Sphere, GLU_FILL);
	gluQuadricNormals(Sphere, GLU_SMOOTH);
	gluQuadricOrientation(Sphere, GLU_INSIDE);
	gluQuadricTexture(Sphere, GLU_TRUE);
	gluSphere(Sphere, Raduis, Raduis, Raduis);
}

void SkyShpere::Render()
{
	GObject* Parent = GetParent();
	
	//glDisable(GL_FOG);
	if (Parent)
		SetLocation(Parent->GetLocation());
	__super::Render();
	//glEnable(GL_FOG);
}
