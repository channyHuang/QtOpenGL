#include "nehewidget.h"

#include <QKeyEvent>

GLfloat lightAmbient[4]={0.5,0.5,0.5,1.0};
GLfloat lightDiffuse[4]={1.0,1.0,1.0,1.0};
GLfloat lightPosition[4]={0.0,0.0,0.0,1.0};

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	xrot=0.0;
	yrot=0.0;
	zrot=0.0;
	zoom=0.0;
	xspeed=yspeed=2.0;
	filter=0;
	light=false;

	p1 = 0;
	p2 = 1;
	object = 0;

	fullscreen=fs;
	setGeometry(100,100,640,480);
//	setCaption("OpenGL window"); //这个函数，不支持了吧？
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{
	gluDeleteQuadric(quadratic);
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

	glLightfv(GL_LIGHT1,GL_AMBIENT,lightAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightDiffuse);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);
	glEnable(GL_LIGHT1);

	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic,GLU_SMOOTH);
	gluQuadricTexture(quadratic,GL_TRUE);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0,0.0,zoom);
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,1.0,0.0);
	glBindTexture(GL_TEXTURE_2D,texture[filter]);

	switch(object) {
	case 0:
		glDrawCube();
		break;
	case 1:
		glTranslatef(0.0f,0.0f,-1.5f);
		gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);
		break;
	case 2:
		gluDisk(quadratic,0.5f,1.5f,32,32);
		break;
	case 3:
		gluSphere(quadratic,1.3f,32,32);
		break;
	case 4:
		glTranslatef(0.0f,0.0f,-1.5f);
		gluCylinder(quadratic,1.0f,0.0f,3.0f,32,32);
		break;
	case 5:
		part1+=p1;
		part2+=p2;
		if(part1>359) {
			p1 = 0;
			p2 = 1;
			part1 = 0;
			part2 = 0;
		}
		if(part2>359) {
			p1 = 1;
			p2 = 0;
		}
		gluPartialDisk(quadratic,0.5f,1.5f,32,32,part1,part2-part1);
		break;
	default:
		break;
	}

	xrot+=xspeed;
	yrot+=yspeed;
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
			setGeometry(0,0,640,480);
		}
		updateGL();
		break;
	case Qt::Key_Space:
		object++;
		if (object > 5) object = 0;
		updateGL();
		break;
	case Qt::Key_Escape:
		close();
	}
}

void nehewidget::loadGLTextures()
{
	QImage tex,buf;
	if(!buf.load("./kaola.jpg")) {
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
	//	glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGB,GL_UNSIGNED_BYTE,tex.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,tex.width(),tex.height(),GL_RGBA,GL_UNSIGNED_BYTE,tex.bits());
}

void nehewidget::glDrawCube()
{
	glBegin(GL_QUADS);
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

	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(-0.2,0.2,-0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(-0.2,0.2,0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(0.2,0.2,0.2);
	glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.2,-0.2);

	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(-0.2,-0.2,-0.2);
	glTexCoord2f(0.0,1.0);glVertex3f(0.2,-0.2,-0.2);
	glTexCoord2f(0.0,0.0);glVertex3f(0.2,-0.2,-0.2);
	glTexCoord2f(1.0,0.0);glVertex3f(-0.2,-0.2,0.2);

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
}