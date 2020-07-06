#include "Sphere.h"
#include <Windows.h>
#include <gl\gl.h>  
#include <gl\GLU.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "TextureLoader.h"
#include <iostream>
#include <string>
#include "Plane.h"
//#include "Circle.h"
using namespace std;

int Sphere::countID = 0;
float COE = 0.6f;
float FC = 0.99f;
int collisions = 0;
bool trayMoving;
bool trayForward;
Sphere::Sphere(void) : m_mass(0.02f), m_radius(0.05f)
{
	m_wireframe = false;
	m_objectID = countID;
	++countID;
	m_texture = TextureLoader::LoadBMP("checker.bmp");
	m_applyFriction = false;
	m_velocityChange = Vector3f(0, 0, 0);
	m_currentRVel = Vector3f(0, 0, 0);
	m_frictionMX = false;
	m_frictionX = false;
}

Sphere::~Sphere(void)
{
	m_velocityChange = Vector3f(0, 0, 0);
	m_currentRVel = Vector3f(0, 0, 0);
	m_frictionMX = false;
	m_frictionX = false;
}


Sphere::Sphere(float mass, float radius)
{
	m_wireframe = false;
	m_mass = mass;
	m_radius = radius;
	m_objectID = countID;
	++countID;
	m_texture = TextureLoader::LoadBMP("checker.bmp");
	m_applyFriction = false;
}
void Sphere::ChangeFC(float f)
{
	FC = FC + f;
	if (FC < 0.0f)
	{
		FC = 0.0f;
	}
	cout << "\nFC is: " << FC;
}
void Sphere::swapTrayValue(bool tf,bool tv)
{
	trayForward = tf;

	trayMoving = tv;
	
}
void Sphere::ChangeCOE(float f)
{
	COE = COE + f;
	if (COE < 0.1f)
	{
		COE = 0.1f;
	}
	if (COE > 1.0f)
	{
		COE = 1.0f;
	}
	cout << "\nCOE is: " << COE;
}

void Sphere::SetPos(float x, float y, float z)
{
	m_pos.Set(x, y, z);
}

void Sphere::SetNewPos(Vector3f pos)
{
	m_newPos = pos;
}

void Sphere::SetVel(float x, float y, float z)
{
	m_velocity.Set(x, y, z);
}

void Sphere::SetNewVel(Vector3f vel)
{
	m_newVelocity = vel;

}

void Sphere::SetMass(float mass)
{
	m_mass = mass;
}

