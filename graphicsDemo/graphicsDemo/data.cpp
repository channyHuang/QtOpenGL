#include "data.h"

//PhoneModel
GLfloat lightPosition[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightShiness[1] = { 50 };
GLfloat lightAmbient[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightDiffuse[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightSpecular[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightEmission[4] = { 0.0, 0.0, 0.0, 1.0 };

//Bezier
Points bezierPoints[4] = { { -0.2, 0.2 }, { 0.1, 0.2 }, { 0.2, 0.0 }, { 0.2, -0.2 } };
Points bspinePoints[4] = { { -0.2, 0.2 }, { 0.1, 0.2 }, { 0.2, 0.0 }, { 0.2, -0.2 } };