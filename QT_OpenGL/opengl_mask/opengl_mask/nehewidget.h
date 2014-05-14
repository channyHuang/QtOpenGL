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
	void loadGLTextures();

	bool masking;     // �Ƿ�ʹ�á���ģ��
	bool scene;      // ������һ������
	GLuint texture[3];     // ����5�������־
	GLuint loop;      // ѭ������

	GLfloat roll;      // ��������

};

#endif // NEHEWIDGET_H
