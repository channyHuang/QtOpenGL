#include "glWindow.h"

#include "data.h"

glWindow::glWindow(QWidget *parent) : QGLWidget(parent)
{

}

glWindow::~glWindow()
{}

void glWindow::initializeGL()
{
	model.load("teapot.obj");

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void glWindow::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	float m[16] = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i * 4 + j] = viewmatrix.get(i, j);
		}
	}

	glPushMatrix();
	glLoadMatrixf(m);
	drawGrid(10, 1);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i * 4 + j] = modelview.get(i, j);
		}
	}
	glLoadMatrixf(m);
	drawAxis(4);
	displaymodel();

	glPopMatrix();
	*/

	glLoadIdentity();
	gluLookAt(0, 0, -1.3, 0, 0, 0, 0, 1, 0);
	displaymodel();

	update();
}

void glWindow::displaymodel()
{
	if (model.tri.size() <= 0) return;
	Triangle *mytri;
	for (int i = 0; i < model.tri.size(); i++) {
		mytri = &model.tri[i];
		glBegin(GL_TRIANGLES);
		glNormal3fv(mytri->norm);
		glVertex3fv(model.ver[mytri->midedge[0].tail].axis);
		glVertex3fv(model.ver[mytri->midedge[1].tail].axis);
		glVertex3fv(model.ver[mytri->midedge[2].tail].axis);
		glEnd();
	}
}

void glWindow::drawGrid(float size, float step)
{
	// disable lighting
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glColor3f(0.0f, 0.0f, 0.0f);
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
	//	glEnable(GL_LIGHTING);
}

void glWindow::drawAxis(float size)
{
	glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
	glDisable(GL_LIGHTING);
	glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
	//      the light position when you draw GL_LINES
	//      and GL_POINTS. remember the matrix.

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
	glPopMatrix();
	//	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
}