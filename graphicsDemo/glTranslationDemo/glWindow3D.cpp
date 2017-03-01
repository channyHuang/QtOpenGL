#include "glWindow3D.h"

#include "data.h"

glWindow3D::glWindow3D(QWidget *parent) : QGLWidget(parent)
{

}

glWindow3D::~glWindow3D()
{}

void glWindow3D::initializeGL()
{
	model.load("teapot.obj");

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void glWindow3D::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glWindow3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0, 0, viewmatrix.get(0, 3));
	glRotatef(45, 1, 0, 0);
	glRotatef(-45, 0, 1, 0);
	drawGrid(10, 1);

	glPushMatrix();
	glTranslatef(modelmatrix.get(0, 3), modelmatrix.get(1, 3), modelmatrix.get(2, 3));
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glRotatef(rotz, 0, 0, 1);
	drawAxis(4);
	displaymodel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(viewmatrix.get(0, 3), viewmatrix.get(1, 3), viewmatrix.get(2, 3));
	drawFrustum(60.0, 1, 1, 10);
	glPopMatrix();

	glPopMatrix();

	update();
}

void glWindow3D::displaymodel()
{
	if (model.tri.size() <= 0) return;
	Triangle *mytri;
	glColor3f(0.1, 0.2, 0.3);
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

void glWindow3D::drawGrid(float size, float step)
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

void glWindow3D::drawAxis(float size)
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

void glWindow3D::drawFrustum(float fovY, float aspectRatio, float nearPlane, float farPlane)
{
	float tangent = tanf(fovY / 2 * DEG2RAD);
	float nearHeight = nearPlane * tangent;
	float nearWidth = nearHeight * aspectRatio;
	float farHeight = farPlane * tangent;
	float farWidth = farHeight * aspectRatio;

	// compute 8 vertices of the frustum
	float vertices[8][3];
	// near top right
	vertices[0][0] = nearWidth;     vertices[0][1] = nearHeight;    vertices[0][2] = -nearPlane;
	// near top left
	vertices[1][0] = -nearWidth;    vertices[1][1] = nearHeight;    vertices[1][2] = -nearPlane;
	// near bottom left
	vertices[2][0] = -nearWidth;    vertices[2][1] = -nearHeight;   vertices[2][2] = -nearPlane;
	// near bottom right
	vertices[3][0] = nearWidth;     vertices[3][1] = -nearHeight;   vertices[3][2] = -nearPlane;
	// far top right
	vertices[4][0] = farWidth;      vertices[4][1] = farHeight;     vertices[4][2] = -farPlane;
	// far top left
	vertices[5][0] = -farWidth;     vertices[5][1] = farHeight;     vertices[5][2] = -farPlane;
	// far bottom left
	vertices[6][0] = -farWidth;     vertices[6][1] = -farHeight;    vertices[6][2] = -farPlane;
	// far bottom right
	vertices[7][0] = farWidth;      vertices[7][1] = -farHeight;    vertices[7][2] = -farPlane;

	float colorLine1[4] = { 0.7f, 0.7f, 0.7f, 0.7f };
	float colorLine2[4] = { 0.2f, 0.2f, 0.2f, 0.7f };
	float colorPlane[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw the edges around frustum
	glBegin(GL_LINES);
	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[4]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[5]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[6]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[7]);
	glEnd();

	glColor4fv(colorLine1);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);
	glEnd();

	glColor4fv(colorLine1);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glEnd();

	// draw near and far plane
	glColor4fv(colorPlane);
	glBegin(GL_QUADS);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);
	glEnd();

	glEnable(GL_CULL_FACE);
//	glEnable(GL_LIGHTING);
}