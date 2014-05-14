#include "nehewidget.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include <QKeyEvent>
#include <QImage>
#include <QColor>

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	xrot=yrot=zrot=0.0;
	hold=0.0;
	wigglecount=0;

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

	glPolygonMode(GL_BACK,GL_FILL);
	glPolygonMode(GL_FRONT,GL_LINE);
	for(int x=0;x<45;x++)
		for(int y=0;y<45;y++) {
			points[x][y][0]=float((x/9.0)-4.5);
			points[x][y][1]=float((y/9.0)-4.5);
			points[x][y][2]=float(sin((((x/9.0)*40.0)/360.0)*3.1415926*2.0));
		}
}

void nehewidget::paintGL()
{
	int x,y;
	float fx,fy,fxb,fyb;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0,0.0,0.0);
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,1.0,0.0);
	glRotatef(zrot,0.0,0.0,1.0);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin(GL_QUADS);

	for(x=0;x<44;x++) 
		for(y=0;y<44;y++) {
			fx=float(x)/44.0;
			fy=float(y)/44.0;
			fxb=float(x+1)/44.0;
			fyb=float(y+1)/44.0;
			glTexCoord2f(fx,fy);
			glVertex3f(points[x][y][0],points[x][y][1],points[x][y][2]);
			glTexCoord2f(fx,fyb);
			glVertex3f(points[x][y+1][0],points[x][y+1][1],points[x][y+1][2]);
			glTexCoord2f(fxb,fyb);
			glVertex3f(points[x+1][y+1][0],points[x+1][y+1][1],points[x+1][y+1][2]);
			glTexCoord2f(fxb,fy);
			glVertex3f(points[x+1][y][0],points[x+1][y][1],points[x+1][y][2]);
		}
	
	glEnd();

	if(wigglecount==2) {
		for(y=0;y<45;y++) {
			hold=points[0][y][2];
			for(x=0;x<45;x++) {
				points[x][y][2]=points[x+1][y][2];
			}
			points[44][y][2]=hold;
		}
		wigglecount=0;
	}
	wigglecount++;
	xrot+=0.3;
	yrot+=0.2;
	zrot+=0.4;
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
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}