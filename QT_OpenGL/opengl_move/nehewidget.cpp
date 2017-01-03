#include "nehewidget.h"

#include <gl/GLU.h>
#include <QKeyEvent>

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	zoom=-0.0;
	tilt=90.0;
	spin=0.0;
	loop=0;
	twinkle=false;

	fullscreen=fs;
	setGeometry(100,100,640,480);
//	setCaption("OpenGL window"); //这个函数，不支持了吧？
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();

	startTimer(5);
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

//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
//	glEnable(GL_BLEND);
	for(loop=0;loop<num;loop++) {
		star[loop].angle=0.0;
		star[loop].dist=((float)loop)/num*1.5;
		star[loop].r=rand()%256;
		star[loop].g=rand()%256;
		star[loop].b=rand()%256;
	}
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	for(loop=0;loop<num;loop++) {
		glLoadIdentity();

		glTranslatef(0.0,0.0,zoom);
		glRotatef(tilt,1.0,0.0,0.0);
		glRotatef(star[loop].angle,0.0,1.0,0.0);
		glTranslatef(star[loop].dist,0.0,0.0);
		glRotatef(-star[loop].angle,0.0,1.0,0.0);
		glRotatef(-tilt,1.0,0.0,0.0);

		if(twinkle) {
			glColor4ub(star[(num-loop)-1].r,star[(num-loop)-1].g,star[(num-loop)-1].b,255);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);glVertex3f(-0.01,-0.01,0.01);
			glTexCoord2f(1.0,0.0);glVertex3f(0.01,-0.01,0.01);
			glTexCoord2f(1.0,1.0);glVertex3f(0.01,0.01,0.01);
			glTexCoord2f(0.0,1.0);glVertex3f(-0.01,0.01,0.01);
			glEnd();
		}
		glRotatef(spin,0.0,0.0,1.0);
		glColor4ub(star[loop].r,star[loop].g,star[loop].b,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);glVertex3f(-0.01,-0.01,0.01);
		glTexCoord2f(1.0,0.0);glVertex3f(0.01,-0.01,0.01);
		glTexCoord2f(1.0,1.0);glVertex3f(0.01,0.01,0.01);
		glTexCoord2f(0.0,1.0);glVertex3f(-0.01,0.01,0.01);
		glEnd();

		spin+=0.01;
		star[loop].angle+=((float)loop)/num;
		star[loop].dist-=0.01;
		if(star[loop].dist<0.0) {
			star[loop].dist+=1.5;
			star[loop].r=rand()%256;
			star[loop].g=rand()%256;
			star[loop].b=rand()%256;
		}
	}
}

void nehewidget::timerEvent(QTimerEvent *)
{
	updateGL();
}

void nehewidget::resizeGL(int w,int h)
{
	if(h==0) h=1;
	glViewport(0,0,(GLint)w,(GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//下面这个函数在Qt和OpenGL新版本中都不支持了！先注释掉吧，以后不得不用时再想办法
//	gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nehewidget::keyPressEvent(QKeyEvent *e)
{
	switch(e->key()) {
	case Qt::Key_T:
		twinkle=!twinkle;
		updateGL();
		break;
	case Qt::Key_PageUp:
		zoom-=0.2;
		updateGL();
		break;
	case Qt::Key_PageDown:
		zoom+=0.2;
		updateGL();
		break;
	case Qt::Key_Up:
		tilt-=0.5;
		updateGL();
		break;
	case Qt::Key_Down:
		tilt+=0.5;
		updateGL();
		break;
	case Qt::Key_F2:
		fullscreen=!fullscreen;
		if(fullscreen) showFullScreen();
		else {
			showNormal();
			setGeometry(100,100,640,480);
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
	if(!buf.load("texture.bmp")) {
		qWarning("Please use single-color instead");
		QImage dummy(128,128,QImage::Format_RGB32);
		dummy.fill(Qt::red);
		buf=dummy;
	}
	tex=QGLWidget::convertToGLFormat(buf);
	glGenTextures(1,&texture[0]);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}