void Sphere::CalculatePhysics(float dt)
{
	// Calcuate total force for this sphere, e.g. F = F1+F2+F3+...
	//Vector3f force(0.0f, -9.81f * m_mass, 0.0f);
	Vector3f force(0.0f, -9.81f * m_mass, 0.0f);

	//float MaxFriction = m_mass * FC;
	//if(fabs(force.GetX > MaxFriction || fabs(force.GetY > MaxFriction)))
	/*if (m_applyFriction == true)
	{
		m_applyFriction = false;
		collisions++;
		OutputDebugString("\nhere");
	//	OutputDebugString(to_string(collisions));
		force = force * FC;

	}*/



	// Calculate acceleration
	Vector3f accel = force / m_mass;

	Vector3f k1, k2, k3, k4;
	// Integrate accel to get the new velocity (using Euler)
//	m_newVelocity = m_velocity + (accel * dt);

	k1 = m_velocity;
	k2 = m_velocity + (accel * (0.5f * dt));
	k3 = m_velocity + (accel * (0.5f * dt));
	k4 = m_velocity + (accel * dt);

	m_newVelocity = (k1 + (2 * k2) + (2 * k3) + k4) / 6.0f;
	// Integrate old velocity to get the new position (using Euler)
	//m_newPos = m_pos + (m_velocity * dt);

	m_newPos = m_pos + ((m_velocity + m_newVelocity) * 0.5f) * dt;

	if (m_applyFriction == true)
	{
		m_newVelocity = Vector3f(m_newVelocity.GetX() * FC, m_newVelocity.GetY(), m_newVelocity.GetZ()*FC);
		if (m_frictionX == true)
		{
			m_newVelocity = Vector3f(m_newVelocity.GetX() + 0.01f, m_newVelocity.GetY() + 0.1f, m_newVelocity.GetZ());
			Update();
		}
		if (m_frictionMX == true)
		{
			m_newVelocity = Vector3f(m_newVelocity.GetX() + 0.02f, m_newVelocity.GetY(), m_newVelocity.GetZ());
			Update();
		}
		m_frictionMX = false;
		m_frictionX = false;
	//	m_newVelocity = Vector3f(m_newVelocity.GetX(), m_newVelocity.GetY(), m_newVelocity.GetZ());
	}
	// ****************************************************************
	// ******** This implementation is very basic and does not ********
	// ******** accurately model collisions with a plane       ********
	// ****************************************************************
	// ******** Replace with better collision detection code   (done)********
	// ****************************************************************

	/*if(m_newPos.GetY() < -20.0f+m_radius)
	{

		plane.normalise();
		m_newPos.Set(m_newPos.GetX(), -20.0f + m_radius);


		m_newVelocity.Set(m_newVelocity.GetX(), 0.0f);

	}*/
	/*if (abs(m_newVelocity.GetY())< 0.035f && m_velocity.GetY() < 0.35f)
	{
				m_newVelocity.Set(m_newVelocity.GetX(), 0, m_newVelocity.GetZ());
				m_wireframe = true;
	}
	else
	{
		m_wireframe = false;
	}
	*/
}
void Sphere::setVelocityChange(Vector3f velC)
{
	m_velocityChange = velC;
}
void Sphere::setCurrentRVel(Vector3f cRVel)
{
	m_currentRVel = cRVel;
}
Vector3f Sphere::getCurrentRVel()
{
	return m_currentRVel;
}
Vector3f Sphere::getVelocityChange()
{
	return m_velocityChange;
}
void Sphere::checkActive()
{
	m_wireframe = false;
	float floatOfGod = 0.05f;
/*	float test = m_velocity.GetY() - m_newVelocity.GetY();
	if (abs(test) < 0.001f)
	{
		m_newVelocity = Vector3f(m_newVelocity.GetX(), 0.0f, m_newVelocity.GetZ());
		//	m_newVelocity = Vector3f(0.0f, 0.0f, 0.0f);
		Update();
		m_wireframe = true;
	}*/
		
	/*if (abs(m_newVelocity.GetZ()) < floatOfGod)
	{
		m_newVelocity = Vector3f(m_newVelocity.GetX(), m_newVelocity.GetY(), 0.0f);
		Update();
	}*/
	//if (abs(m_newVelocity.GetY()) < floatOfGod)
	//{
	//	m_newVelocity = Vector3f(m_newVelocity.GetX(), 0.0f, m_newVelocity.GetZ());
//		Update();
//	}
	/*if (abs(m_newVelocity.GetX()) < floatOfGod)
	{
		m_newVelocity = Vector3f(0.0f, m_newVelocity.GetY(), m_newVelocity.GetZ());
		Update();
	}*/
	//if (abs(m_newVelocity.GetZ()) < floatOfGod)
	//{
	if (abs(m_newVelocity.GetZ()) < floatOfGod)
	{
		if (abs(m_newVelocity.GetX()) < floatOfGod)
		{
			if (abs(m_newVelocity.GetY()) < floatOfGod)
			{
				//	m_newVelocity = Vector3f(m_newVelocity.GetX(), 0.0f, m_newVelocity.GetZ());
				m_newVelocity = Vector3f(0.0f, 0.0f, 0.0f);
				//Update();
				m_wireframe = true;
			}
		}
	}
	//}
	else
	{
		m_wireframe = false;
	}
}

float Sphere::GetDotProduct(Vector3f x, Vector3f y)
{
	float dot = 0.0f;
	float dot1X = x.GetX();
	float dot2X = y.GetX();
	float dot1Y = x.GetY();
	float dot2Y = y.GetY();
	float dot1Z = x.GetZ();
	float dot2Z = y.GetZ();
	dot = ((dot1X * dot2X) + (dot1Y * dot2Y) + (dot1Z * dot2Z));
	return dot;
}

