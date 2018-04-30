#include "Mesh.h"
#include "Drawing.h"


Mesh::Mesh()
	:RenderedObject()
{
	//glListIndex = -1;
}

Mesh::Mesh(int glListIndex)
	:RenderedObject(glListIndex)
{
	this->glListIndex = glListIndex;
}

bool Mesh::Load(char* FileName)
{
	int TextureLocation = -1;
	FILE *in = fopen(FileName, "r");
	if (!in)
		return false;

	char header[100]; // read the heading of the file (ex first character "v"
	while (fscanf(in, "%s", header) != EOF)
	{
		if (!strcmp(header, "v"))
		{
			GVector pt;
			fscanf(in, "%f%f%f", &pt.x, &pt.y, &pt.z);
			vertices.push_back(pt);
		}
		if (!strcmp(header, "vt"))
		{
			GVector pt;
			fscanf(in, "%f%f%f", &pt.x, &pt.y, &pt.z);
			textures.push_back(pt);
		}
		if (!strcmp(header, "vn"))
		{
			GVector pt;
			fscanf(in, "%f%f%f", &pt.x, &pt.y, &pt.z);
			normals.push_back(pt);
		}
		if (!strcmp(header, "o"))
		{
			char TextureName[40];
			fscanf(in, "%s", TextureName);

			texs.push_back(Drawing::LoadTexture(TextureName));
			TextureLocation++;
		}
		if (!strcmp(header, "f"))
		{
			Face f;

			int av = -1, bv = -1, cv = -1, dv = -1;
			int at = -1, bt = -1, ct = -1, dt = -1;
			int an = -1, bn = -1, cn = -1, dn = -1;

			char FaceLine[100];
			fgets(FaceLine, 99, in);

			sscanf(FaceLine, " %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&av, &at, &an, &bv, &bt, &bn, &cv, &ct, &cn, &dv, &dt, &dn);

			if (bv == -1)
			{
				sscanf(FaceLine, " %d/%d %d/%d %d/%d %d/%d",
					&av, &at, &bv, &bt, &cv, &ct, &dv, &dt);
				an = bn = cn = dn = 0;
			}

			f.a = vertices[av - 1];
			f.b = vertices[bv - 1];
			f.c = vertices[cv - 1];

			f.at = textures[at - 1];
			f.bt = textures[bt - 1];
			f.ct = textures[ct - 1];

			if (normals.size() > 0)
			{
				f.an = normals[an - 1];
				f.bn = normals[bn - 1];
				f.cn = normals[cn - 1];
			}

			if (dv != -1)
			{
				f.type = 2;

				f.d = vertices[dv - 1];
				f.dt = textures[dt - 1];


				if (normals.size() > 0)
					f.dn = normals[dn - 1];


			}
			f.TextureIndex = TextureLocation;
			faces.push_back(f);
		}

	}

	
	return __super::Load(FileName);
}

void Mesh::Build()
{
	for (int i = 0; i < faces.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, texs[faces[i].TextureIndex]);
		if (faces[i].type == 1)
		{
			glBegin(GL_TRIANGLES);

			glTexCoord2d(faces[i].at.x, faces[i].at.y);
			glNormal3f(faces[i].an.x, faces[i].an.y, faces[i].an.z);
			glVertex3f(faces[i].a.x, faces[i].a.y, faces[i].a.z);

			glTexCoord2d(faces[i].bt.x, faces[i].bt.y);
			glNormal3f(faces[i].bn.x, faces[i].bn.y, faces[i].bn.z);
			glVertex3f(faces[i].b.x, faces[i].b.y, faces[i].b.z);

			glTexCoord2d(faces[i].ct.x, faces[i].ct.y);
			glNormal3f(faces[i].cn.x, faces[i].cn.y, faces[i].cn.z);
			glVertex3f(faces[i].c.x, faces[i].c.y, faces[i].c.z);

		}
		if (faces[i].type == 2)
		{
			glBegin(GL_QUADS);

			glTexCoord2d(faces[i].at.x, faces[i].at.y);
			glNormal3f(faces[i].an.x, faces[i].an.y, faces[i].an.z);
			glVertex3f(faces[i].a.x, faces[i].a.y, faces[i].a.z);

			glTexCoord2d(faces[i].bt.x, faces[i].bt.y);
			glNormal3f(faces[i].bn.x, faces[i].bn.y, faces[i].bn.z);
			glVertex3f(faces[i].b.x, faces[i].b.y, faces[i].b.z);

			glTexCoord2d(faces[i].ct.x, faces[i].ct.y);
			glNormal3f(faces[i].cn.x, faces[i].cn.y, faces[i].cn.z);
			glVertex3f(faces[i].c.x, faces[i].c.y, faces[i].c.z);

			glTexCoord2d(faces[i].dt.x, faces[i].dt.y);
			glNormal3f(faces[i].dn.x, faces[i].dn.y, faces[i].dn.z);
			glVertex3f(faces[i].d.x, faces[i].d.y, faces[i].d.z);

		}

		glEnd();
	}

}

