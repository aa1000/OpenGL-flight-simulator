#include "HeightMap.h"
#include <FreeImage.h>
#include "Drawing.h"
#include <iostream>

HeightMap::HeightMap()
	:RenderedObject()
{
	MapWidth = 0;
	MapHeight = 0;
	StepSize = 4;
}

HeightMap::HeightMap(bool RenderInList)
	:RenderedObject(RenderInList)
{
	MapWidth = 0;
	MapHeight = 0;
	StepSize = 4;
}


HeightMap::~HeightMap()
{
	for (int i = 0; i < MapWidth; i++)
	{
		delete[] HeightMapBytes[i];
		delete[] HeightMapNormals[i];
	}

	delete[] HeightMapBytes;
	delete[] HeightMapNormals;

	glDeleteTextures(1, &Texture);
}

void HeightMap::SetTexture(const GLuint& Texture)
{
	this->Texture = Texture;
}

bool HeightMap::Load(char* FileName)
{
	FIBITMAP *img = FreeImage_Load(FreeImage_GetFileType(FileName, 0), FileName);
	if (!img)
		return false;
	img = FreeImage_ConvertTo8Bits(img);
	img = FreeImage_ConvertToGreyscale(img);

	MapWidth = FreeImage_GetWidth(img);
	MapHeight = FreeImage_GetHeight(img);

	HeightMapBytes = new BYTE*[MapWidth];
	for (int i = 0; i < MapWidth; i++)
		HeightMapBytes[i] = new BYTE[MapHeight];

	for (int y = 0; y < MapHeight; y++)
	{
		BYTE* ScanLine = FreeImage_GetScanLine(img, y);
		for (int x = 0; x < MapWidth; x++)
			HeightMapBytes[x][y] = ScanLine[x];
	}

	FreeImage_Unload(img);

//	CalculateNormals();
	return __super::Load(FileName);
}

GVector HeightMap::CalculatePlaneNormal(const int& X, const int& Z)
{
	int x, y, z;
	GVector A, B, C, D;
	GVector Normal;

	A = GetVertex(X, Z);
	B = GetVertex(X, Z + StepSize);
	C = GetVertex(X + StepSize, Z + StepSize);
	D = GetVertex(X + StepSize, Z);
	
	Normal = (C - A) * (D - B);
	return Normal.GetUnitVector();
	



}

GVector HeightMap::CalculateNormal(const int& X, const int& Z)
{
	//finite diffrence 
	

	int OffsetX = StepSize;
	int OffsetZ = StepSize;

	int HL = GetVertex(X - OffsetX, Z).y;
	int HR = GetVertex(X + OffsetX, Z).y;
	int HD = GetVertex(X, Z - OffsetZ).y;
	int HU = GetVertex(X, Z + OffsetZ).y;

	GVector Normal(HL - HR, OffsetZ + OffsetX, HD - HU);
	return Normal.GetUnitVector();
}

void HeightMap::BuildPolygon(const int & X, const int & Z)
{
	int x, y, z;
	GVector Normal;
	//Normal = CalculatePlaneNormal(X, Z);
	//glNormal3f(Normal.x, Normal.y, Normal.z);
	//std::cout << X << "\t";
	
	//Bottom left point
	x = X;
	z = Z;
	y = HeightMapBytes[x][z];

	Normal = CalculateNormal(x, z);

	if (Normal.x  <= 0 && Normal.y <= 0 && Normal.z <= 0)
		GVector();

	glTexCoord2d(0, 0);
	glNormal3f(Normal.x, Normal.y, Normal.z);
	glVertex3f(x, y, z);

	//Top Left Point
	x = X;
	z = Z + StepSize;
	y = HeightMapBytes[x][z];

	Normal = CalculateNormal(x, z);

	if (Normal.x <= 0 && Normal.y <= 0 && Normal.z <= 0)
		GVector();

	glTexCoord2d(0, 1);
	glNormal3f(Normal.x, Normal.y, Normal.z);
	glVertex3f(x, y, z);

	//Top right
	x = X + StepSize;
	z = Z + StepSize;
	y = HeightMapBytes[x][z];
	
	Normal = CalculateNormal(x, z);

	if (Normal.x <= 0 && Normal.y <= 0 && Normal.z <= 0)
		GVector();

	glTexCoord2d(1, 1);
	glNormal3f(Normal.x, Normal.y, Normal.z);
	glVertex3f(x, y, z);

	//Bottom Right
	x = X + StepSize;
	z = Z;
	y = HeightMapBytes[x][z];

	Normal = CalculateNormal(x, z);

	if (Normal.x <= 0 && Normal.y <= 0 && Normal.z <= 0)
		GVector();

	glTexCoord2d(1, 0);
	glNormal3f(Normal.x, Normal.y, Normal.z);
	glVertex3f(x, y, z);

	
}

void HeightMap::Build()
{
	//glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);
	

	for (int X = StepSize; X < MapWidth - StepSize - 1; X += StepSize)
	{
		for (int Y = StepSize; Y < MapHeight - StepSize - 1; Y += StepSize)
		{
			BuildPolygon(X, Y);
		}
	}

	glEnd();
	//glEnable(GL_LIGHTING);
}

void HeightMap::BindTextures()
{
	glBindTexture(GL_TEXTURE_2D, Texture);
}

void HeightMap::SetStepSize(int StepSize)
{
	this->StepSize = StepSize;
}

GVector HeightMap::GetVertex(int X, int Z)
{
	X = X >= 0 ? X : 0;
	X = X < MapWidth ? X : MapWidth - 1;
	Z = Z >= 0 ? Z : 0;
	Z = Z < MapHeight ? Z : MapHeight - 1;

	GVector Vertex;
	Vertex.x = X;
	Vertex.z = Z;
	Vertex.y = HeightMapBytes[X][Z];

	return Vertex;
}
