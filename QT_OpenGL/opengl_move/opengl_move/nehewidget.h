#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL/QGLWidget>
//#include "ui_nehewidget.h"

#include <qgl.h>

const GLuint num=50;
typedef struct {
	int r,g,b;
	GLfloat dist,angle;
}stars;

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
	void timerEvent(QTimerEvent *);

	bool fullscreen;
	GLfloat zoom;
	GLuint texture[1];
	GLfloat spin,tilt;
	GLuint loop;

	bool twinkle;
	stars star[num];
};

#endif // NEHEWIDGET_H
