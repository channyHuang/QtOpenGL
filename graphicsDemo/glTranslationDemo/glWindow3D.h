#ifndef GLWINDOW3D_H
#define GLWINDOW3D_H

#include <QGLWidget>

#include "model.h"

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
	void displaymodel();
	void drawGrid(float size, float step);
	void drawAxis(float size);
	void drawFrustum(float fovY, float aspectRatio, float nearPlane, float farPlane);

	const float DEG2RAD = 3.141593f / 180;


	Model model;
};

#endif