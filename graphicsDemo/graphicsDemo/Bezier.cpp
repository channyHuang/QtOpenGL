#include "Bezier.h"

#include <iostream>
using namespace std;

BezierClass::BezierClass(QWidget *parent /* = 0 */)
{
	flag = 0;
}

BezierClass::~BezierClass()
{}

void BezierClass::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1, 1, 1, 0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void BezierClass::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Points prep = bezierPoints[0];

	switch (flag) {
	case 0:
		glColor3f(1.0, 0.0, 0.0);
		for (int i = 0; i < 4; i++) {
			drawPoint(bezierPoints[i]);
		}
		glColor3f(0.0, 1.0, 0.0);
		for (int i = 0; i < 3; i++) {
			drawLine(bezierPoints[i], bezierPoints[i + 1]);
		}
		for (double t = 0.0; t <= 1.0; t += 0.1) {
			Points p = CmpBezier(bezierPoints[0], bezierPoints[1], bezierPoints[2], bezierPoints[3], t);
			drawLine(prep, p);
			prep = p;
		}
		break;
	default: 
		for (int i = 0; i < flag; i++) {
			drawPoint(bezierPoints[i]);
		}
		break;
	}
}

void BezierClass::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void BezierClass::drawPoint(Points pt)
{
	/*
	glBegin(GL_POINTS);
	glVertex2f(pt.x, pt.y);
	glEnd();
	*/
	glPushMatrix();
	glTranslatef(pt.x, pt.y, 0.0);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, 0.01, 20, 20);
	glPopMatrix();
}

void BezierClass::drawLine(Points p1, Points p2)
{
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

Points BezierClass::CmpBezier(Points pa, Points pb, Points pc, Points pd, double t)
{
	Points p;
	double a1, a2, a3, a4;
	a1 = pow(1 - t, 3);
	a2 = pow(1 - t, 2) * 3 * t;
	a3 = 3 * t*t*(1 - t);
	a4 = t*t*t;
	p.x = a1*pa.x + a2*pb.x + a3*pc.x + a4*pd.x;
	p.y = a1*pa.y + a2*pb.y + a3*pc.y + a4*pd.y;
	return p;
}