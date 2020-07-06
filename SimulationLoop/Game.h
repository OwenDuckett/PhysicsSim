#pragma once
#include "Plane.h"
#include <Windows.h>
#include "Sphere.h"
#include "Circle.h"
#include "ContactManifold.h"
class Game
{
public:
	Game(HDC hdc);
	~Game(void);

	void Update();
	void UpdateTray(int key);
	void UpdateCamera(char key);
	void UpdateTime(char key);
	void AddSphere();
	void Reset();
	void ChangeAbsolutes(char key);

private:
	void SimulationLoop();
	void CalculateObjectPhysics();
	void DynamicCollisionDetection();
	void DynamicCollisionResponse();
	void UpdateObjectPhysics();	
	void Render();

private:
	HDC   m_hdc;
	float m_dt;
	float m_dtScale;
	int	  m_fps;
	float m_previousTime;
	Sphere *m_delete;
	Sphere *m_bowl;
	Sphere *m_sphere1;
	Sphere *m_sphere2;
	Sphere *m_sphere3;
	Sphere *m_spheres[100];
	//Plane *m_planeBase;
	Plane *m_planeLeft;
	Plane *m_planeRight;
	//Plane *m_planeTop;
	Plane *m_topTray;
	Plane *m_middleTray;
	Plane *m_bottomTray;
	Plane *m_planeFront;
	Plane *m_planeBack;
	Circle *circle1;
	Circle *circle2;
	Circle *circle3;
	Circle *circle4;
	Circle *circle5;
	Circle *circle6;
	Circle *circle7;
	Circle *circle8;
	Circle *circle9;
	bool m_moveTop;
	bool m_moveBottom;
	bool m_resetTop;
	bool m_resetBottom;

	ContactManifold *m_manifold;
	LARGE_INTEGER start, end, frequency;
};

