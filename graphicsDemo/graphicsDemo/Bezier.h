#ifndef BEZIER_H
#define BEZIER_H

#include <QtOpenGL/QGLWidget>

#include "data.h"

class BezierClass : public QGLWidget
{
	Q_OBJECT

public:
	BezierClass(QWidget *parent = 0);
	~BezierClass();

	int flag;
	void drawPoint(Points pt);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:
	void drawLine(Points p1, Points p2);
	Points CmpBezier(Points pa, Points pb, Points pc, Points pd, double t);
};

#endif