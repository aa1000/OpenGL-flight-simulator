#include "HeightMap.h"
#include <FreeImage.h>
#include "Drawing.h"

HeightMap::HeightMap()
	:RenderedObject()
{
	MapWidth = 0;
	MapHeight = 0;
	StepSize = 4;
}

HeightMap::HeightMap(int glListIndex)
	:RenderedObject(glListIndex)
{
	MapWidth = 0;
	MapHeight = 0;
	StepSize = 4;
}

//HeightMap::HeightMap(int glListIndex)
//	:RenderedObject(glListIndex)
//{
//}

HeightMap::~HeightMap()
{
	for (int i = 0; i < MapWidth; i++)
	{
		delete[] HeightMapBytes[i];
		delete[] HeightMapNormals[i];
	}

	delete[] HeightMapBytes;
	delete[] HeightMapNormals;

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

	CalculateNormals();
	return __super::Load(FileName);
}

void HeightMap::CalculateNormals()
{
	HeightMapNormals = new GVector*[MapWidth];

	for (int X = 0; X < MapWidth; X++)
		HeightMapNormals[X] = new GVector[MapHeight];
		
	CalculateEdgeNormals();
	Calculate3EdgeNormals();
	Calculate4EdgeNormals();
	

}

void HeightMap::CalculateEdgeNormals()
{
	// bottom Left
	GVector A = GetVertex(0, 0);
	GVector B = GetVertex(1, 0);
	GVector C = GetVertex(0, 1);

	HeightMapNormals[0][0] = Drawing::CalculateNormal(A, B, C);

	// Top Left
	A = GetVertex(0, MapHeight - 1);
	B = GetVertex(1, MapHeight - 1);
	C = GetVertex(0, MapHeight - 2);

	HeightMapNormals[0][MapHeight - 1] = Drawing::CalculateNormal(A, B, C);

	// Top Right
	A = GetVertex(MapWidth - 1, MapHeight - 1);
	B = GetVertex(MapWidth -2, MapHeight - 1);
	C = GetVertex(MapWidth - 1, MapHeight - 2);

	HeightMapNormals[MapHeight - 1][MapWidth - 1] = Drawing::CalculateNormal(A, B, C);

	// Bottom Left
	A = GetVertex(MapWidth - 1, 0);
	B = GetVertex(MapWidth - 2, 0);
	C = GetVertex(MapWidth - 1, 1);

	HeightMapNormals[MapWidth -1 ][0] = Drawing::CalculateNormal(A, B, C);
}

void HeightMap::Calculate3EdgeNormals()
{
	GVector CP, RP, LP, OP;
	GVector RON, LON;
	GVector Normal;

	int X, Z;
	// Bottom Row
	Z = 0;
	for (X = 1; X < MapWidth-1 ; X++)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X - 1, Z);
		// Left Point
		LP = GetVertex(X + 1, Z);
		// Z Point
		OP = GetVertex(X, Z +1);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}

	// Top Row
	Z = MapHeight - 1;
	for (X = 1; X < MapWidth - 1; X++)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X - 1, Z);
		// Left Point
		LP = GetVertex(X + 1, Z);
		// Z Point
		OP = GetVertex(X, Z - 1);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}

	// Left Coloumn
	X = 0;
	for (Z = 1; Z < MapHeight - 1; Z++)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X, Z - 1);
		// Left Point
		LP = GetVertex(X, Z + 1);
		// Out Point
		OP = GetVertex(X + 1, Z);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}

	// Right Coloumn
	X = MapWidth - 1;
	for (Z = 1; Z < MapHeight - 1; Z++)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X, Z + 1);
		// Left Point
		LP = GetVertex(X, Z - 1);
		// Out Point
		OP = GetVertex(X - 1, Z);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}
}

void HeightMap::Calculate4EdgeNormals()
{
	GVector CP, TP, RP, BP, LP;
	GVector TRN, RBN, BLN, LTN;
	GVector Normal;
	for (int X = 1; X < MapWidth - 1; X++)
	{
		for (int Z = 1; Z < MapHeight - 1; Z++)
		{
			// Centre Point
			CP = GetVertex(X, Z);
			// Top Point
			TP = GetVertex(X, Z + 1);
			// Right Point
			RP = GetVertex(X + 1, Z);
			// Bottom Point
			BP = GetVertex(X, Z - 1);
			// Left Point
			LP = GetVertex(X - 1, Z);

			// Top Right Normal
			TRN = Drawing::CalculateNormal(CP, TP, RP);
			// Right Bottom Normal
			RBN = Drawing::CalculateNormal(CP, RP, BP);
			// Bottom Left Normal
			BLN = Drawing::CalculateNormal(CP, BP, LP);
			// Left Top Normal
			LTN = Drawing::CalculateNormal(CP, LP, TP);

			Normal = (TRN + RBN + BLN + LTN) / 4;
			HeightMapNormals[X][Z] = Normal.GetUnitVector();
		}
	}
}

void HeightMap::BuildPolygon(const int & X, const int & Z)
{
	int x, y, z;
	GVector Normal;
	//Bottom left point
	x = X;
	z = Z;
	y = HeightMapBytes[x][z];
	glColor3f(1, 0, 0);
	Normal = HeightMapNormals[x][z];
	glNormal3f(Normal.x, Normal.y, Normal.z);

	glVertex3f(x, y, z);

	//Top Left Point
	x = X;
	z = Z + StepSize;
	y = HeightMapBytes[x][z];

	Normal = HeightMapNormals[x][z];
	glNormal3f(Normal.x, Normal.y, Normal.z);
	
	glVertex3f(x, y, z);

	//Top right
	x = X + StepSize;
	z = Z + StepSize;
	y = HeightMapBytes[x][z];
	glColor3f(1, 0, 0);
	Normal = HeightMapNormals[x][z];
	glNormal3f(Normal.x, Normal.y, Normal.z);

	glVertex3f(x, y, z);

	//Bottom Right
	x = X + StepSize;
	z = Z;
	y = HeightMapBytes[x][z];
	glColor3f(1, 0, 0);
	Normal = HeightMapNormals[x][z];
	glNormal3f(Normal.x, Normal.y, Normal.z);
	
	glVertex3f(x, y, z);
}

void HeightMap::Build()
{
	//glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	for (int X = 0; X < MapWidth - StepSize; X += StepSize)
	{
		for (int Y = 0; Y < MapHeight - StepSize; Y += StepSize)
		{
			BuildPolygon(X, Y);
		}
	}

	glEnd();
	//glEnable(GL_LIGHTING);
}

void HeightMap::SetStepSize(int StepSize)
{
	this->StepSize = StepSize;
}

GVector HeightMap::GetVertex(const int& X, const int& Z)
{
	GVector Vertex;
	Vertex.x = X;
	Vertex.z = Z;
	Vertex.y = HeightMapBytes[X][Z];

	return Vertex;
}
