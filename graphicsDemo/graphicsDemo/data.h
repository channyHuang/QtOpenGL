#ifndef DATA_HPP
#define DATA_HPP

#include "windows.h"
#include "gl/GL.h"
#include <gl/GLU.h>
#include <gl/glut.h>

//PhoneModel
extern GLfloat lightPosition[4];
extern GLfloat lightShiness[1];
extern GLfloat lightAmbient[4];
extern GLfloat lightDiffuse[4];
extern GLfloat lightSpecular[4];
extern GLfloat lightEmission[4];

//Bezier
struct Points
{
	float x, y;
};
extern Points bezierPoints[4];
extern Points bspinePoints[4];

#endif