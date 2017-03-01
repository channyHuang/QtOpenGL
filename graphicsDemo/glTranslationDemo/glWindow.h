#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>

#include "model.h"

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

	void displaymodel();
private:
	void drawGrid(float size, float step);
	void drawAxis(float size);

	Model model;
};

#endif