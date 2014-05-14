#include "nehewidget.h"

#include <gl/GLU.h>
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <math.h>

GLfloat lightAmbient[4]={0.5,0.5,0.5,1.0};
GLfloat lightDiffuse[4]={1.0,1.0,1.0,1.0};
GLfloat lightPosition[4]={0.0,0.0,0.0,1.0};

typedef struct tagvertex {
	float x,y,z,u,v;
}VERTEX;
typedef struct tagtrangle {
	VERTEX vertex[3];
}TRIANGLE;
typedef struct tagsector {
	int numtriangles;
	TRIANGLE *triangles;
}SECTOR;
SECTOR sector1;
float heading=0.0,prover=0.0174532925f;

void nehewidget::setupworld()
{
	float x,y,z,u,v;
	int numtriangles;
	char line[255];
	std::ifstream file;
	file.open("World.txt");
	file.getline(line,250);
	file.getline(line,250);
	sscanf(line,"NUMPOLLIES %d",&numtriangles);
	sector1.triangles=new TRIANGLE[numtriangles];
	sector1.numtriangles=numtriangles;
	for(int loop=0;loop<numtriangles;loop++)
		for(int vert=0;vert<3;vert++) {
			file.getline(line,250);
			while(line[0]=='/'||line[0]=='\n') file.getline(line,250);
			sscanf(line,"%f %f %f %f %f",&sector1.triangles[loop].vertex[vert].x,&sector1.triangles[loop].vertex[vert].y,&sector1.triangles[loop].vertex[vert].z,&sector1.triangles[loop].vertex[vert].u,&sector1.triangles[loop].vertex[vert].v);
//			sector1.triangles[loop].vertex->x/=2;
//			sector1.triangles[loop].vertex->y/=2;
//			sector1.triangles[loop].vertex->z/=2;
		}
	file.close();
}

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	xrot=0.0;
	yrot=0.0;
	zrot=0.0;
	zoom=0.0;
	filter=0;
	light=false;
	blend=false;

	lookupdown=0.0f;
	walkbias=0.0f;
	walkbiasangle=0.0f;

	//setupworld();

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

	glColor4f(1.0,1.0,1.0,0.5);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	setupworld();
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat xx,yy,zz,uu,vv;
	GLfloat sceneroty=360.0f-yrot;

	glRotatef(lookupdown,1.0,0.0,0.0);
	glRotatef(sceneroty,0.0,1.0,0.0);
	glTranslatef(-xrot,-walkbias-0.25f,-zrot);
	
	glBindTexture(GL_TEXTURE_2D,texture[filter]);
	for(int loop=0;loop<sector1.numtriangles;loop++) {
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0,0.0,1.0);
		xx=sector1.triangles[loop].vertex[0].x;
		yy=sector1.triangles[loop].vertex[0].y;
		zz=sector1.triangles[loop].vertex[0].z;
		uu=sector1.triangles[loop].vertex[0].u;
		vv=sector1.triangles[loop].vertex[0].v;
		glTexCoord2f(uu,vv);glVertex3f(xx,yy,zz);

		xx=sector1.triangles[loop].vertex[1].x;
		yy=sector1.triangles[loop].vertex[1].y;
		zz=sector1.triangles[loop].vertex[1].z;
		uu=sector1.triangles[loop].vertex[1].u;
		vv=sector1.triangles[loop].vertex[1].v;
		glTexCoord2f(uu,vv);glVertex3f(xx,yy,zz);

		xx=sector1.triangles[loop].vertex[2].x;
		yy=sector1.triangles[loop].vertex[2].y;
		zz=sector1.triangles[loop].vertex[2].z;
		uu=sector1.triangles[loop].vertex[2].u;
		vv=sector1.triangles[loop].vertex[2].v;
		glTexCoord2f(uu,vv);glVertex3f(xx,yy,zz);
		
		glEnd();
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
	case Qt::Key_L:
		light=!light;
		if(!light) {
			glDisable(GL_LIGHTING);
		}
		else {
			glEnable(GL_LIGHTING);
		}
		updateGL();
		break;
	case Qt::Key_B:
		blend=!blend;
		if(blend) {
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
		}
		else {
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		}
		updateGL();
		break;
	case Qt::Key_F:
		filter+=1;
		if(filter>2) {
			filter=0;
		}
		updateGL();
		break;
	case Qt::Key_PageUp:
		zoom-=0.2;
		lookupdown-=1.0f;
		updateGL();
		break;
	case Qt::Key_PageDown:
		zoom+=0.2;
		lookupdown+=1.0f;
		updateGL();
		break;
	case Qt::Key_Up:
		xrot-=(float)sin(heading*prover)*0.05f;
		zrot-=(float)cos(heading*prover)*0.05f;
		if(walkbiasangle>=359.0f) walkbiasangle=0.0f;
		else walkbiasangle+=10;
		walkbias=(float)sin(walkbiasangle*prover)/20.0f;
		updateGL();
		break;
	case Qt::Key_Down:
		xrot+=(float)sin(heading*prover)*0.05f;
		zrot+=(float)cos(heading*prover)*0.05f;
		if(walkbiasangle<=1.0f) walkbiasangle=359.0f;
		else walkbiasangle-=10;
		walkbias=(float)sin(walkbiasangle*prover)/20.0f;
		updateGL();
		break;
	case Qt::Key_Right:
		yrot-=1.0f;
		updateGL();
		break;
	case Qt::Key_Left:
		yrot+=1.0f;
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
	if(!buf.load("Mud.bmp")) {
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