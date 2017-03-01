#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>

#include "gl/GLU.h"

class glWindow : public QGLWidget
{
	Q_OBJECT

public:
	glWindow(QWidget *parent = 0);
	~glWindow();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	void initLights();
	void drawSpheres();
};

#endif