/*
void Sphere::CollisionWithTray(Plane planes[], Circle circles[], float dt)
{
	for (int count = 2; count < 5; count++)
	{
		Plane testObj = planes[count];

		Vector3f normal(0.0f, 1.0f, 0.0f);
		Vector3f lowerNormal(0.0f, -1.0f, 0.0f);
		Vector3f testLowerXNormal(1.0f, 0.0f, 0.0f);
		Vector3f testZNormal(0.0f, 0.0f, 1.0f);

		Vector3f Yplane(0.0f, -15.0f, 0.0f);
		Vector3f middle = testObj.getMiddle();
		Vector3f z = Vector3f(0, 0, 0);
		float Y = testObj.getY();
		float X = middle.GetX();
		float Z = middle.GetY();
		float height = testObj.getHeight();
		float width = testObj.getWidth();

		Vector3f upperZPlane(0.0f, 0.0f, Z + width / 2 - m_radius);
		Vector3f lowerZPlane(0.0f, 0.0f, Z - width / 2 - m_radius);
		Vector3f lowerXPlane(X - width / 2 - m_radius, 0.0f, 0.0f);
		Vector3f upperXPlane(X + width / 2 - m_radius, 0.0f, 0.0f);

		float newY = m_newPos.GetY();

		Yplane = Vector3f(0, Y, 0);
		normal = Vector3f(0.0f, 1.0f, 0);
		lowerNormal = Vector3f(0.0f, -1.0f, 0);


		Vector3f Ytest = m_newPos - Yplane;

		Vector3f lowerZTest = m_newPos - lowerZPlane;
		Vector3f upperZTest = m_newPos - upperZPlane;
		Vector3f lowerXTest = m_newPos - lowerXPlane;
		Vector3f upperXtest = m_newPos - upperXPlane;

		float testDotZupper = GetDotProduct(upperZTest, testZNormal);
		float testDotZlower = GetDotProduct(lowerZTest, testZNormal);
		float testDotXUpper = GetDotProduct(upperXtest, testLowerXNormal);
		float testDotXLower = GetDotProduct(lowerXTest, testLowerXNormal);
		float testYDot = GetDotProduct(Ytest, normal);

		if (testDotXUpper <= m_radius)
		{
			if (testDotXLower >= m_radius)
			{
				if (testDotZupper <= m_radius)
				{
					if (testDotZlower >= m_radius)
					{
						if (testYDot <= m_radius)
						{
							if (newY > Y - m_radius)
							{
								bool flag = true;
								if (count == 2)
								{
									for (int i = 0; i < 10; i++)
									{
										Circle testObj = circles[i];
										Vector3f pos = testObj.returnPos();
										float radius = testObj.returnRadius();
										Vector2f pos1 = Vector2f(this->GetNewPos().GetX(), this->GetNewPos().GetZ());
										Vector2f pos2 = Vector2f(pos.GetX(), pos.GetZ());
										float dist = pos1.distance(pos2) - (this->GetRadius() + (radius / 3));
										if (dist < 0.0f)
										{
											flag = false;

										}
									}
								}
								if (flag == true)
								{
									float lb = 0;
									float ub = dt;

										for (int i = 0; i < 5000; i++)
										{
											//while(distLoop>0.0f || distLoop<-0.001f)
											//	{
											float test_dt = (ub - lb) / 2;
											Vector3f Ytest = m_newPos - Yplane;
											testYDot = GetDotProduct(Ytest, normal);
											CalculatePhysics(lb + test_dt);
											if (testYDot <= m_radius)
											{
												lb = lb + test_dt;
											}
											else
											{
												ub = lb + test_dt;

											}
										}

									m_newPos = m_pos;
									m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, normal) * normal);
									m_applyFriction = true;
										if (abs(m_newVelocity.GetZ()) < 0.001f)
										{
											if (abs(m_newVelocity.GetX()) < 0.001f)
											{

											}
										}
									checkActive();
									break;
								}
							}
							else
							{
								float testYLowerDot = GetDotProduct(Ytest, lowerNormal);
								if (testYLowerDot <= m_radius)
								{
									if (newY > Y - m_radius)
									{
										cout << "X: " << to_string(m_pos.GetX()) << "Y: " << to_string(m_pos.GetY());
										m_newPos = m_pos;
										m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, lowerNormal) * lowerNormal);
										m_applyFriction = true;
										checkActive();
										break;
									}
								}
							}
						}
					}
				}

			}
		}
	}
	for (int count = 5; count < 7; count++)
	{
		Plane testObj = planes[count];
		Vector3f normal(1.0f, 0.0f, 0.0f);
		Vector3f testYNormal(0.0f, 1.0f, 0.0f);
		Vector3f testZNormal(0.0f, 0.0f, 1.0f);
		Vector3f middle = testObj.getMiddle();
		float X = middle.GetX();
		float Z = middle.GetY();
		float Y = testObj.getY();
		Vector3f z = Vector3f(0, 0, 0);
		Vector3f XPlane = Vector3f(X, 0.0f, 0.0f);
		float height = testObj.getHeight();
		float width = testObj.getWidth();

		Vector3f upperZPlane(0.0f, 0.0f, Z + width / 2 - m_radius);
		Vector3f lowerZPlane(0.0f, 0.0f, Z - width / 2 - m_radius);
		Vector3f lowerYPlane(0.0f, Y - height / 2 - m_radius, 0.0f);
		Vector3f upperYPlane(0.0f, Y + height / 2 - m_radius, 0.0f);

		Vector3f lowerZTest = m_newPos - lowerZPlane;
		Vector3f upperZTest = m_newPos - upperZPlane;
		Vector3f lowerYTest = m_newPos - lowerYPlane;
		Vector3f upperYtest = m_newPos - upperYPlane;

		Vector3f Xtest = m_newPos - XPlane;

		float testDotYUpper = GetDotProduct(upperYtest, testYNormal);
		float testDotYLower = GetDotProduct(lowerYTest, testYNormal);
		float testDotZupper = GetDotProduct(upperZTest, testZNormal);
		float testDotZlower = GetDotProduct(lowerZTest, testZNormal);

		float testXDot = GetDotProduct(Xtest, normal);

		if (testDotYUpper <= m_radius)
		{
			if (testDotYLower >= m_radius)
			{
				if (testDotZupper <= m_radius)
				{
					if (testDotZlower >= m_radius)
					{
						if (testXDot <= m_radius)
						{
							float newX = m_newPos.GetX();
							if (newX > X - m_radius)
							{
								m_newPos = m_pos;
								m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, normal) * normal);
								m_applyFriction = true;
								break;
							}
								else
								{
									float testYLowerDot = GetDotProduct(Xtest, normal);
									if (testYLowerDot <= m_radius)
									{
										if (newX > X - m_radius)
										{
											cout << "X: " << to_string(m_pos.GetX()) << "Y: " << to_string(m_pos.GetY());
											m_newPos = m_pos;
											m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, normal) * normal);
											m_applyFriction = true;
											break;
										}
									}
								}
						}
					}
				}
			}
		}

	}

	for (int count = 7; count < 9; count++)
	{
		Plane testObj = planes[count];
		Vector3f normal(0.0f, 0.0f, 1.0f);
		Vector3f testYNormal(0.0f, 1.0f, 0.0f);
		Vector3f testXNormal(1.0f, 0.0f, 0.0f);
		Vector3f middle = testObj.getMiddle();
		float X = middle.GetX();
		float Z = middle.GetY();
		float Y = testObj.getY();
		Vector3f ZPlane = Vector3f(0.0f, 0.0f, Z);
		float height = testObj.getHeight();
		float width = testObj.getWidth();

		Vector3f lowerXPlane(X - width / 2 - m_radius, 0.0f, 0.0f);
		Vector3f upperXPlane(X + width / 2 - m_radius, 0.0f, 0.0f);
		Vector3f lowerYPlane(0.0f, Y - height / 2 - m_radius, 0.0f);
		Vector3f upperYPlane(0.0f, Y + height / 2 - m_radius, 0.0f);

		Vector3f lowerYTest = m_newPos - lowerYPlane;
		Vector3f upperYtest = m_newPos - upperYPlane;
		float testDotYUpper = GetDotProduct(upperYtest, testYNormal);
		float testDotYLower = GetDotProduct(lowerYTest, testYNormal);

		Vector3f lowerXTest = m_newPos - lowerXPlane;
		Vector3f upperXtest = m_newPos - upperXPlane;
		float testDotXUpper = GetDotProduct(upperXtest, testXNormal);
		float testDotXLower = GetDotProduct(lowerXTest, testXNormal);

		Vector3f Ztest = m_newPos - ZPlane;
		float testZDot = GetDotProduct(Ztest, normal);
		if (testDotXUpper <= m_radius)
		{
			if (testDotXLower >= m_radius)
			{
				if (testDotYUpper <= m_radius)
				{
					if (testDotYLower >= m_radius)
					{
						if (testZDot <= m_radius)
						{
							float newZ = m_newPos.GetZ();
							if (newZ > Z - m_radius)
							{
								m_newPos = m_pos;
								m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, normal) * normal);
								m_applyFriction = true;
								break;
							}
								else
								{
									float testZLowerDot = GetDotProduct(Ztest, normal);
									if (testZLowerDot <= m_radius)
									{
										if (newZ > Z - m_radius)
										{
											cout << "X: " << to_string(m_pos.GetX()) << "Y: " << to_string(m_pos.GetY());
											m_newPos = m_pos;
											m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, normal) * normal);
											m_applyFriction = true;
											break;
										}
									}
								}
						}
					}
				}
			}
		}
	}
}*/
float Sphere::square(float f)
{
	return f * f;
}
void Sphere::CollisionWithPlane(Plane planes[], Circle circles[], ContactManifold *contactManifold, float dt)
{
	int precision = 2;
	for (int count = 2; count < 5; count++)
	{
		Plane testObj = planes[count];
		Vector3f middle = testObj.getMiddle();
		float bcX = middle.GetX() - (testObj.getWidth() / 2);
		float bcY = testObj.getY();
		float bcZ = middle.GetY() - (testObj.getWidth() / 2);
		float tcX = middle.GetX() + (testObj.getWidth() / 2);
		float tcY = testObj.getY();
		float tcZ = middle.GetY() + (testObj.getWidth() / 2);

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}
		bool flag = true;
		if (count == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				Circle testObj = circles[i];
				Vector3f pos = testObj.returnPos();
				float radius = testObj.returnRadius();
				Vector2f pos1 = Vector2f(this->GetNewPos().GetX(), this->GetNewPos().GetZ());
				Vector2f pos2 = Vector2f(pos.GetX(), pos.GetZ());
				float dist = pos1.distance(pos2) - (this->GetRadius() + (radius / 3));
				if (dist < 0.0f)
				{
					flag = false;

				}
			}
		}
		if (flag == true)
		{
			if (dist_squared > 0)
			{
				float lb = 0;
				float ub = dt;
				if (count != 3)
				{
					m_applyFriction = true;
					if (count == 4 && trayMoving == true)
					{
						if (trayForward == true)
						{
							m_frictionX = true;
						}
						else
						{
							m_frictionMX = true;
						}
					}
				}
				else
				{
					m_applyFriction = false;
				}
				for (int i = 0; i < precision; i++)
				{

					float test_dt = (ub - lb) / 2;
					CalculatePhysics(lb + test_dt);
					if (dist_squared < 0)
					{
						lb = lb + test_dt;
					}
					else
					{
						ub = lb + test_dt;
					}

				}
				ManifoldPoint mp;
				mp.contactID1 = this;
				mp.contactID3 = &testObj;
				mp.collisionType = 'p';
				mp.contactNormal = Vector3f(0, 1.0f, 0);
				contactManifold->Add(mp);
			}
		}
	}
	for (int count = 5; count < 7; count++)
	{
		Plane testObj = planes[count];
		Vector3f middle = testObj.getMiddle();
		float bcX = middle.GetX();
		float bcY = testObj.getY() - (testObj.getHeight() / 2);
		float bcZ = middle.GetY() - (testObj.getWidth() / 2);
		float tcX = middle.GetX();
		float tcY = testObj.getY() + (testObj.getHeight() / 2);
		float tcZ = middle.GetY() + (testObj.getWidth() / 2);

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}

		if (dist_squared > 0)
		{
			float lb = 0;
			float ub = dt;

			for (int i = 0; i < precision; i++)
			{

				float test_dt = (ub - lb) / 2;
				CalculatePhysics(lb + test_dt);
				if (dist_squared < 0)
				{
					lb = lb + test_dt;
				}
				else
				{
					ub = lb + test_dt;
				}

			}
			ManifoldPoint mp;
			mp.contactID1 = this;
			mp.contactID3 = &testObj;
			mp.collisionType = 'p';
			mp.contactNormal = Vector3f(1.0f, 0.0f, 0.0f);
			contactManifold->Add(mp);
			m_applyFriction = false;
		}
	}

	for (int count = 7; count < 9; count++)
	{
		Plane testObj = planes[count];
		Vector3f middle = testObj.getMiddle();
		float bcX = middle.GetX() - (testObj.getWidth() / 2);
		float bcY = testObj.getY() - (testObj.getHeight() / 2);
		float bcZ = middle.GetY();
		float tcX = middle.GetX() + (testObj.getWidth() / 2);
		float tcY = testObj.getY() + (testObj.getHeight() / 2);
		float tcZ = middle.GetY();

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}

		if (dist_squared > 0)
		{
			float lb = 0;
			float ub = dt;

			for (int i = 0; i < precision; i++)
			{

				float test_dt = (ub - lb) / 2;
				CalculatePhysics(lb + test_dt);
				if (dist_squared < 0)
				{
					lb = lb + test_dt;
				}
				else
				{
					ub = lb + test_dt;
				}

			}
			ManifoldPoint mp;
			mp.contactID1 = this;
			mp.contactID3 = &testObj;
			mp.collisionType = 'p';
			mp.contactNormal = Vector3f(0.0f, 0.0f, 1.0f);
			contactManifold->Add(mp);
			m_applyFriction = false;
		}
	}
}

