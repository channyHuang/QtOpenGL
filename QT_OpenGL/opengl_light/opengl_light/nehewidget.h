#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL/QGLWidget>
//#include "ui_nehewidget.h"

#include <qgl.h>

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

	void keyPressEvent(QKeyEvent *e);
	void loadGLTextures();

	bool fullscreen;
	GLfloat xrot,yrot,zrot;
	GLfloat zoom,xspeed,yspeed;
	GLuint texture[3],filter;

	bool light;
};

#endif // NEHEWIDGET_H
