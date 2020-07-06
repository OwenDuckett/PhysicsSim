#include "Game.h"
#include <gl\gl.h>                                // Header File For The OpenGL32 Library
#include <gl\GLU.h>
#include "Vector3f.h"
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
Circle circleArray[9];
Plane planeArray[9];
float eyeX = 0;
float eyeY = -1;
float eyeZ = 5;
float centerX = 0;
float centerY = -1;
float centerZ = -2;
float upX = 0;
float upY = 1;
float upZ = 0;
//gluLookAt(0, -1, 5, 0, -1, -2, 0, 1, 0);
int spheres = 0;
using namespace std;
Game::Game(HDC hdc) : m_hdc(hdc), m_previousTime(0)
{
	m_dtScale = 1.0f;
/*	m_sphere1 = new Sphere();
	m_sphere1->SetPos(-0.3, 1.50f, 0);
	m_sphere1->SetVel(2.0f,1.0f, 0.5f);
    m_sphere1->SetMass(0.02f);*/

	circle1 = new Circle(Vector3f(-0.3f, 0.0f, -0.3f), 0.1f);
	circle2 = new Circle(Vector3f(0.0f, 0.0f, -0.3f), 0.1f);
	circle3 = new Circle(Vector3f(0.3f, 0.0f, -0.3f), 0.1f);
	circle4 = new Circle(Vector3f(-0.3f, 0.0f, 0.0f), 0.1f);
	circle5 = new Circle(Vector3f(0.0f, 0.0f, 0.0f), 0.1f);
	circle6 = new Circle(Vector3f(0.3f, 0.0f, 0.0f), 0.1f);
	circle7 = new Circle(Vector3f(-0.3f, 0.0f, 0.3f), 0.1f);
	circle8 = new Circle(Vector3f(0.0f, 0.0f, 0.3f), 0.1f);
	circle9 = new Circle(Vector3f(0.3f, 0.0f, 0.3f), 0.1f);
/*	m_sphere2 = new Sphere();
	m_sphere2->SetPos(-0.45f,-1.20f, 0.0);
	m_sphere2->SetVel(0.01f,0.6f,1.0f);
	m_sphere2->SetMass(0.02f);

	m_sphere3 = new Sphere();
	m_sphere3->SetPos(0,-0.7f, 0);
	m_sphere3->SetVel(1.0f, 0.0f, 0.40f);
	m_sphere3->SetMass(0.02f);*/

	m_bowl = new Sphere(0, 2.73f);
	m_bowl->SetPos(0, 0.0, 0);
	m_bowl->SetVel(0.00f, 0, 0);
	m_bowl->SetMass(0.00f);


	//m_planeBase = new Plane(10, 10, Vector3f(0, 0, 0), false, -20, false);
	m_planeLeft = new Plane(10, 15, Vector3f(-5, 0, 0), true, -12.5f, false);
	m_planeRight = new Plane(10, 15, Vector3f(5, 0, 0), true, -12.5f, false);
//	m_planeTop = new Plane(10, 10, Vector3f(0, 0, 0), false, -5, false);
	m_topTray = new Plane(10, 10, Vector3f(0, 0, 0), false, -8, false);
	m_middleTray = new Plane(10, 10, Vector3f(0, 0, 0), false, -12.5f, false);
	m_bottomTray = new Plane(10, 10, Vector3f(0, 0, 0), false, -17, false);
	m_planeFront = new Plane(10, 15, Vector3f(0, 5, 0), false, -12.5f, true);
	m_planeBack = new Plane(10, 15, Vector3f(0, -5, 0), false, -12.5f, true);

	m_moveTop = false;

	//planeArray[0] = *m_planeBase;
//	planeArray[1] = *m_planeTop;
	
	planeArray[2] = *m_middleTray;

	m_middleTray->setArrayPos(2);

	planeArray[3] = *m_topTray;

	m_topTray->setArrayPos(3);

	planeArray[4] = *m_bottomTray;

	m_bottomTray->setArrayPos(4);

	planeArray[5] = *m_planeLeft;

	m_middleTray->setArrayPos(2);

	planeArray[6] = *m_planeRight;	

	m_middleTray->setArrayPos(2);

	planeArray[7] = *m_planeFront;

	m_middleTray->setArrayPos(2);

	planeArray[8] = *m_planeBack; 

	m_middleTray->setArrayPos(2);
	
	circleArray[0] = *circle1;
	circleArray[1] = *circle2;
	circleArray[2] = *circle3;
	circleArray[3] = *circle4;
	circleArray[4] = *circle5;
	circleArray[5] = *circle6;
	circleArray[6] = *circle7;
	circleArray[7] = *circle8;
	circleArray[8] = *circle9;
	m_manifold = new ContactManifold();
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

}
Game::~Game(void)
{
	//delete m_sphere1;
	//delete m_sphere2;
	//delete m_sphere3;

	delete m_spheres;

	delete m_bowl;
	delete m_manifold;
	//delete m_planeBase;
	delete m_planeLeft;
	delete m_planeRight;
	//delete m_planeTop;
	delete m_topTray;
	delete m_middleTray;
	delete m_planeFront;
	delete m_planeBack;
	delete circle1;
	delete circle2;
	delete circle3;
	delete circle4;
	delete circle5;
	delete circle6;
	delete circle7;
	delete circle8;
	delete circle9;
}
void Game::AddSphere()
{
	srand(time(NULL));
	float pos;
	float randVelX;
	float randVelY;
	float randVelZ;
	cout << "\nNo. of spheres: " << spheres;
	pos = (rand() % 3);
	if (pos == 2)
	{
		randVelX = (rand() % 100) * 0.01f;
	}
	else
	{
		randVelX = (rand() % 100) * -0.01f;
	}
	pos = (rand() % 3);
	if (pos == 2)
	{
		randVelY = (rand() % 100) * 0.01f;
	}
	else
	{
		randVelY = (rand() % 100) * -0.01f;
	}
	pos = (rand() % 3);
	if (pos == 2)
	{
		randVelZ = (rand() % 100) * 0.01f;
	}
	else
	{
		randVelZ = (rand() % 100) * -0.01f;
	}
	
	m_spheres[spheres] = new Sphere();
	m_spheres[spheres]->SetPos(0, -0.44f, 0);
	m_spheres[spheres]->SetVel(randVelX, randVelY, randVelZ);
	m_spheres[spheres]->SetMass(0.02f);
	spheres++;
}
void Game::ChangeAbsolutes(char c)
{
	if (c == 'i')
	{
		m_spheres[0]->ChangeFC(0.1f);
	}
	if (c == 'k')
	{
		m_spheres[0]->ChangeFC(-0.1f);
	}
	if (c == 'o')
	{
		m_spheres[0]->ChangeCOE(0.1f);
	}
	if (c == 'l')
	{
		m_spheres[0]->ChangeCOE(-0.1f);
	}
}
void Game::Reset()
{
	m_topTray = new Plane(10, 10, Vector3f(0, 0, 0), false, -8, false);
	m_bottomTray = new Plane(10, 10, Vector3f(0, 0, 0), false, -17, false);
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i] = m_delete;
	}
	spheres = 0;
	
}
int stopped = 1;
void Game::UpdateTime(char key)
{
	if (key == 'u')
	{
		m_dtScale = m_dtScale + 0.01f;
	}
	if (key == 'j')
	{
		m_dtScale = m_dtScale - 0.01f;
	}
	if (key == 'y')
	{
		m_dtScale = 1.0f;
	}
	if (key == 'p')
	{
		stopped = stopped * -1;
		if (stopped < 0)
		{
			m_dtScale = 0.0f;
		}
		else
		{
			m_dtScale = 1.0f;
		}
	}
}
void Game::Update()
{
	// **************************************************
	// The simulation loop should be on its own thread(s)
	// **************************************************
	//planeArray[1] = *m_planeTop;
	planeArray[2] = *m_middleTray;
	planeArray[3] = *m_topTray;
	planeArray[4] = *m_bottomTray;
	planeArray[5] = *m_planeLeft;
	planeArray[6] = *m_planeRight;
	planeArray[7] = *m_planeFront;
	planeArray[8] = *m_planeBack;
	circleArray[0] = *circle1;
	circleArray[1] = *circle2;
	circleArray[2] = *circle3;
	circleArray[3] = *circle4;
	circleArray[4] = *circle5;
	circleArray[5] = *circle6;
	circleArray[6] = *circle7;
	circleArray[7] = *circle8;
	circleArray[8] = *circle9;
	SimulationLoop();
	Render();
}

