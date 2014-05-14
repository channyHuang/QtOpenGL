#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL>
//#include "ui_nehewidget.h"

#include <qgl.h>

#define    MAX_PARTICLES    1000        // ��������������

struct particles  
{
	bool    active;                    // �Ƿ񼤻�
	float    life;                    // ��������
	float    fade;                    // ˥���ٶ�
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

	bool    rainbow;            // �Ƿ�Ϊ�ʺ�ģʽ
	float    slowdown;            // ��������
	float    xspeed;                // X������ٶ�
	float    yspeed;                // Y������ٶ�
	float    zoom;            // ��Z������
	GLuint    loop;                // ѭ������
	GLuint    col;                // ��ǰ����ɫ
	GLuint    delay;                // �ʺ�Ч���ӳ�

	particles particle[MAX_PARTICLES];
};

#endif // NEHEWIDGET_H
