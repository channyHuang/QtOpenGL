#ifndef MODELWIDGET_H
#define MODELWIDGET_H

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

class ModelWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    struct Light {
        QVector4D lightPosition;
        GLfloat lightShiness;
        QVector4D lightAmbient;
        QVector4D lightDiffuse;
        QVector4D lightSpecular;
        QVector4D lightEmission;
    };

    ModelWidget(QWidget *partent);
    ~ModelWidget();

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
};

#endif