void Game::UpdateTray(int key)
{
	switch (key)
	{
	case 3:
		m_moveTop = true;
		break;
	case 4:
		m_resetTop = true;
		break;
	case 5:
		m_moveBottom = true;
		break;
	case 6:
		m_resetBottom = true;
		break;
	default:
		break;
	}

}
void Game::UpdateCamera(char key)
{
	switch (key)
	{
	case 'w':
		eyeY = eyeY + 0.02f;
		centerY = centerY + 0.02f;
		break;
	case 'a':
		eyeX = eyeX - 0.02f;
		centerX = centerX - 0.02f;
		break;

	case 's':
		eyeY = eyeY - 0.02f;
		centerY = centerY - 0.02f;
		break;

	case 'd':
		eyeX = eyeX + 0.02f;
		centerX = centerX + 0.02f;
		break;
	case 'u':
		eyeZ = eyeZ - 0.02f;
		break;
	case 'n':
		eyeZ = eyeZ + 0.02f;
		break;
	default:
		break;
	}
}

void Game::SimulationLoop()
{
	// calculate dt based on the simulation loop rate using a timer
	QueryPerformanceCounter(&end);
	m_dt = static_cast<float>((end.QuadPart - start.QuadPart) / static_cast<double>(frequency.QuadPart)*m_dtScale);
	start = end;

	m_fps = static_cast<int>(1.0 / m_dt);

	// Calculate the physic calculations on all objects (e.g. new position, velocity, etc)
	CalculateObjectPhysics();

	// Clear the manifold so that we can calculate all collisions for this simulation loop
	m_manifold->Clear();
	// Find dynamic collisions for all objects and add to contact manifold 
	DynamicCollisionDetection();

	// Handle dynamic collision responses using the contact manifold
	DynamicCollisionResponse();

	// Update the physics calculations on all objects (e.g. new position, velocity, etc)
	UpdateObjectPhysics();
	/*Vector3f pos1 = contactID1->GetNewPos();
	Vector3f pos2 = contactID2->GetNewPos();
	float dist = pos1.distance(pos2) - (point.contactID1->GetRadius() + point.contactID2->GetRadius());
	if (dist < 0.0f)
	{
		cout << "here";
	}*/
}

