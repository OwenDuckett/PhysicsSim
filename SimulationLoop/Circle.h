#pragma once
#include "Vector2f.h"
#include <Windows.h>
#include <gl\gl.h> 
#include "Vector3f.h"
class Circle
{
public: 
	Circle(Vector3f pos, float radius);
	Circle();
	void renderCircle();
	Vector3f returnPos();
	float returnRadius();
private:
	Vector3f m_pos;
	float m_radius;
};