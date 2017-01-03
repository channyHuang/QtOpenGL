#include "nehewidget.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include <QKeyEvent>
#include <QImage>
#include <QColor>

static GLfloat boxcol[5][3]=
{
	{1.0,0.0,0.0},
	{1.0,0.5,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,1.0}
};
static GLfloat topcol[5][3]=
{
	{0.5,0.0, 0.0 },
	{ 0.5, 0.25, 0.0 },
	{ 0.5, 0.5, 0.0 },
	{ 0.0, 0.5, 0.0 },
	{ 0.0, 0.5, 0.5 }
};

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	xrot=yrot=zrot=0.0;
	box=top=0;
	xloop=yloop=0;

	fullscreen=fs;
	setGeometry(100,100,640,480);
//	setCaption("OpenGL window"); //这个函数，不支持了吧？
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{

}

void nehewidget::initializeGL()
{
	loadGLTextures();
	buildlists();
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,texture[0]);

	for (yloop=1;yloop<6;yloop++)
		for(xloop=0;xloop<yloop;xloop++) {
			glLoadIdentity();
			//下面这句应该怎么改？突然发现画得太大了，屏幕放不下……
//			glTranslatef(1.4+(float(xloop)*2.8)-(float(yloop)*1.4),((6.0-(float(yloop)))*2.4)-7.0,-20.0);
			glTranslatef(xloop*0.5-yloop*0.2,yloop*0.5-1.0,0.0);
			glRotatef(45.0-(2.0*yloop)+xrot,1.0,0.0,0.0);
			glRotatef(45.0+yrot,0.0,1.0,0.0);
			glColor3fv(boxcol[yloop-1]);
			glCallList(box);
			glColor3fv(topcol[yloop-1]);
			glCallList(top);
		} 
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
	case Qt::Key_Up:
		xrot-=0.2;
		updateGL();
		break;
	case Qt::Key_Down:
		xrot+=0.2;
		updateGL();
		break;
	case Qt::Key_Left:
		yrot-=0.2;
		updateGL();
		break;
	case Qt::Key_Right:
		yrot+=0.2;
		updateGL();
		break;
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
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void nehewidget::buildlists()
{
	box=glGenLists(2);
	glNewList(box,GL_COMPILE);
	glBegin(GL_QUADS);

	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(-0.2,-0.2,-0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(0.2,-0.2,-0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(0.2,-0.2,0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(-0.2,-0.2,0.2);
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,0.0);glVertex3f(-0.2,-0.2,0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(0.2,-0.2,0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.2,0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.2,0.2,0.2);
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(1.0,0.0);glVertex3f(-0.2,-0.2,-0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(-0.2,0.2,-0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(0.2,0.2,-0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(0.2,-0.2,-0.2);
	glNormal3f(1.0,0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(0.2,-0.2,-0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.2,-0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(0.2,0.2,0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(0.2,-0.2,0.2);
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0.0,0.0);glVertex3f(-0.2,-0.2,-0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(-0.2,-0.2,0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(-0.2,0.2,0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.2,0.2,-0.2);

	glEnd();
	glEndList();
	top=box+1;
	glNewList(top,GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.2,0.2,-0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(-0.2,0.2,0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(0.2,0.2,0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.2,-0.2);
	glEnd();
	glEndList();
}