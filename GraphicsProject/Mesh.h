#pragma once

#include "vector"
#include "RenderedObject.h"

using namespace std;
struct Face
{
	GVector a, b, c, d;
	GVector an, bn, cn, dn;
	GVector at, bt, ct, dt;

	int type;
	int TextureIndex;

	Face()
	{
		a.init(-1);
		b.init(-1);
		c.init(-1);
		d.init(-1);
		an.init(-1);
		bn.init(-1);
		cn.init(-1);
		dn.init(-1);
		at.init(-1);
		bt.init(-1);
		ct.init(-1);
		dt.init(-1);
		type = 1; // Default Triangle
	}

};

class Mesh : public RenderedObject
{
public:
	vector<GVector> vertices;
	vector<GVector> normals;
	vector<GVector> textures;

	vector<Face> faces;
	vector<GLuint> texs;


	Mesh();
	Mesh(bool RenderInList);
	~Mesh();

	virtual bool Load(char* FileName) override;
	virtual void Build() override;
};