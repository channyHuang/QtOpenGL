#include "gl/glew.h"
#include "glWidget.h"

#include "gl/GLU.h"

#include "data.hpp"


GlWidget::GlWidget(QGLWidget *parent /* = 0 */) : QGLWidget(parent)
{
	g_camera.camera[0] = 0.0f;
	g_camera.camera[1] = 0.0f;
	g_camera.camera[2] = 1.0f;

	g_camera.cam[0] = g_camera.cam[1] = g_camera.cam[2] = 0.0f;

	g_camera.lookat[0] = 0.0f - g_camera.camera[0];
	g_camera.lookat[1] = 0.0f - g_camera.camera[1];
	g_camera.lookat[2] = 1.0f - g_camera.camera[2];


	g_Counter = 0;
}

GlWidget::~GlWidget()
{
	
}

void GlWidget::resizeGL(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GlWidget::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	gLightOpen[0] = gLightOpen[1] = gLightOpen[2] = true;  //������Դ������
	glEnable(GL_DEPTH_TEST);

//	glewInit();
	createLight();
	isRotatef[3] = true; //Ĭ���ƶ��� ����ת������ͼ

	g_renderObj = 0;
}

void GlWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Modelview Transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(g_camera.camera[0], g_camera.camera[1], g_camera.camera[2], g_camera.lookat[0], g_camera.lookat[1], g_camera.lookat[2], 0, 1, 0);

	glTranslatef(g_camera.cam[0], g_camera.cam[1], g_camera.cam[2]);
	glRotatef((GLfloat)g_RotatefY, 0.0, 1.0, 0.0);
	/*****************************�����Դ2***********************************/

	glPushMatrix();          //�� �����Դ2�ĵ�Բ��
	glTranslatef(g_LightPosition2[0], g_LightPosition2[1], g_LightPosition2[2]);
	glDisable(GL_LIGHTING);        //ʹ��glColor3f��Ҫ���ù���

	if (gLightOpen[1])
	{
		glColor3f(1.0f, 0.2f, 0.2f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	GLUquadricObj *qobj = gluNewQuadric();
	gluSphere(qobj, 0.1, 10.0, 10.0); //����������������ĸ���
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT1, GL_POSITION, g_LightZero);
	//    glLightfv(GL_LIGHT1, GL_POSITION, g_LightPosition2);  //��Դ2 ���ڹ۲�����ϵ
	glPopMatrix();

	if (isRotatef[3])  //�ж��Ƿ���Ҫ��ת��ͼ
	{
		glRotatef((GLfloat)g_mousePos_x, -1.0, 0.0, 0.0);
		glRotatef((GLfloat)g_mousePos_y, 0.0, -1.0, 0.0);
	}
	/*****************************�����һ�����***********************************/

	glPushMatrix();
	glTranslatef(-0.8f, 0.0f, 1.5f);

	if (isRotatef[0])  //�ж��Ƿ���ת
	{
		glRotatef((GLfloat)g_mousePos_x, -1.0, 0.0, 0.0);
		glRotatef((GLfloat)g_mousePos_y, 0.0, -1.0, 0.0);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient_Teapot1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse_Teapot1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular_Teapot1);
	glMaterialfv(GL_FRONT, GL_SHININESS, Shininess_Teapot1);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

//	glutSolidTeapot(1.0);
	gluSphere(qobj, 0.2, 20, 20);

	glTranslatef(g_LightPosition3[0], g_LightPosition3[1], g_LightPosition3[2]); //�Ѿֲ�����ϵ�ƶ�����Ҫ�ŵ��Դ�ĵط�
	glDisable(GL_LIGHTING);        //ʹ��glColor3f��Ҫ���ù���

	if (gLightOpen[2])
	{
		glColor3f(0.2f, 1.0f, 0.2f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}

//	glutSolidSphere(0.2, 10.0, 10.0); //����������������ĸ���
	gluSphere(qobj, 0.1, 10.0, 10.0);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT2, GL_POSITION, g_LightZero);
	//	glLightfv(GL_LIGHT2, GL_POSITION, g_LightPosition3);   //��Դ3�����������ڲ��1������ϵ��
	glPopMatrix();


	/*****************************����ڶ������***********************************/

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.5f);
	if (isRotatef[1])  //�ж��Ƿ���ת
	{
		glRotatef((GLfloat)g_mousePos_x, -1.0, 0.0, 0.0);
		glRotatef((GLfloat)g_mousePos_y, 0.0, -1.0, 0.0);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient_Teapot2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse_Teapot2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular_Teapot2);
	glMaterialfv(GL_FRONT, GL_SHININESS, Shininess_Teapot2);
	glMaterialfv(GL_FRONT, GL_EMISSION, Emission_Teapot2);
//	glutSolidTeapot(1.0);
	gluSphere(qobj, 0.2, 20, 20);
	glPopMatrix();


	/*****************************������������***********************************/

	glPushMatrix();
	glTranslatef(0.8f, 0.0f, 1.5f);
	if (isRotatef[2])  //�ж��Ƿ���Ҫ��ת
	{
		glRotatef((GLfloat)g_mousePos_x, -1.0, 0.0, 0.0);
		glRotatef((GLfloat)g_mousePos_y, 0.0, -1.0, 0.0);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient_Teapot3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse_Teapot3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular_Teapot3);
	glMaterialfv(GL_FRONT, GL_SHININESS, Shininess_Teapot3);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

//	glutSolidTeapot(1.0);
	gluSphere(qobj, 0.2, 20, 20);
	glPopMatrix();


	/*****************************�����Դ1***********************************/

	//���������������������ת�ĵ��Դ
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.5f);
	glRotatef((GLfloat)gRotatefSpeed_1, 0.0, 1.0, 0.0);
	glTranslatef(1.5, 0.0, 0.0);
	glDisable(GL_LIGHTING);        //ʹ��glColor3f��Ҫ���ù���

	if (gLightOpen[0])
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
//	glutSolidSphere(0.3, 10.0, 10.0); //����������������ĸ���
	gluSphere(qobj, 0.1, 10.0, 10.0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, g_LightPosition1);       //��Դ1  ��������ת
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0.0, 0.0, 4.5);

	glEnable(GL_LIGHTING);
	glPopMatrix();


	gRotatefSpeed_1 += 0.4f;
	if (gRotatefSpeed_1 > 360)
	{
		gRotatefSpeed_1 = 0;
	}

	update();
}

void GlWidget::createLight()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat LightAmbient1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular1);

	glEnable(GL_LIGHT1);
	GLfloat LightAmbient2[] = { 1.0f, 0.2f, 0.2f };
	GLfloat LightDiffuse2[] = { 1.0f, 0.2f, 0.2f };
	GLfloat LightSpecular2[] = { 1.0f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular2);

	glEnable(GL_LIGHT2);
	GLfloat LightAmbient3[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat LightDiffuse3[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat LightSpecular3[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular3);
}

