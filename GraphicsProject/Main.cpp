
#include "Definitions.h"
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <iostream>

#include "GObject.h"
#include "Camera.h"
#include "HeightMap.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"

#include "Drawing.h"
#include "ParticleSystem.h"
#include "BoxParticleEmitter.h"
#include "PlayerPlane.h"
//#include <md2.h>
#pragma comment(lib, "FreeImage.lib")

using namespace std;

GLfloat AmbientLight[] = { 0.8f, 0.8f, 0.8f, 0.8f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 10, -5.0f, 1.0f };

//CMD2MODEL model1;

Camera camera;
PlayerPlane* Player;

void RenderTimer(int Dif)
{
	const int time = 1000 / __FPS__;
	glutTimerFunc(time, RenderTimer, time);
	PhysicsEngine::Simulate(time / 1000.0); // to milli secs
	glutPostRedisplay();
}

void Resize(int width, int height)
{
	height = height > 0 ? height : 1;

	float AR = (float)width / height;
	
	glMatrixMode(GL_PROJECTION); //load projection matrix to change resolution and mapping, GL_MODELVIEW for the screen matrix
	glLoadIdentity(); // to reset all rotation etc in memory

	glViewport(0, 0, width, height);
	gluPerspective(__FOV__, AR, 1.0f, __SCENE_DEPTH__);


	glMatrixMode(GL_MODELVIEW); // to show changes on the screen
	glLoadIdentity();
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
	if (k == GLUT_KEY_LEFT)
	{
		camera.RotateLeft();
		if (Player)
			Player->MoveLeft();
	}
	if (k == GLUT_KEY_RIGHT)
	{
		camera.RotateRight();
		if (Player)
			Player->MoveRight();
	}
	if (k == GLUT_KEY_UP)
	{
		camera.MoveForward();
		if (Player)
			Player->Accelerate();
	}
	if (k == GLUT_KEY_DOWN)
	{
		camera.MoveBackwards();
		if (Player)
			Player->Break();
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

void Draw()
{
	glClearColor(0, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderingEngine::Render();

	glutSwapBuffers();

}

void InitLighting()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
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

	glutTimerFunc(1000 / __FPS__, RenderTimer, 1000 / __FPS__);
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_TEXTURE_2D);

	
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);

	InitLighting();
	//InitFog();
}

void LoadObjects()
{


	HeightMap* HM = new HeightMap(true); 
	HM->SetTexture(Drawing::LoadTexture("SnowMap.png"));
	//HM->SetStepSize(1);
	HM->Load("map2.jpg");
	//HM->SetScale(1);
	//HM->Location.y = -100;

	//Mesh* Apple = new Mesh(true);
	//Apple->SetAngle(90);
	//Apple->SetRoation(GVector(0, 1, 0));
	////Apple->SetScale(.25);
	//Apple->Load("A6M_ZERO.obj");

	//PhysicsObject* Phy = new PhysicsObject(&camera, 0.001);
	//Phy->AddRelativeLocation(-10, 4, 0);
	//Phy->SetVelocity(GVector(5, 0, 0));

	Player = new PlayerPlane();

	ParticleSystem* PS = new ParticleSystem;
	PS->SetMass(0.01);
	PS->AddTexture("snowflake0.png");
	PS->AddTexture("snowflake1.png");
	PS->AddTexture("snowflake2.png");


	BoxParticleEmitter* PE = new BoxParticleEmitter((RenderedObject*)PS, GVector(0, 50, 0), GVector(500, 50, 500));
	PE->SetLifeTime(10, 20);
	PE->SetSpeed(1, 1);
	PE->SetSize(8, 15);
	PS->SetEmitter(PE);
	//PS->InitPaticles();
}

void Destruct()
{
}

int main(int argc, char *argv[])
{
	cout << "Loading ....";

	glutInit(&argc, argv);

	Init();
	LoadObjects();
	
	RenderingEngine::SetActiveCamera(&camera);

	glutMainLoop();


	Destruct();
	return 0;
}