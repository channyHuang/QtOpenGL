#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>

class GlWidget : public QGLWidget
{
	Q_OBJECT
public:
	GlWidget(QGLWidget *parent = 0);
	~GlWidget();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	void createLight();
};

#endif