#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL>
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
	void loadGLTextures();
	void buildlists();

	void keyPressEvent(QKeyEvent *e);

	bool fullscreen;
	GLfloat xrot,yrot,zrot;
	GLuint texture[1];
	GLuint box,top,xloop,yloop;
};

#endif // NEHEWIDGET_H
