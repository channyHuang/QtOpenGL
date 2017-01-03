#include "nehewidget.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glaux.h>

#include <QKeyEvent>
#include <QImage>
#include <QColor>

static GLfloat colors[12][3]=                // �ʺ���ɫ
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};


nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	slowdown=2.0f;
	zoom=-1.0f;

	fullscreen=fs;
	setGeometry(100,100,640,480);
	//	setCaption("OpenGL window"); //�����������֧���˰ɣ�
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{

}

void nehewidget::initializeGL()
{
	loadGLTextures();
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_DEPTH_TEST);
	 for (loop=0;loop<MAX_PARTICLES;loop++)  {
/*
		 particle[loop].x=0.0f;
		 particle[loop].y=0.0f;
		 particle[loop].z=0.0f;*/

		 particle[loop].active=true;                    // ʹ���е�����Ϊ����״̬
		 particle[loop].life=1.0f;                    // ���е���������ֵΪ���
		 particle[loop].fade=float(rand()%100)/1000.0f
+0.003f;        // �������˥������
		 particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];        // ���ӵĺ�ɫ��ɫ
		 particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];        // ���ӵ���ɫ��ɫ
		 particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];        // ���ӵ���ɫ��ɫ
		 particle[loop].xi=float((rand()%50)-26.0f)*10.0f;        // �������X�᷽���ٶ�
		 particle[loop].yi=float((rand()%50)-25.0f)*10.0f;        // �������Y�᷽���ٶ�
		 particle[loop].zi=float((rand()%50)-25.0f)*10.0f;        // �������Z�᷽���ٶ�
		 particle[loop].xg=0.0f;                        // ����X�᷽����ٶ�Ϊ0
		 particle[loop].yg=-0.8f;                        //  ����Y�᷽����ٶ�Ϊ-0.8
		 particle[loop].zg=0.0f;                        //  ����Z�᷽����ٶ�Ϊ0
	 }
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	for (loop=0;loop<MAX_PARTICLES;loop++)  {
		if (particle[loop].active) {
			float x=particle[loop].x;
			float y=particle[loop].y;                // ����Y���λ��
			float z=particle[loop].z+zoom;            // ����Z���λ��
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);
			glBegin(GL_TRIANGLE_STRIP);                // ���������δ�
			glTexCoord2d(1,1); glVertex3f(x+0.05f,y+0.05f,z); 
			glTexCoord2d(0,1); glVertex3f(x-0.05f,y+0.05f,z); 
			glTexCoord2d(1,0); glVertex3f(x+0.05f,y-0.05f,z); 
			glTexCoord2d(0,0); glVertex3f(x-0.05f,y-0.05f,z); 
			glEnd();

			particle[loop].x+=particle[loop].xi/(slowdown*1000);    // ����X�����λ��
			particle[loop].y+=particle[loop].yi/(slowdown*1000);    // ����Y�����λ��
			particle[loop].z+=particle[loop].zi/(slowdown*1000);    // ����Z�����λ��
			particle[loop].xi+=particle[loop].xg;            // ����X�᷽���ٶȴ�С
			particle[loop].yi+=particle[loop].yg;            // ����Y�᷽���ٶȴ�С
			particle[loop].zi+=particle[loop].zg;            // ����Z�᷽���ٶȴ�С
			particle[loop].life-=particle[loop].fade;        // �������ӵ�����ֵ
			if (particle[loop].life<0.0f)    {                // �����������ֵС��0
				particle[loop].life=1.0f;                // ����һ���µ�����
				particle[loop].fade=float(rand()%100)/1000.0f+0.003f;    // �������˥������
				particle[loop].x=0.0f;                    // �����ӳ�������Ļ������
				particle[loop].y=0.0f;                    
				particle[loop].z=0.0f;
				particle[loop].xi=xspeed+float((rand()%60)-32.0f);    // ������������ٶ�
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);    
				particle[loop].zi=float((rand()%60)-30.0f);     
				particle[loop].r=colors[col][0];            // ����������ɫ
				particle[loop].g=colors[col][1];            
				particle[loop].b=colors[col][2];        
			} 
		}
	}
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

void nehewidget::loadGLTextures()
{
	QImage tex,buf;
	if(!buf.load("./texture.bmp")) {
		qWarning("Please use single-color instead");
		QImage dummy(128,128,QImage::Format_RGB32);
		dummy.fill(Qt::red);
		buf=dummy;
	}
	tex=QGLWidget::convertToGLFormat(buf);
	glGenTextures(1,&texture[0]);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}