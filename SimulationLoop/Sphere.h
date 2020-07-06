#pragma once

#include "ContactManifold.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include <Windows.h>
#include <gl\gl.h>  
#include "Plane.h"
#include "Circle.h"
class Sphere
{
public:
	Sphere(void);
	~Sphere(void);
	Sphere(float mass, float radius);
	void CalculatePhysics(float dt);
	void CollisionWithSphere(Sphere* sphere, ContactManifold *contactManifold, float dt);
	bool CollisionTestWithSphere(Sphere* sphere, float dt);
	void CollisionWithPlane(Plane planes[], Circle circles[],ContactManifold *contactManifold, float dt);
	void CollisionWithBowl(Sphere* bowl, ContactManifold *contactManifold, float dt);
	bool CollisionTestWithBowl(Sphere* bowl, float dt);
	bool CollisionTestWithPlane(Plane* plane, Circle circles[], float dt);
	void Update();
	void CollisionResponseWithSphere(ManifoldPoint &point, float dt,Circle circles[]);
	void SetPos(float x, float y, float z);
	void SetVel(float x, float y, float z);
	void setVelocityChange(Vector3f velC);
	void setCurrentRVel(Vector3f cVelR);
	void ChangeFC(float f);
	void ChangeCOE(float f);
	Vector3f getVelocityChange();
	Vector3f getCurrentRVel();
	void swapTrayValue(bool t,bool m);
	void SetNewPos(Vector3f pos);
	void SetNewVel(Vector3f vel);
	void SetMass(float mass);
	float square(float f);
	void checkActive();
	Vector3f GetPos() const;
	Vector3f GetNewPos() const;
	Vector3f GetVel() const;
	Vector3f GetNewVel() const;
	float GetMass() const;
	void ResetPos();
	float GetRadius() const;
	float GetDotProduct(Vector3f x, Vector3f y);
	void Render() const;
	//void CollisionWithTray(Plane planes[], Circle circles[], float dt);
	void CollisionResponseWithBowl(ManifoldPoint &point);
	//void SetCheatVelocity(Vector3f vel);
private:
	//Vector3f cheatVelocity;
	Vector3f m_currentRVel;
	Vector3f m_velocityChange;
	float m_mass;
	float m_radius;
	bool m_frictionX;
	bool m_frictionMX;
	Vector3f m_pos;
	Vector3f m_newPos;
	Vector3f m_velocity;
	Vector3f m_newVelocity;
	int m_objectID;
	GLuint m_texture;
	bool m_applyFriction;
	bool m_wireframe;

	static int countID;
};

