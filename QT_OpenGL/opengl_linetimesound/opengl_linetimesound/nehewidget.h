#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "ui_nehewidget.h"

class nehewidget : public QGLWidget
{
	Q_OBJECT

public:
	nehewidget(QWidget *parent = 0);
	~nehewidget();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);

	void keyPressEvent(QKeyEvent *e);

	GLvoid BuildFont(GLvoid);
	void ResetObjects(void);
	GLvoid glPrint(GLint x, GLint y, int set, const char *fmt, ...);

	bool fullscreen;

	GLuint  texture[2];       // �ַ�����
	GLuint  base;        // �ַ���ʾ�б�Ŀ�ʼֵ
};

#endif // NEHEWIDGET_H
