#include "Sphere.h"
#include "Plane.h"
#include <Windows.h>
#include <gl\gl.h>  
#include <gl\GLU.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "TextureLoader.h"
#include <iostream>
using namespace std;

Plane::Plane(float W, float H, Vector3f middle, bool vert, float Y, bool typeIn)
{
	width = W * 0.1f;
	height = H * 0.1f;
	center = Vector3f(middle.GetX() * 0.1f,middle.GetY() * 0.1f, middle.GetZ() * 0.1f);
	vertical = vert * 0.1f;
	yValue = Y * 0.1f;
	type = typeIn;
}
Plane::Plane(void)
{
	width = 0;
	height = 0;
	center = Vector3f(0,0,0);
	vertical = false;
	yValue = 0;
	type = false;
}
void Plane::setArrayPos(int i)
{
	arrayPos = i;
}
int Plane::getArrayPos()
{
	return arrayPos;
}
void Plane::RenderPlane()
{
	float centerZ = center.GetY();
	float centerX = center.GetX();
	if (type == false)
	{
		if (vertical == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glColor3d(1, 0, 1);
			glVertex3d(centerX, yValue - (height / 2), centerZ - (width / 2));
			glVertex3d(centerX, yValue - (height / 2), centerZ + (width / 2));
			glVertex3d(centerX, yValue + (height / 2), centerZ + (width / 2));
			glVertex3d(centerX, yValue + (height / 2), centerZ - (width / 2));
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glColor3d(1, 0, 1);
			glVertex3d(centerX - (width / 2), yValue, centerZ - (height / 2));
			glVertex3d(centerX - (width / 2), yValue, centerZ + (height / 2));
			glVertex3d(centerX + (width / 2), yValue, centerZ + (height / 2));
			glVertex3d(centerX + (width / 2), yValue, centerZ - (height / 2));
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor3d(1, 0, 1);
		glVertex3d(centerX - (width / 2), yValue - (height / 2), centerZ);
		glVertex3d(centerX - (width / 2), yValue + (height / 2), centerZ);
		glVertex3d(centerX + (width / 2), yValue + (height / 2), centerZ);
		glVertex3d(centerX + (width / 2), yValue - (height / 2), centerZ);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void Plane::updateX(float X)
{
	center.Set(center.GetX() + X, center.GetY(), center.GetZ());
}
Vector3f Plane::getMiddle()
{
	return center;
}
float Plane::getY()
{
	return yValue;
}
bool Plane::getVert()
{
	return vertical;
}
bool Plane::getType()
{
	return type;
}
float Plane::getWidth()
{
	return width;
}
float Plane::getHeight()
{
	return height;
}