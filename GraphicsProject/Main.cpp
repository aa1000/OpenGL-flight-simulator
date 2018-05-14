
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
#include "SkyShpere.h"
#include "FollowCamera.h"
#include "ResourceManager.h"
#include "SphereParticleEmitter.h"
//#include <md2.h>
#pragma comment(lib, "FreeImage.lib")

using namespace std;

GLfloat AmbientLight[] = { 0.8f, 0.8f, 0.8f, 0.8f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 10, -5.0f, 1.0f };

//CMD2MODEL model1;
ResourceManager RM;

Camera camera;
PlayerPlane* Player;

bool Inputs[10];

void UpdateInputs()
{
	if (Inputs[0])
	{
		camera.RotateLeft();
		if (Player)
			Player->MoveLeft();
	}

	if (Inputs[1])
	{
		camera.RotateRight();
		if (Player)
			Player->MoveRight();
	}

	if (Inputs[2])
	{
		camera.MoveForward();
		if (Player)
			Player->MoveUp();
	}

	if(Inputs[3])
	{
		camera.MoveBackwards();
		if (Player)
			Player->MoveDown();
	}

	if(Inputs[4])
	{
		camera.MoveUp();
	}
	if(Inputs[5])
	{
		camera.MoveDown();
	}
	if (Inputs[6])
	{
		if (Player)
			Player->Accelerate();
	}
	if (Inputs[7])
	{
		if (Player)
			Player->Break();
	}
	if (Inputs[8])
	{
		if (Player)
			Player->Shoot();
	}
	else
	{
		if (Player)
			Player->StopShooting();
	}
}
void RenderTimer(int Dif)
{
	const int time = 1000 / __FPS__;
	glutTimerFunc(time, RenderTimer, time);
	UpdateInputs();
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
	if (k == 'w')
		Inputs[6] = true;
	if (k == 's')
		Inputs[7] = true;
	if (k == ' ')
		Inputs[8] = true;
}

void KeyboradUpFunc(unsigned char k, int x, int y) // uses ASCII
{
	if (k == 'w')
		Inputs[6] = false;
	if (k == 's')
		Inputs[7] = false;
	if (k == ' ')
		Inputs[8] = false;
}

void SpecialFunc(int k, int x, int y) // uss UTF
{
	if (k == GLUT_KEY_LEFT)
		Inputs[0] = true;

	if (k == GLUT_KEY_RIGHT)
		Inputs[1] = true;

	if (k == GLUT_KEY_UP)
		Inputs[2] = true;

	if (k == GLUT_KEY_DOWN)
		Inputs[3] = true;
	
	if (k == GLUT_KEY_PAGE_UP)
		Inputs[4] = true;

	if (k == GLUT_KEY_PAGE_DOWN)
		Inputs[5] = true;
}

void SpecialUpFunc(int k, int x, int y) // uss UTF
{
	if (k == GLUT_KEY_LEFT)
		Inputs[0] = false;

	if (k == GLUT_KEY_RIGHT)
		Inputs[1] = false;

	if (k == GLUT_KEY_UP)
		Inputs[2] = false;

	if (k == GLUT_KEY_DOWN)
		Inputs[3] = false;

	if (k == GLUT_KEY_PAGE_UP)
		Inputs[4] = false;

	if (k == GLUT_KEY_PAGE_DOWN)
		Inputs[5] = false;
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
	glFogf(GL_FOG_DENSITY, 0.25f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, __SCENE_DEPTH__ );

	glEnable(GL_FOG);
}


void Init()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(__WINDOW_WIDTH__, __WINDOW_HEIGHT__);

	glutCreateWindow(__GAME_NAME__);
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyboradFunc);
	glutKeyboardUpFunc(KeyboradUpFunc);
	glutSpecialFunc(SpecialFunc);
	glutSpecialUpFunc(SpecialUpFunc);

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
	InitFog();
}

void LoadObjects()
{

	
	HeightMap* HM = new HeightMap(true); 
	HM->SetTexture(Drawing::LoadTexture("SnowMap.png"));
	//HM->SetStepSize(1);
	HM->Load("map2.jpg");
	//HM->SetScale(1);
	HM->AddRelativeLocation(0, -100, -200);
	
	Player = new PlayerPlane();

	SkyShpere* SS = new SkyShpere(Player->GetPlaneMesh(), 1500);
	SS->Load("kiara.jpg");

	ParticleSystem* PS = new ParticleSystem();
	PS->SetMass(0.01);
	PS->AddTexture("snowflake0.png");
	PS->AddTexture("snowflake1.png");
	PS->AddTexture("snowflake2.png");
	GVector Acc(0, -PhysicsEngine::GetGravity(), 0);
	PS->SetAcceleration(Acc);

	BoxParticleEmitter* PE = new BoxParticleEmitter((RenderedObject*)PS, GVector(0, 50, -200), GVector(500, 50, 500));
	PE->SetLifeTime(10, 20);
	PE->SetSpeed(1, 1);
	PE->SetSize(5, 15);
	PE->SetAngularVelocity(10, 30);
	PE->SetFadingOverTime(0, 0);
	PS->SetEmitter(PE);

	ParticleSystem *Bullets = new ParticleSystem(Player->GetPlaneMesh(), 100);
	Bullets->SetNewParticles(1);
	Bullets->SetMass(0);
	Bullets->AddTexture("bullet.jpg");
	
	Bullets->SetAcceleration(GVector(10, 0, 0));

	SphereParticleEmitter* SPE = new SphereParticleEmitter(Player->GetPlaneMesh());
	SPE->SetLifeTime(3, 3);
	SPE->SetStartVelocity(GVector(25, 0, 0), GVector(25, 0, 0));
	SPE->SetSize(1, 1);
	SPE->SetAngularVelocity(0, 0);
	SPE->SetAngle(-45, -45);
	SPE->SetParticleRotation(GVector(1, 0, 0), GVector(1, 0, 0));
	SPE->SetOffset(GVector(3, -1, 0));
	Bullets->SetEmitter(SPE);

	Player->SetBullets(Bullets);

	ParticleSystem *Smoke = new ParticleSystem(Player->GetPlaneMesh(), 300);
	Smoke->SetSortToCamera(true);
	Smoke->SetNewParticles(1);
	Smoke->SetMass(0);
	Smoke->AddTexture("smoke01.png");
	Smoke->AddTexture("smoke02.png");


	SphereParticleEmitter* SmokePE = new SphereParticleEmitter(Player->GetPlaneMesh(), 1);
	SmokePE->SetFadingOverTime(0.8, 0.8);
	SmokePE->SetLifeTime(3.5, 4.5);
	SmokePE->SetSize(1, 1);
	SmokePE->SetAngularVelocity(0, 0);
	SmokePE->SetAngle(45, 45);
	SmokePE->SetParticleRotation(GVector(0, 1, 0), GVector(0, 1, 0));
	SmokePE->SetOffset(GVector(0, 0, 7));
	SmokePE->SetColour(GVector(0.2, 0.2, 0.2), GVector(0.7, 0.7, 0.7));
	Smoke->SetEmitter(SmokePE);

	FollowCamera* cam = new FollowCamera(Player);
	RenderingEngine::SetActiveCamera(cam);
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
	
	//RenderingEngine::SetActiveCamera(&camera);

	glutMainLoop();


	Destruct();
	return 0;
}