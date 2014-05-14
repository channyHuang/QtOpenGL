#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL>
//#include "ui_nehewidget.h"

#include <qgl.h>

#define    MAX_PARTICLES    1000        // 定义最大的粒子数

struct particles  
{
	bool    active;                    // 是否激活
	float    life;                    // 粒子生命
	float    fade;                    // 衰减速度
	float r,g,b;
	float x,y,z;
	float xi,yi,zi;
	float xg,yg,zg;
};

class nehewidget : public QGLWidget
{
	Q_OBJECT

public:
	nehewidget(QWidget *parent = 0,bool fs=false);
	~nehewidget();

protected:

	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void loadGLTextures();

	void keyPressEvent(QKeyEvent *e);

	bool fullscreen;
	GLfloat xrot,yrot,zrot;
	GLuint texture[1];

	bool    rainbow;            // 是否为彩虹模式
	float    slowdown;            // 减速粒子
	float    xspeed;                // X方向的速度
	float    yspeed;                // Y方向的速度
	float    zoom;            // 沿Z轴缩放
	GLuint    loop;                // 循环变量
	GLuint    col;                // 当前的颜色
	GLuint    delay;                // 彩虹效果延迟

	particles particle[MAX_PARTICLES];
};

#endif // NEHEWIDGET_H
