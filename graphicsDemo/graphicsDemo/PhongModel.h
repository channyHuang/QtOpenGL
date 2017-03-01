#ifndef PHONGMODEL_H
#define PHONGMODEL_H

#include <QtOpenGL/QGLWidget>

class LightClass : public QGLWidget
{
	Q_OBJECT
public:
	LightClass(QWidget *parent = 0);
	~LightClass();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);


};

#endif