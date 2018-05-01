#pragma once
#include "RenderedObject.h"

class HeightMap : public RenderedObject
{
	int MapWidth;
	int MapHeight;
	int StepSize;

	BYTE **HeightMapBytes;
	GVector  **HeightMapNormals;

	GVector CalculatePlaneNormal(const int & X, const int & Z);
	void CalculateNormals();
	void CalculateEdgeNormals();
	void Calculate3EdgeNormals();
	void Calculate4EdgeNormals();
	void BuildPolygon(const int & X, const int & Z);
	

public:
	HeightMap();
	HeightMap(int glListIndex);
	~HeightMap();
	virtual bool Load(char* FileName) override;
	virtual void Build() override;
	void SetStepSize(int StepSize);
	GVector GetVertex(const int & X, const int & Z);
};
