#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QMatrix4x4>

#include "logo.h"

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GlWidget(QWidget *partent = nullptr);
    ~GlWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    void initCubeGeometry();
    void drawCubeGeometry();
    void initShader();
    void setRotation(int angle, int axis);

private:
    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;

    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;

    QMatrix4x4 projection;
    QVector2D mousePressPosition;

    bool m_core = false;

    Logo m_logo;
    QOpenGLBuffer *m_vbo;

    int m_Rot[3] = {0, 0, 0};
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
};

#endif
