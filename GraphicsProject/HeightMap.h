#pragma once
#include "RenderedObject.h"

class HeightMap : public RenderedObject
{
	int MapWidth;
	int MapHeight;
	int StepSize;
	GLuint Texture;

	BYTE **HeightMapBytes;
	GVector  **HeightMapNormals;

	GVector CalculatePlaneNormal(const int & X, const int & Z);
	void CalculateNormals();
	void CalculateEdgeNormals();
	void Calculate3EdgeNormals();
	void Calculate4EdgeNormals();
	GVector CalculateEdgeNormal(const int & X, const int & Z);
	GVector CalculateNormal(const int & X, const int & Z);
	void BuildPolygon(const int & X, const int & Z);
	

public:
	HeightMap();
	HeightMap(bool RenderInList);
	~HeightMap();

	void SetTexture(const GLuint & Texture);
	virtual void BindTextures() override;
	virtual bool Load(char* FileName) override;
	virtual void Build() override;
	void SetStepSize(int StepSize);
	GVector GetVertex(int X, int Z);
};
