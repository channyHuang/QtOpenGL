#include "glWindow.h"

#include "data.h"

glWindow::glWindow(QWidget *parent) : QGLWidget(parent)
{

}

glWindow::~glWindow()
{}

void glWindow::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	initLights();
}

void glWindow::resizeGL(int w, int h)
{
	GLfloat nrange = 10.0f;

	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	//int dis = w < h ? w : h;
	//glViewport(0, 0, dis, dis);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(left, right, bottom, top, near, far);
	if (w <= h) {
		//glOrtho(-nrange, nrange, -nrange*h / w, nrange*h / w, -nrange, nrange);
		gluPerspective(45.0, (GLdouble)h / (GLdouble)w, 0.1, 10.0);
	}
	else {
		//glOrtho(-nrange*w/h, nrange*w/h, -nrange, nrange, -nrange, nrange);
		gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 10.0);
	}

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (projtype) {
		glFrustum(left, right, bottom, top, nearnum, farnum);
	}
	else {
		glOrtho(left, right, bottom, top, nearnum, farnum);
	}

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	drawSpheres();
	update();
}

void glWindow::initLights()
{
	// set up light colors (ambient, diffuse, specular)
	GLfloat lightKa[] = { .0f, .0f, .0f, 1.0f };      // ambient light
	GLfloat lightKd[] = { .9f, .9f, .9f, 1.0f };      // diffuse light
	GLfloat lightKs[] = { 1, 1, 1, 1 };               // specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light in eye space
	float lightPos[4] = { 0, 0, 1, 0 };               // directional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);                            // MUST enable each light source after configuration
}


void glWindow::drawSpheres()
{
	//color has no effect
	GLUquadricObj* quadricId = gluNewQuadric();
	gluQuadricDrawStyle(quadricId, GLU_FILL);

	const int SLICES = 36;
	const int STACKS = 24;
	const float RADIUS = 0.5f;

	float color1[3] = { 1, 0, 0 };
	float color2[3] = { 1, 0.5f, 0 };
	float color3[3] = { 1, 1, 0 };
	float color4[3] = { 0, 1, 0 };
	float color5[3] = { 0, 1, 1 };
	float color6[3] = { 0, 0, 1 };
	float color7[3] = { 1, 0, 1 };

	// set default specular and shiniess using glMaterial
	float shininess = 64.0f;
	float specularColor[] = { 1.0, 1.0f, 1.0f, 1.0f };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); // range 0 ~ 128
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);

	glPushMatrix();
	glTranslatef(0, 0, 3);
	glColor3fv(color1);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, 2);
	glColor3fv(color2);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 0, 2);
	glColor3fv(color2);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 2);
	glColor3fv(color2);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1, 2);
	glColor3fv(color2);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 0, 1);
	glColor3fv(color3);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, 0, 1);
	glColor3fv(color3);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 1);
	glColor3fv(color3);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2, 1);
	glColor3fv(color3);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, 0);
	glColor3fv(color4);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glColor3fv(color4);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	glColor3fv(color4);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3, 0);
	glColor3fv(color4);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, -1);
	glColor3fv(color5);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 0, -1);
	glColor3fv(color5);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, -1);
	glColor3fv(color5);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -4, -1);
	glColor3fv(color5);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, -2);
	glColor3fv(color6);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, -2);
	glColor3fv(color6);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, -2);
	glColor3fv(color6);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -5, -2);
	glColor3fv(color6);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, -3);
	glColor3fv(color7);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, 0, -3);
	glColor3fv(color7);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6, -3);
	glColor3fv(color7);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -6, -3);
	glColor3fv(color7);
	gluSphere(quadricId, RADIUS, SLICES, STACKS);
	glPopMatrix();
}
