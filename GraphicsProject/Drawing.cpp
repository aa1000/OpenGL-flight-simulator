#include "Drawing.h"
#include "FreeImage.h"

GLuint Drawing::LoadTexture(char* filename, bool invert)
{
	GLuint Texture;

	FIBITMAP *fimg = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);
	fimg = FreeImage_ConvertTo32Bits(fimg);

	if (invert)
		FreeImage_FlipVertical(fimg);

	int width = FreeImage_GetWidth(fimg);
	int height = FreeImage_GetHeight(fimg);

	glGenTextures(1, &Texture); // number of textures, the ref to the texture uint or texture array

	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // can have gl_nearst for faster computation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//texture type, texture quality (0 highest), image type, border width, image format, sign and size for bytes
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fimg));

	FreeImage_Unload(fimg);

	return  Texture;
}

GVector Drawing::CalculateNormal(GVector A, GVector B, GVector C)
{
	GVector AC = C - A;
	GVector AB = B - A;
	GVector Cross = AC*AB;

	

	Cross = Cross.GetUnitVector();

	return Cross;
}
