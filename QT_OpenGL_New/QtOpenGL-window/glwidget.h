#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GlWidget(QWidget *partent);
    ~GlWidget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    QOpenGLShaderProgram *m_shader;
};

#endif