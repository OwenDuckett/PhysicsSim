#pragma once
#include "Vector2f.h"
#include <Windows.h>
#include <gl\gl.h> 
#include "Circle.h"
#include "Vector3f.h"
#include <math.h>
Circle::Circle(Vector3f pos, float radius)
{
	m_pos = pos;
	m_pos.Set(m_pos.GetX(), -1.25f, m_pos.GetZ());
	m_radius = radius;
}
Circle::Circle()
{

}
Vector3f Circle::returnPos()
{
	return m_pos;
}
float Circle::returnRadius()
{
	return m_radius;
}
void Circle::renderCircle()
{
		float Pi = 3.14159265f;
		int lineAmount = 10000; 

							  //GLfloat radius = 0.8f; //radius
		float twicePi = 2.0f * Pi;
		float x = m_pos.GetX();
		float y = m_pos.GetY();
		float z = m_pos.GetZ();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor3d(1, 0, 1);
		for (int i = 0; i <= lineAmount; i++) {
			glVertex3d(x + (m_radius * cos(i *  twicePi / lineAmount)), y , z + (m_radius * sin(i * twicePi / lineAmount)));
			
		}
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnd();
}