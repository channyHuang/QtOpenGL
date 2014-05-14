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
	void setupworld();

	bool fullscreen;
	GLfloat xrot,yrot,zrot;
	GLfloat zoom;
	GLuint texture[3],filter;

	GLfloat lookupdown,walkbias,walkbiasangle;

	bool light;
	bool blend;
};

#endif // NEHEWIDGET_H
