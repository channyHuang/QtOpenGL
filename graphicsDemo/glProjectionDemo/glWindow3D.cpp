#include "glWindow3D.h"

#include "data.h"

glWindow3D::glWindow3D(QWidget *parent) : QGLWidget(parent)
{

}

glWindow3D::~glWindow3D()
{}

void glWindow3D::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	initLights();
}

void glWindow3D::resizeGL(int w, int h)
{
	if (h == 0) h = 1;

	GLfloat nrange = 10.0f;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		gluPerspective(45.0, (GLdouble)h / (GLdouble)w, 0.1, 10.0);
	}
	else {
		gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 10.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void glWindow3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	if (projtype) {
		glFrustum(left, right, bottom, top, nearnum, farnum);
//	}
//	else {
//		glOrtho(left, right, bottom, top, nearnum, farnum);
//	}

	gluLookAt(1, 3, 10, 0, 0, 0, 0, 1, 0);

	drawGrid(10, 1);
	drawSpheres();
	update();
}

void glWindow3D::initLights()
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

void glWindow3D::drawGrid(float size, float step)
{
	// disable lighting
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glColor3f(0.3f, 0.3f, 0.3f);
	for (float i = step; i <= size; i += step)
	{
		glVertex3f(-size, 0, i);   // lines parallel to X-axis
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);   // lines parallel to X-axis
		glVertex3f(size, 0, -i);

		glVertex3f(i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(-i, 0, size);
	}

	// x-axis
	glColor3f(0.5f, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);

	// z-axis
	glColor3f(0, 0, 0.5f);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);

	glEnd();

	// enable lighting back
	glEnable(GL_LIGHTING);
}

void glWindow3D::drawAxis(float size)
{
	glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
	glDisable(GL_LIGHTING);

	// draw axis
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
	glLineWidth(1);

	// draw arrows(actually big square dots)
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, size);
	glEnd();
	glPointSize(1);

	// restore default settings
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
}

void glWindow3D::drawSpheres()
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