//**************************Update the physics calculations on each object***********************
void Game::CalculateObjectPhysics()
{
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i]->CalculatePhysics(m_dt);
	}
	/*m_sphere1->CalculatePhysics(m_dt);
	m_sphere2->CalculatePhysics(m_dt);
	m_sphere3->CalculatePhysics(m_dt);*/
}

//**************************Handle dynamic collisions***********************
void Game::DynamicCollisionDetection()
{
	
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i]->CollisionWithPlane(planeArray, circleArray, m_manifold, m_dt);
	}
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i]->CollisionWithBowl(m_bowl, m_manifold, m_dt);
	}
	for (int i = 0; i < spheres; i++)
	{
		if (spheres != 1)
		{
			for (int o = i + 1; o < spheres; o++)
			{
				m_spheres[i]->CollisionWithSphere(m_spheres[o], m_manifold, m_dt);
			}
		}
	}
/*	m_sphere1->CollisionWithPlane(planeArray, circleArray,m_manifold, m_dt);
	m_sphere2->CollisionWithPlane(planeArray, circleArray, m_manifold, m_dt);
	m_sphere3->CollisionWithPlane(planeArray, circleArray, m_manifold, m_dt);
	m_sphere1->CollisionWithBowl(m_bowl, m_manifold, m_dt);
	m_sphere2->CollisionWithBowl(m_bowl, m_manifold, m_dt);
	m_sphere3->CollisionWithBowl(m_bowl, m_manifold, m_dt);

	m_sphere1->CollisionWithSphere(m_sphere2, m_manifold, m_dt);
	m_sphere1->CollisionWithSphere(m_sphere3, m_manifold, m_dt);
	m_sphere2->CollisionWithSphere(m_sphere3, m_manifold, m_dt);
	*/
	

	
	
	//m_sphere1->CollisionWithTray(planeArray, circleArray, m_dt);
	//m_sphere2->CollisionWithTray(planeArray, circleArray, m_dt);
	//m_sphere3->CollisionWithTray(planeArray, circleArray, m_dt);
	
	
}

