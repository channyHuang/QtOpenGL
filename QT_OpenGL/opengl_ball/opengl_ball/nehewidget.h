#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL/QGLWidget>
//#include "ui_nehewidget.h"
#include <gl/GLU.h>
#include <gl/GL.h>
#include <gl/glaux.h>

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

	void glDrawCube();
		
	void keyPressEvent(QKeyEvent *e);
	void loadGLTextures();
	bool fullscreen;
	GLfloat xrot,yrot,zrot;
	GLfloat zoom,xspeed,yspeed;
	GLuint texture[3],filter;

	bool light;

	int    part1;                        // 圆盘的起始角度
	int    part2;                        // 圆盘的结束角度
	int    p1;                        // 增量1
	int    p2;                        // 增量1
	GLUquadricObj *quadratic;                    // 二次几何体
	GLuint  object;                        // 二次几何体标示符

};

#endif // NEHEWIDGET_H
