#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "ktxloader.h"

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
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;

    QOpenGLTexture *m_texture;
    GLuint texture;
    ktxLoader loader;
    double t = 0;
};

#endif