//**************************Handle dynamic collision responses***********************
void Game::DynamicCollisionResponse()
{

	bool stuck = true;
	//while (stuck == true)
//	{
		
		for (int collision = 0; collision < m_manifold->GetNumPoints(); ++collision)
		{
			ManifoldPoint &point = m_manifold->GetPoint(collision);
			point.contactID1->CollisionResponseWithSphere(point,m_dt,circleArray);
			point.contactID1->checkActive();
		}
	

			

}

//**************************Update the physics calculations on each object***********************
void Game::UpdateObjectPhysics()
{
	if (m_moveTop == true)
	{
		m_topTray->updateX(0.00075f * m_dtScale);
		Vector3f middle = m_topTray->getMiddle();
		if (middle.GetX() >= 1.0f)
		{
			m_moveTop = false;
		}
	}
	if (m_resetTop == true)
	{
		m_topTray->updateX(-0.0015f * m_dtScale);
		Vector3f middle = m_topTray->getMiddle();
		if (middle.GetX() <= 0.0f)
		{
			m_resetTop = false;
		}
	}
	if (m_moveBottom == true)
	{
		m_spheres[0]->swapTrayValue(true,true);
		m_bottomTray->updateX(0.00075f * m_dtScale);
		Vector3f middle = m_bottomTray->getMiddle();
		if (middle.GetX() >= 1.0f)
		{
			m_spheres[0]->swapTrayValue(true,false);
			m_moveBottom = false;
		}
	}
	if (m_resetBottom == true)
	{
		m_spheres[0]->swapTrayValue(false,true);
		m_bottomTray->updateX(-0.0015f * m_dtScale);
		Vector3f middle = m_bottomTray->getMiddle();
		if (middle.GetX() <= 0.0f)
		{
			m_spheres[0]->swapTrayValue(false,false);
			m_resetBottom = false;
		}
	}
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i]->Update();
	}
	//m_sphere1->Update();
	
	//m_sphere2->Update();
	
	//m_sphere3->Update();

}

//**************************Render and display the scene in OpenGL***********************
void Game::Render()									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glDisable(GL_TEXTURE_2D);
	// Draw plane (at y=-20)
	glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glVertex3d(-50, -25, -50);
		glVertex3d( 50, -25, -50);
		glVertex3d( 50, -25,  50);
		glVertex3d(-50, -25,  50);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	
	

	glPushMatrix();
	glTranslatef(0, -2, 0);
	// Draw base (at y=-19)
	GLdouble plane[4]{ 0.0 ,-1.0,0.0 ,0.0 };
	glClipPlane(GL_CLIP_PLANE0, plane);
	glEnable(GL_CLIP_PLANE0);

	glColor3d(1, 0, 0);
	
	glTranslatef(0, 1, 0);

	//glBindTexture(GL_TEXTURE_2D, m_texture);               // Select Our Texture
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_LINE);
//	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluSphere(quadric, 2, 100, 100);
	gluDeleteQuadric(quadric);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE0);
	
/*	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3d(1, 0, 1);
	glVertex3d(-5, -19, 0);
	glVertex3d(-5, -19, 5);
	glVertex3d(5, -19, 5);
	glVertex3d(5, -19, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);*/
//	m_sphere1->Render();
//	m_sphere2->Render();
//	m_sphere3->Render();
	for (int i = 0; i < spheres; i++)
	{
		m_spheres[i]->Render();
	}
	//m_planeBase->RenderPlane();
	m_planeLeft->RenderPlane();
	m_planeRight->RenderPlane();
//	m_planeTop->RenderPlane();
	m_topTray->RenderPlane();
	m_middleTray->RenderPlane();
	m_bottomTray->RenderPlane();
	m_planeFront->RenderPlane();
	m_planeBack->RenderPlane();
	circle1->renderCircle();
	circle2->renderCircle();
	circle3->renderCircle();
	circle4->renderCircle();
	circle5->renderCircle();
	circle6->renderCircle();
	circle7->renderCircle();
	circle8->renderCircle();
	circle9->renderCircle();
	SwapBuffers(m_hdc);				// Swap Buffers (Double Buffering)
}

