#include "nehewidget.h"

#include <gl/GLU.h>
#include <QKeyEvent>

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	fullscreen=fs;
	setGeometry(50,50,640,480);
//	setCaption("OpenGL window"); //�����������֧���˰ɣ�
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{

}

void nehewidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//�ѵ���gluPerspective��Ե�ʣ���������СһЩ���ܿ���ͼ��
	//����Բ�κ���Ļ��С�й�ϵ����Ļ���Ծ��������α䳤�����ˡ���
	glTranslatef(-0.3,0.3,-0.6);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0,0.2,0.0);
	glVertex3f(-0.2,-0.2,0.0);
	glVertex3f(0.2,-0.2,0.0);
	glEnd();
	glTranslatef(0.6,0,0);
	glBegin(GL_QUADS);
	glVertex3f(-0.2,0.2,0);
	glVertex3f(0.2,0.2,0);
	glVertex3f(0.2,-0.2,0);
	glVertex3f(-0.2,-0.2,0);
	glEnd();
	//���汻ע�͵�һ��������ӵģ�����Ȥ�Ŀ���ȥ��ע������һ��
	//�������ĵ�����������ƽ�Բ��һ�����ģ�һ��ʵ��
/*
	glTranslatef(-0.5,-0.5,0.0);
	GLfloat x,y,angle;
	glBegin(GL_POINTS);
	for(angle=0;angle<2*3.1415926;angle+=0.001) {
		x=0.2*sin(angle);
		y=0.2*cos(angle);
		glVertex3f(x,y,0.0);
	}
	glEnd();
	glTranslatef(0.5,0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0;i<100;i++) {
		float angle=2*3.1415926*i/100;
		glVertex3f(0.2*cos(angle),0.2*sin(angle),0);
	}
	glEnd();
*/
}

void nehewidget::resizeGL(int w,int h)
{
	if(h==0) h=1;
	glViewport(0,0,(GLint)w,(GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//�������������Qt��OpenGL�°汾�ж���֧���ˣ���ע�͵��ɣ��Ժ󲻵ò���ʱ����취
//	gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nehewidget::keyPressEvent(QKeyEvent *e)
{
	switch(e->key()) {
	case Qt::Key_F2:
		fullscreen=!fullscreen;
		if(fullscreen) showFullScreen();
		else {
			showNormal();
			setGeometry(0,0,640,480);
		}
		updateGL();
		break;
	case Qt::Key_Escape:
		close();
	}
}