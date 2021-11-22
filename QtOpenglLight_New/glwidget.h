#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QMouseEvent>

#include "objfileloader.h"

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    struct Light {
        QVector3D lightPosition;
        GLfloat lightShiness;
        QVector3D lightAmbient;
        QVector3D lightDiffuse;
        QVector3D lightSpecular;
        QVector3D lightEmission;
    };

    GlWidget(QWidget *partent);
    ~GlWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    void initObjects();
    void initShader();
    void initLight();
    void setRotation(int angle, int axis);

public:
    QVector3D m_vRot = QVector3D(0, 0, 0);
    QVector3D m_lightRot = QVector3D(0, 0, 0);

private:
    QString m_sProPath; // pro file path
    QTimer timer;
    float currentTime = 0.f;

    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLFunctions_4_3_Core *f = nullptr;

    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;

    ObjFileLoader loader;

    Light lights[3];

    QMatrix4x4 projection;
    QVector2D mousePressPosition;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;

    GLfloat lightPosition[4] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat lightShiness[1] = { 50 };
    GLfloat lightAmbient[4] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat lightDiffuse[4] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat lightSpecular[4] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat lightEmission[4] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat lightPosition1[4] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat lightShiness1[1] = { 50 };
    GLfloat lightAmbient1[4] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat lightDiffuse1[4] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat lightSpecular1[4] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat lightEmission1[4] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat lightPosition2[4] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat lightShiness2[1] = { 50 };
    GLfloat lightAmbient2[4] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat lightDiffuse2[4] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat lightSpecular2[4] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat lightEmission2[4] = { 0.0, 0.0, 0.0, 1.0 };
};

#endif