void Sphere::CollisionWithSphere(Sphere* sphere2, ContactManifold *contactManifold, float dt)
{
	float lb = 0;
	float ub = dt;
	Vector3f pos1 = this->GetNewPos();
	Vector3f pos2 = sphere2->GetNewPos();
	float dist = pos1.distance(pos2) - (this->GetRadius() + sphere2->GetRadius());
	if (dist < 0.0f)
	{
		float distLoop = dist;
		for (int i = 0; i < 200; i++)
		{
			//while(distLoop>0.0f || distLoop<-0.001f)
		//	{
			float test_dt = (ub - lb) / 2;
			CalculatePhysics(lb + test_dt);
			Vector3f pos1 = this->GetNewPos();
			Vector3f pos2 = sphere2->GetNewPos();
			float distLoop = pos1.distance(pos2) - (this->GetRadius() + sphere2->GetRadius());
			if (distLoop < 0.0f)
			{
				ub = lb + test_dt;
			}
			else
			{
				lb = lb + test_dt;
			}
		}

		ManifoldPoint mp;
		mp.contactID1 = this;
		mp.contactID2 = sphere2;
		mp.contactNormal = (pos2 - pos1).normalise();
		mp.collisionType = 's';
		contactManifold->Add(mp);
		m_applyFriction = false;
	}

}
bool Sphere::CollisionTestWithPlane(Plane* plane, Circle circles[], float dt)
{
	if (plane->getArrayPos() <= 2 || plane->getArrayPos() < 5)
	{
		Plane* testObj = plane;
		Vector3f middle = testObj->getMiddle();
		float bcX = middle.GetX() - (testObj->getWidth() / 2);
		float bcY = testObj->getY();
		float bcZ = middle.GetY() - (testObj->getWidth() / 2);
		float tcX = middle.GetX() + (testObj->getWidth() / 2);
		float tcY = testObj->getY();
		float tcZ = middle.GetY() + (testObj->getWidth() / 2);

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}

		if (dist_squared > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (plane->getArrayPos() <= 5 || plane->getArrayPos() < 7)
	{
		Plane* testObj = plane;
		Vector3f middle = testObj->getMiddle();
		float bcX = middle.GetX();
		float bcY = testObj->getY() - (testObj->getHeight() / 2);
		float bcZ = middle.GetY() - (testObj->getWidth() / 2);
		float tcX = middle.GetX();
		float tcY = testObj->getY() + (testObj->getHeight() / 2);
		float tcZ = middle.GetY() + (testObj->getWidth() / 2);

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}

		if (dist_squared > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (plane->getArrayPos() <= 7 || plane->getArrayPos() < 9)
	{
		Plane* testObj = plane;
		Vector3f middle = testObj->getMiddle();
		float bcX = middle.GetX() - (testObj->getWidth() / 2);
		float bcY = testObj->getY() - (testObj->getHeight() / 2);
		float bcZ = middle.GetY();
		float tcX = middle.GetX() + (testObj->getWidth() / 2);
		float tcY = testObj->getY() + (testObj->getHeight() / 2);
		float tcZ = middle.GetY();

		Vector3f bottomCorner = Vector3f(bcX, bcY, bcZ);
		Vector3f topCorner = Vector3f(tcX, tcY, tcZ);
		Vector3f S = this->GetNewPos();
		float r = this->GetRadius();
		float dist_squared = r * r;


		if (S.GetX() < bottomCorner.GetX())
		{
			dist_squared -= square(S.GetX() - bottomCorner.GetX());
		}
		else if (S.GetX() > topCorner.GetX())
		{
			dist_squared -= square(S.GetX() - topCorner.GetX());
		}
		if (S.GetY() < bottomCorner.GetY())
		{
			dist_squared -= square(S.GetY() - bottomCorner.GetY());
		}
		else if (S.GetY() > topCorner.GetY())
		{
			dist_squared -= square(S.GetY() - topCorner.GetY());
		}

		if (S.GetZ() < bottomCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - bottomCorner.GetZ());
		}
		else if (S.GetZ() > topCorner.GetZ())
		{
			dist_squared -= square(S.GetZ() - topCorner.GetZ());
		}

		if (dist_squared > 0)
		{
			return true;
			
		}
		else
		{
			return false;
		}
	}
}
bool Sphere::CollisionTestWithSphere(Sphere* sphere2, float dt)
{
	float lb = 0;
	float ub = dt;
	Vector3f pos1 = this->GetNewPos();
	Vector3f pos2 = sphere2->GetNewPos();
	float dist = pos1.distance(pos2) - (this->GetRadius() + sphere2->GetRadius());
	if (dist < 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool Sphere::CollisionTestWithBowl(Sphere* bowl, float dt)
{
	float lb = 0;
	float ub = dt;
	Vector3f pos1 = this->GetNewPos();
	Vector3f pos2 = bowl->GetPos();
	float dist = pos1.distance(pos2) - (this->GetRadius() + bowl->GetRadius());
	if (dist > 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Sphere::CollisionWithBowl(Sphere* bowl, ContactManifold *contactManifold, float dt)
{
	float lb = 0;
	float ub = dt;
	Vector3f pos1 = this->GetNewPos();
	Vector3f pos2 = bowl->GetPos();
	float dist = pos1.distance(pos2) - (this->GetRadius() + bowl->GetRadius());
	if (dist > 0.0f)
	{
		float distLoop = dist;
		for (int i = 0; i < 3; i++)
		{
			float test_dt = (ub - lb) / 2;
			CalculatePhysics(lb + test_dt);
			Vector3f pos1 = this->GetNewPos();
			Vector3f pos2 = bowl->GetPos();
			distLoop = pos1.distance(pos2) - (this->GetRadius() + bowl->GetRadius());
			if (distLoop > 0.0f)
			{
				ub = lb + test_dt;
			}
			else
			{
				lb = lb + test_dt;
			}
		}
		ManifoldPoint mp;
		mp.contactID1 = this;
		mp.contactID2 = bowl;
		mp.collisionType = 'b';
		mp.contactNormal = (pos2 - pos1).normalise();
		contactManifold->Add(mp);
		m_applyFriction = true;

	}

}
void Sphere::ResetPos()
{
	m_newPos = m_pos;
}

void Sphere::Update()
{
	m_velocity = m_newVelocity;
	m_pos = m_newPos;
}

/*void Sphere::CollisionResponseWithTray()
{

}*/
void Sphere::CollisionResponseWithBowl(ManifoldPoint &point)
{
	/*Vector3f colNormal = point.contactNormal;
	Vector3f Rv2 = point.contactID2->GetVel();
	Rv2 = Rv2.mult(-1);
	point.contactID2->ResetPos();
	point.contactID2->SetNewVel(Rv2);*/
	// ****************************************************************
	// ******** This implementation is very basic and does not ********
	// ******** accurately model responses between Spheres     ********
	// ****************************************************************
	// ******** Replace with better response code for Spheres (done) ********
	// ****************************************************************

	Vector3f colNormal = point.contactNormal;

	Vector3f Vl1 = ((point.contactID1->GetMass() - (COE * point.contactID2->GetMass())) *
		((point.contactID1->GetVel().dot(colNormal)) * colNormal) +
		(point.contactID2->GetMass() + (COE * point.contactID2->GetMass())) *
		((point.contactID2->GetVel().dot(colNormal)) * colNormal))
		/ (point.contactID1->GetMass() + point.contactID2->GetMass());


	Vector3f Rv1 = point.contactID1->GetVel() - (point.contactID1->GetVel().dot(colNormal) * colNormal) + Vl1;

	point.contactID1->ResetPos();
	//point.contactID1->SetNewVel(-1.0f*colNormal*colNormal.dot(point.contactID1->GetVel()));
	point.contactID1->SetNewVel(Rv1);

	//checkActive();
	//point.contactID2->SetNewVel(-1.0f*colNormal*colNormal.dot(point.contactID2->GetVel()));
}
/*void Sphere::SetCheatVelocity(Vector3f vel)
{
	this->cheatVelocity = vel;
}*/
void Sphere::CollisionResponseWithSphere(ManifoldPoint &point, float dt, Circle circles[])
{
	// ****************************************************************
	// ******** This implementation is very basic and does not ********
	// ******** accurately model responses between Spheres     ********
	// ****************************************************************
	// ******** Replace with better response code for Spheres (done) ********
	// ****************************************************************
	Vector3f colNormal = point.contactNormal;
	if (point.collisionType == 's')
	{
		Vector3f colNormal = point.contactNormal;
		Vector3f Vl1 = ((point.contactID1->GetMass() - (COE * point.contactID2->GetMass())) *
			((point.contactID1->GetVel().dot(colNormal)) * colNormal) +
			(point.contactID2->GetMass() + (COE * point.contactID2->GetMass())) *
			((point.contactID2->GetVel().dot(colNormal)) * colNormal))
			/ (point.contactID1->GetMass() + point.contactID2->GetMass());
		
		Vector3f Vl2 = ((point.contactID1->GetMass() + (COE * point.contactID1->GetMass())) *
			((point.contactID1->GetVel().dot(colNormal)) * colNormal) +
			(point.contactID2->GetMass() - (COE * point.contactID1->GetMass())) *
			((point.contactID2->GetVel().dot(colNormal)) * colNormal)) /
			(point.contactID1->GetMass() + point.contactID2->GetMass());
		Vector3f Rv1 = point.contactID1->GetVel() - (point.contactID1->GetVel().dot(colNormal) * colNormal) + Vl1;
		Vector3f Rv2 = point.contactID2->GetVel() - (point.contactID2->GetVel().dot(colNormal) * colNormal) + Vl2;
		Vector3f velocityDif = point.contactID1->GetVel().subtract(Rv1);
		Vector3f angularVelocity = velocityDif.divide(0.02f);
		Vector3f rotation = angularVelocity / dt * FC;
		point.contactID1->setVelocityChange(velocityDif);
		point.contactID1->setCurrentRVel(point.contactID1->getCurrentRVel().add(velocityDif));
		velocityDif = point.contactID2->GetVel().subtract(Rv2);
		point.contactID2->setCurrentRVel(point.contactID2->getCurrentRVel().add(velocityDif));
		angularVelocity = velocityDif.divide(0.02f);
		rotation = angularVelocity / dt * FC;
		point.contactID2->setVelocityChange(velocityDif);
		
		point.contactID1->ResetPos();
		//point.contactID1->SetNewVel(-1.0f*colNormal*colNormal.dot(point.contactID1->GetVel()));
		point.contactID1->SetNewVel(Rv1);
		point.contactID2->ResetPos();
		point.contactID2->SetNewVel(Rv2);
		Vector3f origVel1 = Rv1;
		Vector3f origVel2 = Rv2;
		float scale = 1.2f;
		bool stuck = false;
		
		while (point.contactID1->CollisionTestWithSphere(point.contactID2, dt) == true)
		{
		/*	stuck = true;
			scale = scale + 0.1f;
			point.contactID1->SetNewVel(Vector3f(origVel1.GetX()*scale, origVel1.GetY()*scale, origVel1.GetZ()*scale));
			point.contactID1->Update();
			point.contactID1->CalculatePhysics(dt);*/
		
			stuck = true;
				//		scale = scale + 0.1f;
				Vector3f test = point.contactNormal;
				test.mult(0.01);
				point.contactID1->SetNewVel(origVel2.subtract(test));
				//	point.contactID1->SetNewVel(Vector3f(originVel.GetX()*scale, originVel.GetY()*scale, originVel.GetZ()*scale));
				point.contactID1->Update();
				point.contactID1->CalculatePhysics(dt);
			bool stuck2 = false;
			while (point.contactID2->CollisionTestWithSphere(point.contactID1, dt) == true)
			{

				//scale = scale + 0.1f;


				/*	point.contactID2->SetNewVel(Vector3f(origVel2.GetX()*scale, origVel2.GetY()*scale, origVel2.GetZ()*scale));
				point.contactID2->Update();
				point.contactID2->CalculatePhysics(dt);*/
				stuck2 = true;
				//		scale = scale + 0.1f;
				Vector3f test = point.contactNormal;
				test.mult(0.01);
				point.contactID2->SetNewVel(origVel2.subtract(test));
				//	point.contactID1->SetNewVel(Vector3f(originVel.GetX()*scale, originVel.GetY()*scale, originVel.GetZ()*scale));
				point.contactID2->Update();
				point.contactID2->CalculatePhysics(dt);

				
			}
			if (stuck2 == true)
			{
		//		point.contactID2->SetNewVel(Vector3f(0, 0, 0));
			}

		}
		if (stuck == true)
		{
	//		point.contactID1->SetNewVel(Vector3f(0, 0, 0));
		}
		scale = 1.2f;
		
		
		point.contactID1->SetNewVel(Rv1);
		point.contactID2->SetNewVel(Rv2);
		
		point.contactID1->Update();
		point.contactID2->Update();
		
		point.contactID1->checkActive();
		point.contactID2->checkActive();
	}
	else
	{
		bool stuck = false;
		point.contactID1->ResetPos();
		
		m_newVelocity = m_velocity - (1.0f + COE) * (GetDotProduct(m_newVelocity, colNormal) * colNormal);
		Vector3f velocityDif = point.contactID1->GetVel().subtract(m_newVelocity);
		Vector3f angularVelocity = velocityDif.divide(0.02f);
		Vector3f rotation = angularVelocity / dt * FC;
		point.contactID1->setVelocityChange(velocityDif);
		m_currentRVel = m_currentRVel.add(velocityDif);
		if (point.collisionType == 'p')
		{
			Vector3f originVel = m_newVelocity;
			float scale = 1.2f;
			while (point.contactID1->CollisionTestWithPlane(point.contactID3, circles, dt) == true)
			{
		//		scale = scale + 0.01f;
		//		point.contactID1->SetNewVel(Vector3f(originVel.GetX()*scale, originVel.GetY()*scale, originVel.GetZ()*scale));
		//		point.contactID1->Update();
		//		point.contactID1->CalculatePhysics(dt);
				stuck = true;
				//		scale = scale + 0.1f;
				Vector3f test = point.contactNormal;
				test.mult(0.01);
				point.contactID1->SetNewVel(originVel.add(test));
				//	point.contactID1->SetNewVel(Vector3f(originVel.GetX()*scale, originVel.GetY()*scale, originVel.GetZ()*scale));
				point.contactID1->Update();
				point.contactID1->CalculatePhysics(dt);
			}
			if (stuck == true)
			{
				point.contactID1->SetNewVel(Vector3f(0, 0, 0));
			}
		}
	
		if (point.collisionType == 'b')
		{
			bool stuck = false;
				Vector3f originVel = m_newVelocity;
				float scale = 1.2f;
				while (point.contactID1->CollisionTestWithBowl(point.contactID2, dt) == true)
				{
					stuck = true;
			//		scale = scale + 0.1f;
					Vector3f test = point.contactNormal;
					test.mult(0.01);
					point.contactID1->SetNewVel(originVel.add(test));
				//	point.contactID1->SetNewVel(Vector3f(originVel.GetX()*scale, originVel.GetY()*scale, originVel.GetZ()*scale));
					point.contactID1->Update();
					point.contactID1->CalculatePhysics(dt);
				}
				if (stuck == true)
				{
					point.contactID1->SetNewVel(Vector3f(0, 0, 0));
				}

		}
		if (point.collisionType == 'p')
		{
			if (point.contactID3->getArrayPos() == 4)
			{
				if (trayMoving == true)
				{

				}
				else
				{
				//	point.contactID1->checkActive();
				}
			}
		}
		else
		{
			point.contactID1->checkActive();
		}
	//	point.contactID1->Update();
		
			
	}
	//point.contactID2->SetNewVel(-1.0f*colNormal*colNormal.dot(point.contactID2->GetVel()));

}

float Sphere::GetMass() const
{
	return m_mass;
}

Vector3f Sphere::GetPos() const
{
	return m_pos;
}

Vector3f Sphere::GetNewPos() const
{
	return m_newPos;
}

Vector3f Sphere::GetVel() const
{
	return m_velocity;
}

Vector3f Sphere::GetNewVel() const
{
	return m_newVelocity;
}

float Sphere::GetRadius() const
{
	return m_radius;
}
float test;
float Y = 0;
float X = 0;
float Z = 0;
void Sphere::Render() const
{
//	if (test > 1000)
//	{
//		test = 0;
//	}
	glPushMatrix();
	
	//Y = Y + 0.1f;
	//Z = Z + 0.2f;
	//X = X + 0.2f;
	
//	test = test + 1.0f;
	//glTranslatef(-m_pos.GetX(), -m_pos.GetY(), -m_pos.GetZ());
	X = X + m_velocityChange.GetX();
	Y = X + m_velocityChange.GetY();
	Z = X + m_velocityChange.GetZ();
	X = X + m_newVelocity.GetX();
	Y = X + m_newVelocity.GetY();
	Z = X + m_newVelocity.GetZ();
//	X = m_currentRVel.GetX();
//	Y = m_currentRVel.GetY();
//	Z = m_currentRVel.GetZ();
	
	
	
	glTranslatef(m_pos.GetX(), m_pos.GetY(), m_pos.GetZ());
	glRotatef(X, 1.0f, 0.0f, 0.0f);
	glRotatef(Y, 0.0f, 1.0f, 0.0f);
	glRotatef(Z, 0.0f, 0.0f, 1.0f);
	
	glColor3d(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, m_texture);               // Select Our Texture
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	if (m_wireframe == false)
	{
		gluQuadricTexture(quadric, GL_TRUE);
	}
	else
	{
		gluQuadricTexture(quadric, GL_FALSE);
	}
	
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluSphere(quadric, m_radius, 2000, 20);
	
	gluDeleteQuadric(quadric);
	//gluQuadricDrawStyle(quadric, GLU_FILL);
	glPopMatrix();
}
