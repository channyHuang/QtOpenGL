#ifndef BSPINE_H
#define BSPINE_H

#include <QGLWidget>

#include "data.h"

class BspineClass : public QGLWidget
{
	Q_OBJECT

public:
	BspineClass(QWidget *parent = 0);
	~BspineClass();

	int flag;
	void drawPoint(Points pt);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:
	void drawLine(Points p1, Points p2);
	Points CmpBSpine(Points pa, Points pb, Points pc, Points pd, double t);
};

#endif