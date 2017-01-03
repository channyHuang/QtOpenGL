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

	void loadTextures();
	void keyPressEvent(QKeyEvent *e);
	bool fullscreen;
};

#endif // NEHEWIDGET_H
