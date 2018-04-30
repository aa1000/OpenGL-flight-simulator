
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <Math.h>
#include <iostream>
#include <vector>
#include "GVector.h"
#include "RenderedObject.h"
#include "Mesh.h"
#include "Definitions.h"
#include "Camera.h"
#include "HeightMap.h"
//#include <md2.h>
#pragma comment(lib, "FreeImage.lib")

using namespace std;

GLfloat AmbientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 500.0f, 2.0f, 1.0f };

//CMD2MODEL model1;

vector<RenderedObject* > RenderedObjects;

Camera camera;




void RenderTimer(int Dif)
{
	glutTimerFunc(33, RenderTimer, 33);
	glutPostRedisplay();
}

void Resize(int width, int height)
{
	height = height > 0 ? height : 1;

	float AR = width / height;

	glMatrixMode(GL_PROJECTION); //load projection matrix to change resolution and mapping, GL_MODELVIEW for the screen matrix
	glLoadIdentity(); // to reset all rotation etc in memory

	glViewport(0, 0, width, height);
	gluPerspective(__FOV__, AR, 1.0f, __SCENE_DEPTH__);


	glMatrixMode(GL_MODELVIEW); // to show changes o nthe screen
	glLoadIdentity();
}

void ApplyTexture(GLuint Texture, int Width, int Height)
{
	//glBindTexture(GL_TEXTURE_2D, Texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // can have gl_nearst for faster computation
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////texture type, texture quality (0 highest), image type, border width, image format, sign and size for bytes
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Width, Heightight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, FreeImage_GetBits(fimg));
}

void KeyboradFunc(unsigned char k, int x, int y) // uses ASCII
{
	/*if (k == 'a')
		ActiveObj->Rot.ZAngle += 1;
	if (k == 'd')
		ActiveObj->Rot.ZAngle -= 1;
	if (k == 'w')
		ActiveObj->Rot.YAngle += 1;
	if (k == 's')
		ActiveObj->Rot.YAngle -= 1;*/
}

void SpecialFunc(int k, int x, int y) // uss UTF
{
	/*if (k == GLUT_KEY_LEFT)
	ActiveObj->Location.x -= 1;
	if (k == GLUT_KEY_RIGHT)
	ActiveObj->Location.x += 1;*/
	if (k == GLUT_KEY_LEFT)
	{
		camera.RotateLeft();
	}
	if (k == GLUT_KEY_RIGHT)
	{
		camera.RotateRight();
	}
	/*if (k == GLUT_KEY_UP)
	ActiveObj->Location.y += 1;
	if (k == GLUT_KEY_DOWN)
	ActiveObj->Location.y -= 1;*/
	if (k == GLUT_KEY_UP)
	{
		camera.MoveForward();
	}
	if (k == GLUT_KEY_DOWN)
	{
		camera.MoveBackwards();
	}
	if (k == GLUT_KEY_PAGE_UP)
	{
		camera.MoveUp();

	}
	if (k == GLUT_KEY_PAGE_DOWN)
	{
		camera.MoveDown();
	}


}

float animationTimer = 0;
void Draw()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(25/255.0, 50/255.0, 95/255.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//gluLookAt(CameraLoc.x, CameraLoc.y, CameraLoc.z, CameraLoc.x + CameraTilt.XAngle, CameraLoc.y, CameraLoc.z + CameraTilt.ZAngle, 0, 1, 0);
	camera.RenderLookAt();

	for (int i = 0; i < RenderedObjects.size(); i++)
		RenderedObjects[i]->Render();


	//glPushMatrix();
	//model1.DrawModel(animationTimer += 0.01);
	//glPopMatrix();

	glutSwapBuffers();

}

void InitWindow()
{
	
}

void InitLighting()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, AmbientLight);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void InitFog()
{
	GLfloat FogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, FogColor);
	glFogf(GL_FOG_DENSITY, 0.45f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, __SCENE_DEPTH__ / 6);

	glEnable(GL_FOG);
}

void Init()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(__WINDOW_WIDTH__, __WINDOW_HEIGHT__);

	glutCreateWindow(__GAME_NAME__);
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyboradFunc);
	glutSpecialFunc(SpecialFunc);

	glutTimerFunc(33, RenderTimer, 33);
	

	//init
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_TEXTURE_2D);
	InitLighting();
	InitFog();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_POLYGON_SMOOTH);

	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_ALPHA_TEST);
}

void LoadObjects()
{
	HeightMap* HM = new HeightMap(1);
	//HM->SetStepSize(1);
	HM->Load("map2.jpg");
	HM->SetScale(0.8);
	RenderedObjects.push_back(HM);

	Mesh* Apple = new Mesh();
	Apple->SetScale(0.25);
	Apple->Load("apple.obj");
	RenderedObjects.push_back(Apple);

	

	//model1.LoadModel("Ogros.md2");
	//model1.LoadSkin("igdosh.jpg");
	//model1.ScaleModel(0.25);
	//model1.SetAnim(0);
}

void Destruct()
{
	for (int i = 0; i < RenderedObjects.size(); i++)
		delete RenderedObjects[i];
}

int main(int argc, char *argv[])
{
	cout << "Loading ....";

	glutInit(&argc, argv);
	Init();
	LoadObjects();
	
	

	glutMainLoop();


	Destruct();
	return 0;
}