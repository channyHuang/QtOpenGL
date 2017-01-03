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

	bool masking;     // 是否使用“掩模”
	bool scene;      // 绘制那一个场景
	GLuint texture[3];     // 保存5个纹理标志
	GLuint loop;      // 循环变量

	GLfloat roll;      // 滚动纹理

};

#endif // NEHEWIDGET_H
