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

	int    part1;                        // Բ�̵���ʼ�Ƕ�
	int    part2;                        // Բ�̵Ľ����Ƕ�
	int    p1;                        // ����1
	int    p2;                        // ����1
	GLUquadricObj *quadratic;                    // ���μ�����
	GLuint  object;                        // ���μ������ʾ��

};

#endif // NEHEWIDGET_H
