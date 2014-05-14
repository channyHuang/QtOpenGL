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
	glBindTexture(GL_TEXTURE_2D, texture[0]);    // 选择Logo纹理
	glBegin(GL_QUADS);       // 绘制纹理四边形
	glTexCoord2f(0.0f, -roll+0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
	glTexCoord2f(3.0f, -roll+0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
	glTexCoord2f(3.0f, -roll+3.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
	glTexCoord2f(0.0f, -roll+3.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
	glEnd();

	glEnable(GL_BLEND);       // 启用混合
	glDisable(GL_DEPTH_TEST);       // 禁用深度测试
	if(masking) {
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
	}
	if(scene) {
		glTranslatef(0.0f,0.0f,-1.0f);     // 移入屏幕一个单位
		glRotatef(roll*360,0.0f,0.0f,1.0f);     // 沿Z轴旋转
		if(masking) {
			glBindTexture(GL_TEXTURE_2D, texture[1]);  // 选择第二个“掩模”纹理
			glBegin(GL_QUADS);     // 开始绘制四边形
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
			glEnd();     
		}
		glBlendFunc(GL_ONE, GL_ONE);    // 把纹理2复制到屏幕
		glBindTexture(GL_TEXTURE_2D, texture[0]);   // 选择第二个纹理
		glBegin(GL_QUADS);      // 绘制四边形
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
		glEnd();
	}
	else {
		if(masking) {
			glBindTexture(GL_TEXTURE_2D, texture[1]);  // 选择第一个“掩模”纹理
			glBegin(GL_QUADS);     // 开始绘制四边形
			glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
			glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
			glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
			glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
			glEnd();     
		}
		glBlendFunc(GL_ONE, GL_ONE);     // 把纹理1复制到屏幕
		glBindTexture(GL_TEXTURE_2D, texture[2]);    // 选择第一个纹理
		glBegin(GL_QUADS);       // 开始绘制四边形
		glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-0.6f, -0.6f,  0.0f); 
		glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 0.6f, -0.6f,  0.0f); 
		glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 0.6f,  0.6f,  0.0f); 
		glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-0.6f,  0.6f,  0.0f); 
		glEnd();   

	}
	glEnable(GL_DEPTH_TEST);       // 启用深度测试
	glDisable(GL_BLEND);       // 禁用混合
	roll+=0.002f;        // 增加纹理滚动变量
	if(roll>1.0f) roll-=1.0f;
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