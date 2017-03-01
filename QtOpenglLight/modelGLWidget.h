#ifndef MODELGLWIDGET_H
#define MODELGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>

/*
GLfloat lightPosition[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightShiness[1] = { 50 };
GLfloat lightAmbient[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightDiffuse[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightSpecular[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightEmission[4] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat lightPosition1[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightShiness1[1] = { 50 };
GLfloat lightAmbient1[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightDiffuse1[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightSpecular1[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat lightEmission1[4] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat lightPosition2[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightShiness2[1] = { 50 };
GLfloat lightAmbient2[4] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat lightDiffuse2[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat lightSpecular2[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat lightEmission2[4] = { 0.0, 0.0, 0.0, 1.0 };
*/
class ModelGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	ModelGLWidget(QWidget *parent = 0);
	~ModelGLWidget();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
private:
	QPoint startPoint, endPoint;
public:
	GLfloat xrot, yrot, zrot;
};

#endif