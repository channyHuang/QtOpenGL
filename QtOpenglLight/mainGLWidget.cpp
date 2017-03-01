#include "mainGLWidget.h"

#include "data.h"

MainGLWidget::MainGLWidget(QWidget *parent /* = 0 */) : QGLWidget(parent)
{
	xrot = 0.0;
	yrot = 0.0;
	zrot = 0.0;
}

MainGLWidget::~MainGLWidget()
{

}

void MainGLWidget::initializeGL()
{
	model.load(filename);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	gluPerspective(45.0f, 1, 0.1f, 100.0f);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SHININESS, lightShiness);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_EMISSION, lightEmission);
	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	glLightfv(GL_LIGHT1, GL_SHININESS, lightShiness1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	glLightfv(GL_LIGHT1, GL_EMISSION, lightEmission1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT2, GL_SHININESS, lightShiness2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
	glLightfv(GL_LIGHT2, GL_EMISSION, lightEmission2);
	
	glEnable(GL_LIGHTING);
	
	glEnable(GL_DEPTH_TEST);
}

void MainGLWidget::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	displaymodel();
	glPopMatrix();

	//*************** 灯光0
	glPushMatrix();
	glRotatef(lightzrot, 0.0, 0.0, -1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);   //使用指定灯光
	glPopMatrix();

	//*************** 灯光1
	glPushMatrix();
	glRotatef(lightxrot, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glEnable(GL_LIGHT1);   //使用指定灯光
	glPopMatrix();

	//*************** 灯光2
	glPushMatrix();
	glRotatef(lightyrot, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glEnable(GL_LIGHT2);   //使用指定灯光
	glPopMatrix();

	glPopMatrix();

	update();
}

void MainGLWidget::displaymodel()
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