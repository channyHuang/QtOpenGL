#ifndef GLWINDOW3D_H
#define GLWINDOW3D_H

#include <QGLWidget>

#include "gl/GLU.h"

class glWindow3D : public QGLWidget
{
	Q_OBJECT

public:
	glWindow3D(QWidget *parent = 0);
	~glWindow3D();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	void initLights();
	void drawGrid(float size, float step);
	void drawAxis(float size);
	void drawSpheres();
};

#endif