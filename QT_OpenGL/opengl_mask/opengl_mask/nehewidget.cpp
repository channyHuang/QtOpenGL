#include "nehewidget.h"

nehewidget::nehewidget(QWidget *parent)
	: QGLWidget(parent)
{
	masking=TRUE;
	roll = 0;
	scene=true;
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
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,-1.0f); 
	glBindTexture(GL_TEXTURE_2D, texture[0]);    // ѡ��Logo����
	glBegin(GL_QUADS);       // ���������ı���
	glTexCoord2f(0.0f, -roll+0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
	glTexCoord2f(3.0f, -roll+0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
	glTexCoord2f(3.0f, -roll+3.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
	glTexCoord2f(0.0f, -roll+3.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
	glEnd();

	glEnable(GL_BLEND);       // ���û��
	glDisable(GL_DEPTH_TEST);       // ������Ȳ���
	if(masking) {
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
	}
	if(scene) {
		glTranslatef(0.0f,0.0f,-1.0f);     // ������Ļһ����λ
		glRotatef(roll*360,0.0f,0.0f,1.0f);     // ��Z����ת
		if(masking) {
			glBindTexture(GL_TEXTURE_2D, texture[1]);  // ѡ��ڶ�������ģ������
			glBegin(GL_QUADS);     // ��ʼ�����ı���
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
			glEnd();     
		}
		glBlendFunc(GL_ONE, GL_ONE);    // ������2���Ƶ���Ļ
		glBindTexture(GL_TEXTURE_2D, texture[0]);   // ѡ��ڶ�������
		glBegin(GL_QUADS);      // �����ı���
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
		glEnd();
	}
	else {
		if(masking) {
			glBindTexture(GL_TEXTURE_2D, texture[1]);  // ѡ���һ������ģ������
			glBegin(GL_QUADS);     // ��ʼ�����ı���
			glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
			glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
			glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
			glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
			glEnd();     
		}
		glBlendFunc(GL_ONE, GL_ONE);     // ������1���Ƶ���Ļ
		glBindTexture(GL_TEXTURE_2D, texture[2]);    // ѡ���һ������
		glBegin(GL_QUADS);       // ��ʼ�����ı���
		glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
		glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
		glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
		glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
		glEnd();   

	}
	glEnable(GL_DEPTH_TEST);       // ������Ȳ���
	glDisable(GL_BLEND);       // ���û��
	roll+=0.002f;        // ���������������
	if(roll>1.0f) roll-=1.0f;
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

void nehewidget::loadGLTextures()
{
	QImage tex,buf;
	if(!buf.load("texture.bmp")) {
		qWarning("Please use single-color instead");
		QImage dummy(128,128,QImage::Format_RGB32);
		dummy.fill(Qt::red);
		buf=dummy;
	}
	tex=QGLWidget::convertToGLFormat(buf);
	glGenTextures(3,&texture[0]);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

//	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,tex.width(),tex.height(),GL_RGBA,GL_UNSIGNED_BYTE,tex.bits());
}