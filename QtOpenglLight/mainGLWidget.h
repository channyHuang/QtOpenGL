#ifndef MAINGLWIDGET_H
#define MAINGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QKeyEvent>

#include "model.h"

class MainGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	MainGLWidget(QWidget *parent = 0);
	~MainGLWidget();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
private:
	void displaymodel();
	Model model;
public:
	GLfloat xrot, yrot, zrot;
	GLfloat lightxrot, lightyrot, lightzrot;
};

#endif 