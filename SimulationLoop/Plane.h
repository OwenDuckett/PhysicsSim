#pragma once

#include "ContactManifold.h"
#include "Vector2f.h"
#include <Windows.h>
#include <gl\gl.h> 

class Plane
{
public:
	Plane(float W, float H, Vector3f middle, bool vert, float Y, bool typeIn);
	Plane(void);
	//void setPlane(float W, float H, Vector2f middle, bool Vert, float Y);
	void RenderPlane();
	Vector3f getMiddle();
	float getY();
	bool getVert();
	bool getType();
	float getWidth();
	float getHeight();
	void updateX(float);
	int getArrayPos();
	void setArrayPos(int i);

private:
	float yValue;
	float width;
	float height;
	Vector3f center;
	bool vertical;
	int arrayPos;
	bool type;
};



