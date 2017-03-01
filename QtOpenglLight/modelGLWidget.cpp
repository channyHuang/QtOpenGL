#include "modelGLWidget.h"

#include <QtWidgets/QMessageBox>

#include <iostream>
using namespace std;
#include "data.h"

ModelGLWidget::ModelGLWidget(QWidget *parent) : QGLWidget(parent)
{
	xrot = 0.0;
	yrot = 0.0;
	zrot = 0.0;
	
}

ModelGLWidget::~ModelGLWidget()
{

}

void ModelGLWidget::initializeGL()
{
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

	//GL_SHININESS ������ָ������ȡֵ��Χ��0��128����ֵԽС����ʾ����Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
	glLightfv(GL_LIGHT1, GL_SHININESS, lightShiness1);

	//GL_AMBIENT ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
	//GL_DIFFUSE �������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ��
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	//GL_SPECULAR �������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ��
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	//GL_EMISSION �ò��ʱ����΢΢�����ⷢ�����
	glLightfv(GL_LIGHT1, GL_EMISSION, lightEmission1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT2, GL_SHININESS, lightShiness2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
	glLightfv(GL_LIGHT2, GL_EMISSION, lightEmission2);
}

void ModelGLWidget::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModelGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

//	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, 0.3, 20, 20);

	glEnable(GL_LIGHTING);
	//************************ �ƹ�0
	glPushMatrix();
	glRotatef(zrot, 0.0, 0.0, -1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	glPopMatrix();
 
	//*********************** �ƹ�1
	glPushMatrix();
	glRotatef(xrot, 1.0, 0.0, 0.0);
	//GL_POSITION ��Դλ��
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glEnable(GL_LIGHT1);
	glPopMatrix();

	//*********************** �ƹ�2
	glPushMatrix();
	glEnable(GL_LIGHT2);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glPopMatrix();
	/*
	xrot -= 0.4f;
	if (xrot < -360) {
		xrot = 0;
	}

	yrot += 0.4f;
	if (yrot > 360) {
		yrot = 0;
	}

	zrot += 0.4f;
	if (xrot > 360) {
		zrot = 0;
	}
	*/
	update();
}

void ModelGLWidget::mousePressEvent(QMouseEvent *e)
{
	QPoint st(e->pos());
	startPoint = st;
}
void ModelGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	
}
void ModelGLWidget::mouseMoveEvent(QMouseEvent *e)
{
	QPoint ed(e->pos());
	endPoint = ed;
//	xrot += endPoint.x() - startPoint.x();
	update();
}
