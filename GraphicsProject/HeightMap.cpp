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

	CalculateNormals();
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
	A = GetVertex(0, MapHeight - StepSize);
	B = GetVertex(StepSize, MapHeight - StepSize);
	C = GetVertex(0, MapHeight - StepSize);

	HeightMapNormals[0][MapHeight - StepSize] = Drawing::CalculateNormal(A, B, C);

	// Top Right
	A = GetVertex(MapWidth - StepSize, MapHeight - StepSize);
	B = GetVertex(MapWidth - StepSize -1 , MapHeight - StepSize);
	C = GetVertex(MapWidth - StepSize, MapHeight - StepSize);

	HeightMapNormals[MapHeight - StepSize][MapWidth - StepSize] = Drawing::CalculateNormal(A, B, C);

	// Bottom Left
	A = GetVertex(MapWidth - StepSize, 0);
	B = GetVertex(MapWidth - StepSize -1 , 0);
	C = GetVertex(MapWidth - StepSize, StepSize);

	HeightMapNormals[MapWidth - StepSize ][0] = Drawing::CalculateNormal(A, B, C);
}

void HeightMap::Calculate3EdgeNormals()
{
	GVector CP, RP, LP, OP;
	GVector RON, LON;
	GVector Normal;

	int X, Z;
	// Bottom Row
	Z = 0;
	for (X = StepSize; X < MapWidth-StepSize ; X+= StepSize)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X - StepSize, Z);
		// Left Point
		LP = GetVertex(X + StepSize, Z);
		// Z Point
		OP = GetVertex(X, Z + StepSize);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}

	// Top Row
	Z = MapHeight - StepSize;
	for (X = StepSize; X < MapWidth - StepSize; X+= StepSize)
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
	for (Z = StepSize; Z < MapHeight - StepSize; Z+= StepSize)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X, Z - StepSize);
		// Left Point
		LP = GetVertex(X, Z + StepSize);
		// Out Point
		OP = GetVertex(X + StepSize, Z);

		// Right Out Normal
		RON = Drawing::CalculateNormal(CP, RP, OP);
		// Left Out Normal
		LON = Drawing::CalculateNormal(CP, LP, OP);

		Normal = (RON + LON) / 2;
		HeightMapNormals[X][Z] = Normal.GetUnitVector();
	}

	// Right Coloumn
	X = MapWidth - StepSize - 1;
	for (Z = StepSize; Z < MapHeight - StepSize; Z+= StepSize)
	{
		// Centre Point
		CP = GetVertex(X, Z);
		// Right Point
		RP = GetVertex(X, Z + StepSize);
		// Left Point
		LP = GetVertex(X, Z - StepSize);
		// Out Point
		OP = GetVertex(X - StepSize, Z);

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
	for (int X = StepSize; X < MapWidth - StepSize; X+=StepSize)
	{
		for (int Z = StepSize; Z < MapHeight - StepSize; Z+= StepSize)
		{
			// Centre Point
			CP = GetVertex(X, Z);
			// Top Point
			TP = GetVertex(X, Z + StepSize );
			// Right Point
			RP = GetVertex(X + StepSize , Z);
			// Bottom Point
			BP = GetVertex(X, Z - StepSize );
			// Left Point
			LP = GetVertex(X - StepSize , Z);

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
	//Normal = CalculatePlaneNormal(X, Z);
	//glNormal3f(Normal.x, Normal.y, Normal.z);
	
	glColor3f(0, 0, 1);

	//Bottom left point
	x = X;
	z = Z;
	y = HeightMapBytes[x][z];

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
	
	Normal = HeightMapNormals[x][z];
	glNormal3f(Normal.x, Normal.y, Normal.z);

	glVertex3f(x, y, z);

	//Bottom Right
	x = X + StepSize;
	z = Z;
	y = HeightMapBytes[x][z];

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
