#include "nehewidget.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glaux.h>

#include <QKeyEvent>
#include <QImage>
#include <QColor>

static GLfloat colors[12][3]=                // 彩虹颜色
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

	glDisable(GL_DEPTH_TEST);
	 for (loop=0;loop<MAX_PARTICLES;loop++)  {
/*
		 particle[loop].x=0.0f;
		 particle[loop].y=0.0f;
		 particle[loop].z=0.0f;*/

		 particle[loop].active=true;                    // 使所有的粒子为激活状态
		 particle[loop].life=1.0f;                    // 所有的粒子生命值为最大
		 particle[loop].fade=float(rand()%100)/1000.0f
+0.003f;        // 随机生成衰减速率
		 particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];        // 粒子的红色颜色
		 particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];        // 粒子的绿色颜色
		 particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];        // 粒子的蓝色颜色
		 particle[loop].xi=float((rand()%50)-26.0f)*10.0f;        // 随机生成X轴方向速度
		 particle[loop].yi=float((rand()%50)-25.0f)*10.0f;        // 随机生成Y轴方向速度
		 particle[loop].zi=float((rand()%50)-25.0f)*10.0f;        // 随机生成Z轴方向速度
		 particle[loop].xg=0.0f;                        // 设置X轴方向加速度为0
		 particle[loop].yg=-0.8f;                        //  设置Y轴方向加速度为-0.8
		 particle[loop].zg=0.0f;                        //  设置Z轴方向加速度为0
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
			float y=particle[loop].y;                // 返回Y轴的位置
			float z=particle[loop].z+zoom;            // 返回Z轴的位置
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);
			glBegin(GL_TRIANGLE_STRIP);                // 绘制三角形带
			glTexCoord2d(1,1); glVertex3f(x+0.05f,y+0.05f,z); 
			glTexCoord2d(0,1); glVertex3f(x-0.05f,y+0.05f,z); 
			glTexCoord2d(1,0); glVertex3f(x+0.05f,y-0.05f,z); 
			glTexCoord2d(0,0); glVertex3f(x-0.05f,y-0.05f,z); 
			glEnd();

			particle[loop].x+=particle[loop].xi/(slowdown*1000);    // 更新X坐标的位置
			particle[loop].y+=particle[loop].yi/(slowdown*1000);    // 更新Y坐标的位置
			particle[loop].z+=particle[loop].zi/(slowdown*1000);    // 更新Z坐标的位置
			particle[loop].xi+=particle[loop].xg;            // 更新X轴方向速度大小
			particle[loop].yi+=particle[loop].yg;            // 更新Y轴方向速度大小
			particle[loop].zi+=particle[loop].zg;            // 更新Z轴方向速度大小
			particle[loop].life-=particle[loop].fade;        // 减少粒子的生命值
			if (particle[loop].life<0.0f)    {                // 如果粒子生命值小于0
				particle[loop].life=1.0f;                // 产生一个新的粒子
				particle[loop].fade=float(rand()%100)/1000.0f+0.003f;    // 随机生成衰减速率
				particle[loop].x=0.0f;                    // 新粒子出现在屏幕的中央
				particle[loop].y=0.0f;                    
				particle[loop].z=0.0f;
				particle[loop].xi=xspeed+float((rand()%60)-32.0f);    // 随机生成粒子速度
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);    
				particle[loop].zi=float((rand()%60)-30.0f);     
				particle[loop].r=colors[col][0];            // 设置粒子颜色
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